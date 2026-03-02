#include "EventListView.h"
#include <QTableView>
#include <QVBoxLayout>

EventTableModel::EventTableModel(const std::vector<Event>& events, QObject* parent)
    : QAbstractTableModel(parent), events(events) {}

int EventTableModel::rowCount(const QModelIndex&) const {
    return static_cast<int>(events.size());
}

int EventTableModel::columnCount(const QModelIndex&) const {
    return 6;
}

QVariant EventTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};

    const Event& e = events.at(index.row());
    switch (index.column()) {
    case 0: return QString::fromStdString(e.getTitle());
    case 1: return QString::fromStdString(e.getDescription());
    case 2: return QString::fromStdString(e.getDateTime().getDate());
    case 3: return QString::fromStdString(e.getDateTime().getTime());
    case 4: return QString::number(e.getNumberOfPeople());
    case 5: return QString::fromStdString(e.getLink());
    default: return {};
    }
}

QVariant EventTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "Title";
        case 1: return "Description";
        case 2: return "Date";
        case 3: return "Time";
        case 4: return "People";
        case 5: return "Link";
        }
    }
    return {};
}

EventListWindow::EventListWindow(const std::vector<Event>& events, QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QVBoxLayout(this);
    auto* tableView = new QTableView(this);
    auto* model = new EventTableModel(events, this);

    tableView->setModel(model);
    tableView->resizeColumnsToContents();

    layout->addWidget(tableView);
    setLayout(layout);
    setWindowTitle("Event List");
    resize(800, 400);
}
