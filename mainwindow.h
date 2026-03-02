#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QShortcut>
#include <QKeySequence>

#include "code/controller.h"
#include "code/repo.h"
#include "code/CSVWriteToFile.h"
#include "code/HTMLWriteToFile.h"
#include "code/eventValidator.h"
#include "EventListView.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void handleExitButton();
    void handleCSVButton();
    void handleHTMLButton();
    void handleAdminButton();
    void handleUserButton();
    void handleChartButton();

    void handleAdminAddButton();
    void handleAdminSubmitAddButton();

    void handleAdminRemoveButton();
    void handleAdminSubmitRemoveButton();

    void handleAdminUpdateButton();
    void handleAdminSubmitUpdateButton();

    void handleAdminViewButton();
    void loadData();
    void handleAdminViewBackButton();

    void handleAdminBackButton();

    void handleUserViewButton();
    void handleUserSubmitMonthButton();
    void handleUserAddEventButton();
    void handleUserPreviousButton();
    void handleUserNextButton();
    void handleUserViewBackButton();

    void handleUserRemoveButton();
    void handleUserSubmitRemoveButton();

    void handleViewUserListButton();
    void handleUserListbackButton();

    void handleOpenListButton();

    void handleUserBackButton();

    void showCurrentUserEvent();

    void handleChartBackButton();

    void handleUndoButton();
    void handleRedoButton();
    void handleViewTableButton();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<Repo> repo;
    std::unique_ptr<Repo> user_repo;
    std::unique_ptr<Controller> controller;
    Controller* user_controller = nullptr;
    WriteToFile* writer = nullptr;
    std::string userListFileName = "";

    std::vector<Event> userEventsList;
    int userEventIndex = 0;
    Event current_event;

};
#endif // MAINWINDOW_H
