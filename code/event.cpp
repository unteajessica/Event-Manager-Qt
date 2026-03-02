#include "event.h"

DateTime::DateTime(int day, int month, int year, int hour, int minutes) {
	this->day = day;
	this->month = month;
	this->year = year;
	this->hour = hour;
	this->minutes = minutes;
}

Event::Event(string title, string description, DateTime date_time,
	int number_of_people, string link) {
	this->title = title;
	this->description = description;
	this->date_time = date_time;
	this->number_of_people = number_of_people;
	this->link = link;
}

Event::Event() {
	this->title = "";
	this->description = "";
	this->date_time = DateTime(0, 0, 0, 0, 0);
	this->number_of_people = 0;
	this->link = "";
}

string Event::eventToString() {
	string result = "";
	result += "Title: " + this->title + "\n";
	result += "Description: " + this->description + "\n";
	result += "Date: " + to_string(this->date_time.getDay()) + "/" + to_string(this->date_time.getMonth()) + "/" + to_string(this->date_time.getYear()) + "\n";
	result += "Time: " + to_string(this->date_time.getHour()) + ":" + to_string(this->date_time.getMinutes()) + "\n";
	result += "Number of people: " + to_string(this->number_of_people) + "\n";
	result += "Link: " + this->link + "\n";
	return result;
}

ostream& operator<<(ostream& output, const Event& event) {
	output << event.getTitle() << "|"
		<< event.getDescription() << "|"
		<< event.getDateTime().getDay() << " "
		<< event.getDateTime().getMonth() << " "
		<< event.getDateTime().getYear() << " "
		<< event.getDateTime().getHour() << " "
		<< event.getDateTime().getMinutes() << "|"
		<< event.getNumberOfPeople() << "|"
		<< event.getLink();
	return output;
}

istream& operator>>(istream& input, Event& event) {
	string title, description, link;
	int day, month, year, hour, minutes, people;

	getline(input, title, '|');
	getline(input, description, '|');
	input >> day >> month >> year >> hour >> minutes;
	input.ignore(1, '|');
	input >> people;
	input.ignore(1, '|');
	getline(input, link);

	DateTime date_time(day, month, year, hour, minutes);
	event = Event(title, description, date_time, people, link);

	return input;
}