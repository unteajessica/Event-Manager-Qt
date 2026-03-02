#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <vector>
#include "code/event.h"

class ChartWidget : public QWidget {
    Q_OBJECT

public:
    explicit ChartWidget(QWidget *parent = nullptr);
    void setEventData(const std::vector<Event>& events);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::vector<Event> events;
};

#endif // CHARTWIDGET_H
