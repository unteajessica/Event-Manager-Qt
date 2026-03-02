#pragma once
#include "event.h"
//#include "vector.h"
#include<vector>

class Repo {

private:
	std::vector<Event> repo;
	string filename;

	void loadFromFile();
	void saveToFile();

public:
	Repo(const string& filename);
	Repo() {};

	int find_event(string title);
	void add_event(Event event);
	void remove_event(string title);
    void update_event(string title, Event new_event);

	int getSize() { return this->repo.size(); }
	Event* getEvents() { return this->repo.data(); }
	Event getEvent(int index) { return this->repo.at(index); }
	std::vector<Event> getRepo() { return this->repo; };
	void setEvent(Event event, int index) { this->repo[index] = event; };
};
