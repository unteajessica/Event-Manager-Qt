#include "repo.h"
#include "repoException.h"
#include <iostream>
#include<fstream>
using namespace std;

Repo::Repo(const string& filename) : filename(filename) {
	loadFromFile();
}

void Repo::loadFromFile() {
	ifstream fin(filename);
	if (!fin.is_open()) return;

	Event event;
    while (fin >> event) {
		repo.push_back(event);
	}

	fin.close();
}

void Repo::saveToFile() {
	ofstream fout(filename);
	for (const Event& event : repo) {
		fout << event << "\n";
	}
	fout.close();
}

int Repo::find_event(string title) {
	vector<Event> events = getRepo();
	int index = 0;
	for (const auto& event : events) {
		if (event.getTitle() == title)
			return index;
		index++;
	}
	return -1;
}

void Repo::add_event(Event event) {
	int index = find_event(event.getTitle());
	if (index != -1) 
		throw RepoException("This title already exists.");
	//else this->repo.push_back(event);
	repo.push_back(event);
	saveToFile();
}

void Repo::remove_event(string title) {
	int index = find_event(title);
	if (index != -1) {
		// this->repo.erase(this->repo.begin() + index);
		repo.erase(repo.begin() + index);
		saveToFile();
	}
	else throw RepoException("This title does not exist");
}

void Repo::update_event(string title, Event new_event) {
	int index = find_event(title);
	if (index != -1) {
		Event* events = getEvents();
		Event& existing_event = events[index];

		if (!new_event.getDescription().empty()) {
			existing_event.setDescription(new_event.getDescription());
		}
		if (new_event.getDateTime() != DateTime()) { 
			existing_event.setDateTime(new_event.getDateTime());
		}
		if (new_event.getNumberOfPeople() != 0) {
			existing_event.setNumberOfPeople(new_event.getNumberOfPeople());
		}
		if (!new_event.getLink().empty()) {
			existing_event.setLink(new_event.getLink());
		}
		saveToFile();
	}
	else throw RepoException("This title does not exist");
}

