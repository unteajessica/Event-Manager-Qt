#include "chartwidget.h"
#include <QPainter>
#include <QFont>
#include <vector>
#include <algorithm>

ChartWidget::ChartWidget(QWidget *parent) : QWidget(parent) {}

void ChartWidget::setEventData(const std::vector<Event>& eventList) {
    events = eventList;
    update();
}

void ChartWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Fixed interval order
    std::vector<std::pair<QString, int>> ranges = {
        {"0–300", 0},
        {"301–500", 0},
        {"501–1000", 0},
        {"1000+", 0}
    };

    for (const Event& e : events) {
        int people = e.getNumberOfPeople();
        if (people <= 300) ranges[0].second++;
        else if (people <= 500) ranges[1].second++;
        else if (people <= 1000) ranges[2].second++;
        else ranges[3].second++;
    }

    // Margins
    int leftMargin = 60;
    int rightMargin = 30;
    int topMargin = 50;
    int bottomMargin = 50;

    QRect chartArea(leftMargin, topMargin, width() - leftMargin - rightMargin, height() - topMargin - bottomMargin);
    painter.drawRect(chartArea);  // Draw the chart frame

    // Max value for Y-axis
    int maxValue = std::max(1, std::max_element(
                                   ranges.begin(), ranges.end(),
                                   [](const auto& a, const auto& b) { return a.second < b.second; }
                                   )->second);

    // Bar layout
    int barCount = ranges.size();
    int barSpacing = 20;
    int barWidth = (chartArea.width() - (barSpacing * (barCount + 1))) / barCount;

    // Draw horizontal grid lines and Y-axis ticks
    painter.setPen(QColor(200, 200, 200));
    QFont tickFont = painter.font();
    tickFont.setPointSize(8);
    painter.setFont(tickFont);
    int tickCount = std::min(maxValue, 10);

    for (int i = 0; i <= tickCount; ++i) {
        int value = i * maxValue / tickCount;
        int y = chartArea.bottom() - (value * chartArea.height()) / maxValue;
        painter.drawLine(chartArea.left(), y, chartArea.right(), y);  // grid line
        painter.setPen(Qt::white);
        painter.drawText(chartArea.left() - 40, y - 5, 35, 15, Qt::AlignRight | Qt::AlignVCenter, QString::number(value));
    }

    // Draw bars
    for (int i = 0; i < barCount; ++i) {
        const auto& [label, count] = ranges[i];
        int x = chartArea.left() + barSpacing + i * (barWidth + barSpacing);
        int barHeight = (count * chartArea.height()) / maxValue;
        int y = chartArea.bottom() - barHeight;

        QRect barRect(x, y, barWidth, barHeight);
        painter.setBrush(QColor(80 + i * 40, 140 + i * 20, 200 - i * 30));
        painter.setPen(Qt::black);
        painter.drawRect(barRect);

        // X-axis labels
        QRect textRect(x, chartArea.bottom() + 5, barWidth, 20);
        painter.setPen(Qt::white);
        painter.drawText(textRect, Qt::AlignCenter, label);
    }

    // Draw axes
    painter.setPen(Qt::black);
    painter.drawLine(chartArea.topLeft(), chartArea.bottomLeft());   // Y-axis
    painter.drawLine(chartArea.bottomLeft(), chartArea.bottomRight()); // X-axis

    // Axis Labels
    QFont axisFont = painter.font();
    axisFont.setPointSize(10);
    axisFont.setBold(true);
    painter.setFont(axisFont);
    painter.setPen(Qt::white);
    painter.drawText(chartArea.left() - 50, chartArea.top() - 20, "Number of Events");
    painter.drawText(QRect(chartArea.left(), chartArea.bottom() + 30, chartArea.width(), 20), Qt::AlignCenter, "Audience Size Interval");

    // Chart Title
    QFont titleFont = painter.font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.setPen(Qt::white);
    painter.drawText(QRect(0, 10, width(), 30), Qt::AlignCenter, "Event Count by Audience Size");
}
