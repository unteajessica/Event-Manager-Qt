#pragma once
#include "repo.h"
#include "WriteToFile.h"
#include "action.h"
#include <memory>
#include <stack>

using namespace std;

class Controller {
private:
	Repo& cont;
	WriteToFile* fileWriter;

    stack<unique_ptr<Action>> undo_stack;
    stack<unique_ptr<Action>> redo_stack;
public:
	Controller(Repo& repo);
	Controller(Repo& repo, WriteToFile* fw);
	~Controller();

	void add_event_controller(Event new_event);
	void remove_event_controller(string title);
	void update_event_controller(string title, Event new_event);
	void update_number_of_people(string title, int increase);

	Event* getEvents() { return this->cont.getEvents(); };
	vector<Event> getRepo() { return this->cont.getRepo(); }
	int getSize() { return this->cont.getSize(); };
	std::vector<Event> events_for_given_month(int month);
    std::vector<Event> sorted_events();

	void saveToFile() { if (fileWriter) fileWriter->writeToFile(cont.getRepo()); };

    void undo();
    void redo();
};
