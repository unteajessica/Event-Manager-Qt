#define NOMINMAX
#undef byte
#include <windows.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->mainMenuPage);

    // Ctrl+Y → Undo
    QShortcut* shortcutUndo = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y), this);
    connect(shortcutUndo, &QShortcut::activated, this, &MainWindow::handleUndoButton);

    // Ctrl+Z → Redo
    QShortcut* shortcutRedo = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), this);
    connect(shortcutRedo, &QShortcut::activated, this, &MainWindow::handleRedoButton);


    ui->viewTable->setHorizontalHeaderLabels(QStringList()
                                               << "Title" << "Description" << "Date"
                                               << "Time" << "People" << "Link");

    repo = std::make_unique<Repo>("events.txt");
    user_repo = std::make_unique<Repo>("user_events.txt");
    controller = std::make_unique<Controller>(*repo);

    // main menu buttons
    connect(ui->CSVButton, &QPushButton::clicked, this, &MainWindow::handleCSVButton);
    connect(ui->HTMLButton, &QPushButton::clicked, this, &MainWindow::handleHTMLButton);
    connect(ui->adminButton, &QPushButton::clicked, this, &MainWindow::handleAdminButton);
    connect(ui->userButton, &QPushButton::clicked, this, &MainWindow::handleUserButton);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::handleExitButton);
    connect(ui->chartButton, &QPushButton::clicked, this, &MainWindow::handleChartButton);
    connect(ui->chartBackButton, &QPushButton::clicked, this, &MainWindow::handleChartBackButton);

    // admin menu buttons
    // add
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::handleAdminAddButton);
    connect(ui->submitAddButton, &QPushButton::clicked, this, &MainWindow::handleAdminSubmitAddButton);
    // remove
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::handleAdminRemoveButton);
    connect(ui->submitRemoveButton, &QPushButton::clicked, this, &MainWindow::handleAdminSubmitRemoveButton);
    //update
    connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::handleAdminUpdateButton);
    connect(ui->submitUpdateButton, &QPushButton::clicked, this, &MainWindow::handleAdminSubmitUpdateButton);
    // view
    connect(ui->viewButton, &QPushButton::clicked, this, &MainWindow::handleAdminViewButton);
    connect(ui->adminViewBackButton, &QPushButton::clicked, this, &MainWindow::handleAdminViewBackButton);
    //view table
    connect(ui->viewTableButton, &QPushButton::clicked, this, &MainWindow::handleViewTableButton);
    //undo
    connect(ui->undoButton, &QPushButton::clicked, this, &MainWindow::handleUndoButton);
    //redo
    connect(ui->redoButton, &QPushButton::clicked, this, &MainWindow::handleRedoButton);
    // back
    connect(ui->adminBackButton, &QPushButton::clicked, this, &MainWindow::handleAdminBackButton);

    // user menu buttons
    // view
    connect(ui->viewAllButton, &QPushButton::clicked, this, &MainWindow::handleUserViewButton);
    connect(ui->submitMonthButton, &QPushButton::clicked, this, &MainWindow::handleUserSubmitMonthButton);
    connect(ui->userAddButton, &QPushButton::clicked, this, &MainWindow::handleUserAddEventButton);
    connect(ui->previousEventButton, &QPushButton::clicked, this, &MainWindow::handleUserPreviousButton);
    connect(ui->nextEventButton, &QPushButton::clicked, this, &MainWindow::handleUserNextButton);
    connect(ui->userViewBackButton, &QPushButton::clicked, this, &MainWindow::handleUserViewBackButton);
    // remove
    connect(ui->userRemoveButton, &QPushButton::clicked, this, &MainWindow::handleUserRemoveButton);
    connect(ui->userSubmitRemoveButton, &QPushButton::clicked, this, &MainWindow::handleUserSubmitRemoveButton);
    // view my list
    connect(ui->viewUserListButton, &QPushButton::clicked, this, &MainWindow::handleViewUserListButton);
    connect(ui->userListBackButton, &QPushButton::clicked, this, &MainWindow::handleUserListbackButton);
    // open my list
    connect(ui->openListButton, &QPushButton::clicked, this, &MainWindow::handleOpenListButton);
    // back
    connect(ui->userBackButton, &QPushButton::clicked, this, &MainWindow::handleUserBackButton);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleExitButton() {
    QApplication::quit();
}

void MainWindow::handleCSVButton() {
    writer = new CSVWriteToFile("events.csv");
    user_controller = new Controller(*user_repo, writer);
    userListFileName = "events.csv";
    QMessageBox::information(this, "File Type", "CSV selected");
}

void MainWindow::handleHTMLButton() {
    writer = new HTMLWriteToFile("events.html");
    user_controller = new Controller(*user_repo, writer);
    userListFileName = "events.html";
    QMessageBox::information(this, "File Type", "HTML selected");
}

void MainWindow::handleAdminButton() {
    //QMessageBox::information(this, "Mode", "Admin Mode selected");
    ui->stackedWidget->setCurrentWidget(ui->adminPage);
}

void MainWindow::handleUserButton() {
    //QMessageBox::information(this, "Mode", "User Mode selected");
    ui->stackedWidget->setCurrentWidget(ui->userPage);
}

void MainWindow::handleAdminAddButton() {
    ui->stackedWidget->setCurrentWidget(ui->adminAddPage);
}

void MainWindow::handleAdminSubmitAddButton() {
    QString title_str = ui->titleBox->text();
    QString description_str = ui->descriptionBox->text();
    QDateTime date_time = ui->dateTimeBox->dateTime();
    int people_int = ui->peopleBox->value();
    QString link_str = ui->linkBox->text();

    QDate date = date_time.date();
    QTime time = date_time.time();

    DateTime dt(
        date.day(),
        date.month(),
        date.year(),
        time.hour(),
        time.minute()
        );

    Event event(
        title_str.toStdString(),
        description_str.toStdString(),
        dt,
        people_int,
        link_str.toStdString()
        );

    try {
        EventValidator::validate(event);
        controller->add_event_controller(event);
        QMessageBox::information(this, "Success", "Event added successfully");
        ui->stackedWidget->setCurrentWidget(ui->adminPage);
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Validation Error", e.what());
    }
}

void MainWindow::handleAdminViewButton() {
    loadData();
    ui->stackedWidget->setCurrentWidget(ui->adminViewPage);
}

void MainWindow::loadData() {
    std::vector<Event> events = controller->getRepo();
    ui->viewTable->setRowCount(events.size());
    int row = 0;
    for (auto& e : events) {
        ui->viewTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(e.getTitle())));
        ui->viewTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(e.getDescription())));
        ui->viewTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(e.getDateTime().getDate())));
        ui->viewTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(e.getDateTime().getTime())));
        ui->viewTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(to_string(e.getNumberOfPeople()))));
        ui->viewTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(e.getLink())));
        row++;
    }
    ui->viewTable->resizeColumnsToContents();
    ui->viewTable->resizeRowsToContents();
}

void MainWindow::handleAdminViewBackButton() {
    ui->stackedWidget->setCurrentWidget(ui->adminPage);
}

void MainWindow::handleAdminBackButton() {
    ui->stackedWidget->setCurrentWidget(ui->mainMenuPage);
}

void MainWindow::handleUserBackButton() {
    ui->stackedWidget->setCurrentWidget(ui->mainMenuPage);
}

void MainWindow::handleAdminRemoveButton() {
    ui->stackedWidget->setCurrentWidget(ui->adminRemovePage);
}

void MainWindow::handleAdminSubmitRemoveButton() {
    QString title = ui->titleToRemoveBox->text();
    try {
        if (title.isEmpty()) throw invalid_argument("Title cannot be empty!");
        controller->remove_event_controller(title.toStdString());
        QMessageBox::information(this, "Succes", "Event removed successfully!");
        ui->stackedWidget->setCurrentWidget(ui->adminPage);
    } catch(const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::handleAdminUpdateButton() {
    ui->stackedWidget->setCurrentWidget(ui->adminUpdatePage);
}


void MainWindow::handleAdminSubmitUpdateButton() {
    QString title = ui->up_titleBox->text();
    QString description = ui->up_descriptionBox->text();
    QDate date = ui->up_dateBox->date();
    QTime time = ui->up_timeBox->time();
    int people = ui->up_peopleBox->value();
    QString link = ui->up_linkBox->text();

    DateTime new_date(date.day(), date.month(), date.year(), time.hour(), time.minute());
    Event new_event(title.toStdString(), description.toStdString(), new_date, people, link.toStdString());

    try {
        controller->update_event_controller(title.toStdString(), new_event);
        QMessageBox::information(this, "Succes", "Event updated successfully!");
        ui->stackedWidget->setCurrentWidget(ui->adminPage);
    } catch(const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::handleUserViewButton() {
    ui->stackedWidget->setCurrentWidget(ui->userViewPage);
}

void MainWindow::handleUserSubmitMonthButton() {
    int month = ui->monthBox->value();
    if (month == 0) userEventsList = controller->sorted_events();
    else userEventsList = controller->events_for_given_month(month);

    if (userEventsList.empty()) {
        QMessageBox::information(this, "No Events", "There are no events in the selected month.");
        ui->stackedWidget->setCurrentWidget(ui->userPage);
        return;
    }

    userEventIndex = 0;
    showCurrentUserEvent();
    ui->stackedWidget->setCurrentWidget(ui->userViewPage);
}

void MainWindow::showCurrentUserEvent() {
    if (userEventIndex < 0 || userEventIndex >= userEventsList.size()) return;

    current_event = userEventsList[userEventIndex];
    ui->userViewTable->setRowCount(1); // make sure only 1 row is shown
    ui->userViewTable->setItem(0, 0, new QTableWidgetItem(QString::fromStdString(current_event.getTitle())));
    ui->userViewTable->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(current_event.getDescription())));
    ui->userViewTable->setItem(0, 2, new QTableWidgetItem(QString::fromStdString(current_event.getDateTime().getDate())));
    ui->userViewTable->setItem(0, 3, new QTableWidgetItem(QString::fromStdString(current_event.getDateTime().getTime())));
    ui->userViewTable->setItem(0, 4, new QTableWidgetItem(QString::number(current_event.getNumberOfPeople())));
    ui->userViewTable->setItem(0, 5, new QTableWidgetItem(QString::fromStdString(current_event.getLink())));

    std::string link = current_event.getLink();
    if (!link.empty()) {
        ShellExecuteA(NULL, "open", link.c_str(), NULL, NULL, SW_SHOWNORMAL);
    }
}

void MainWindow::handleUserAddEventButton() {
    try {
        controller->update_number_of_people(current_event.getTitle(), 1);
        user_controller->add_event_controller(current_event);
        user_controller->update_number_of_people(current_event.getTitle(), 1);
        QMessageBox::information(this, "Added", "Event added to your list!");
        if (userEventIndex + 1 < userEventsList.size()) {
            userEventIndex++;
            showCurrentUserEvent();
        } else {
            QMessageBox::information(this, "End", "That was the last event.");
        }
    }
    catch (const exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::handleUserPreviousButton() {
    if (userEventIndex > 0) {
        userEventIndex--;
        showCurrentUserEvent();
    } else {
        QMessageBox::information(this, "Start", "You're at the first event.");
    }
}

void MainWindow::handleUserNextButton() {
    if (userEventIndex + 1 < userEventsList.size()) {
        userEventIndex++;
        showCurrentUserEvent();
    } else {
        QMessageBox::information(this, "End", "No more events.");
        userEventIndex = 0;
        showCurrentUserEvent();
    }
}

void MainWindow::handleUserViewBackButton() {
    ui->stackedWidget->setCurrentWidget(ui->userPage);
}

void MainWindow::handleUserRemoveButton() {
    ui->stackedWidget->setCurrentWidget(ui->userRemovePage);
}

void MainWindow::handleUserSubmitRemoveButton() {
    QString title = ui->userTitleToRemoveBox->text();
    try {
        if (title.toStdString().empty()) throw std::invalid_argument("Title cannot be empty!");
        controller->update_number_of_people(title.toStdString(), -1);
        user_controller->remove_event_controller(title.toStdString());
        QMessageBox::information(this, "Succes", "Event removed successfully!");
        ui->stackedWidget->setCurrentWidget(ui->userPage);
    }
    catch (const exception& e) {
        QMessageBox::warning(this, "Error", "Title is not valid!");
    }
}

void MainWindow::handleViewUserListButton() {
    ui->userListTable->setHorizontalHeaderLabels(QStringList()
                                             << "Title" << "Description" << "Date"
                                             << "Time" << "People" << "Link");
    std::vector<Event> events = user_controller->getRepo();
    ui->userListTable->setRowCount(events.size());
    int row = 0;
    for (auto& e : events) {
        ui->userListTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(e.getTitle())));
        ui->userListTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(e.getDescription())));
        ui->userListTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(e.getDateTime().getDate())));
        ui->userListTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(e.getDateTime().getTime())));
        ui->userListTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(to_string(e.getNumberOfPeople()))));
        ui->userListTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(e.getLink())));
        row++;
    }
    ui->userListTable->resizeColumnsToContents();
    ui->userListTable->resizeRowsToContents();

    ui->stackedWidget->setCurrentWidget(ui->userViewMyListPage);
}

void MainWindow::handleUserListbackButton() {
    ui->stackedWidget->setCurrentWidget(ui->userPage);
}

void MainWindow::handleOpenListButton() {
    if (userListFileName.empty()){
        QMessageBox::warning(this, "Error", "No file writer selected.");
        return;
    }
    ShellExecuteA(NULL, "open", userListFileName.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void MainWindow::handleChartButton() {
    auto events = controller->getRepo();
    ui->chartWidget->setEventData(events);
    ui->stackedWidget->setCurrentWidget(ui->chartPage);
}

void MainWindow::handleChartBackButton() {
    ui->stackedWidget->setCurrentWidget(ui->mainMenuPage);
}

void MainWindow::handleUndoButton() {
    try {
        controller->undo();
        QMessageBox::information(this, "Undo", "Undo executed successfully.");
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Undo Error", e.what());
    }
}

void MainWindow::handleRedoButton() {
    try {
        controller->redo();
        QMessageBox::information(this, "Redo", "Redo executed successfully.");
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Redo Error", e.what());
    }
}

void MainWindow::handleViewTableButton() {
    std::vector<Event> events = controller->getRepo();

    EventListWindow* eventListWindow = new EventListWindow(events, nullptr);
    eventListWindow->setAttribute(Qt::WA_DeleteOnClose); // Clean up when closed
    eventListWindow->raise();
    eventListWindow->activateWindow();
    eventListWindow->show();
}

