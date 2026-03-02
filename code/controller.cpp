#include "controller.h"
#include "eventValidator.h"
#include <iostream>
#include <algorithm>

Controller::Controller(Repo& repo) : cont{repo}, fileWriter(nullptr) {}

Controller::Controller(Repo& repo, WriteToFile* fw) : cont{repo}, fileWriter(fw) {}

Controller::~Controller() {
}

void Controller::add_event_controller(Event new_event) {
	EventValidator::validate(new_event);
	this->cont.add_event(new_event);
	if (fileWriter != nullptr) saveToFile();

    unique_ptr<Action> a = make_unique<ActionAdd>(new_event, cont);
    undo_stack.push(std::move(a));
}

void Controller::remove_event_controller(string title) {
    int index = this->cont.find_event(title);
    Event e = this->cont.getEvent(index);

	this->cont.remove_event(title);
	if (fileWriter != nullptr) saveToFile();

    std::unique_ptr<Action> a = std::make_unique<ActionRemove>(e, cont);
    undo_stack.push(std::move(a));
}

void Controller::update_event_controller(string title, Event new_event) {
    int index = this->cont.find_event(title);
    Event old_event = this->cont.getEvent(index);

    this->cont.update_event(title, new_event);
    if (fileWriter != nullptr) saveToFile();

    std::unique_ptr<Action> a = std::make_unique<ActionUpdate>(old_event, new_event, cont);
    undo_stack.push(std::move(a));
}

std::vector<Event> Controller::events_for_given_month(int month) {
	std::vector<Event> all = this->cont.getRepo();
	std::vector<Event> events;
	copy_if(all.begin(), all.end(), back_inserter(events), 
		[month](Event& e) {return e.getDateTime().getMonth() == month;});
	return events;
}

void Controller::update_number_of_people(string title, int increase) {
	int index = this->cont.find_event(title);
	if (index != -1) {
		Event* events = this->cont.getEvents();
		Event& existing_event = events[index];
		if (increase == 1)
			existing_event.setNumberOfPeople(existing_event.getNumberOfPeople() + 1);
		else existing_event.setNumberOfPeople(existing_event.getNumberOfPeople() - 1);
	}
	else throw std::exception("This title does not exist");
}

std::vector<Event> Controller::sorted_events() {
	std::vector<Event> events = this->cont.getRepo();
	sort(events.begin(), events.end(), [](Event& a, Event& b)
		{return b.getDateTime() > a.getDateTime();});

	return events;
}

void Controller::undo() {
    if (undo_stack.empty()) {
        throw std::runtime_error("No more undos available.");
    }
    unique_ptr<Action> action = std::move(undo_stack.top());
    undo_stack.pop();
    action->executeUndo();
    redo_stack.push(std::move(action));
}

void Controller::redo() {
    if (redo_stack.empty()) {
        throw std::runtime_error("No more redos available.");
    }
    unique_ptr<Action> action = std::move(redo_stack.top());
    redo_stack.pop();
    action->executeRedo();
    undo_stack.push(std::move(action));
}
