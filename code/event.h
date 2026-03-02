#pragma once
#include <string>
#include <iostream>
using namespace std;

class DateTime {

private:
	int day, month, year, hour, minutes;

public:
	DateTime(int day = 0, int month = 0, int year = 0, 
		int hour = 0, int minutes = 0);

	bool operator!=(const DateTime& other) const {
		return this->day != other.day || this->month != other.month ||
			this->year != other.year || this->hour != other.hour;
			//this->minutes != other.minutes;
	};

	bool operator>(const DateTime& other) const {
		if (this->year > other.year) return true;
		else if (this->year == other.year && this->month > other.month) 
			return true;
		else if (this->year == other.year && this->month == other.month 
			&& this->day > other.day) return true;
		else if (this->year == other.year && this->month == other.month 
			&& this->day == other.day && this->hour > other.hour) return true;
		else if (this->year == other.year && this->month == other.month 
			&& this->day == other.day && this->hour == other.hour 
			&& this->minutes > other.minutes) return true;
		return false;
	};

	int getDay() const {
		return this->day;
	};
	void setDay(int day) {
		this->day = day;
	};
	int getMonth() {
		return this->month;
	};
	void setMonth(int month) {
		this->month = month;
	};
	int getYear() {
		return this->year;
	};
	void setYear(int year) {
		this->year = year;
	};
	int getHour() {
		return this->hour;
	};
	void setHour(int hour) {
		this->hour = hour;
	};
	int getMinutes() {
		return this->minutes;
	};
	void setMinutes(int minutes) {
		this->minutes = minutes;
	};
	string getDate() {
		string str = "";
		str += to_string(this->day) + "/" + to_string(this->month) + "/" + to_string(this->year);
		return str;
	}
	string getTime() {
		string str = "";
		str += to_string(this->hour) + ":" + to_string(this->minutes);
		return str;
	}
};

class Event {

private:
	string title;
	string description;
	DateTime date_time;
	int number_of_people;
	string link;

public:
	Event(string title, string description, DateTime date_time,
		int number_of_people, string link);
	string getTitle() const {
		return this->title;
	};
	string getDescription() const {
		return this->description;
	};
	void setDescription(string description) {
		this->description = description;
	};
	DateTime getDateTime() const {
		return this->date_time;
	};
	void setDateTime(DateTime date_time) {
		this->date_time = date_time;
	};
	int getNumberOfPeople() const {
		return this->number_of_people;
	};
	void setNumberOfPeople(int number_of_people) {
		this->number_of_people = number_of_people;
	};
	string getLink() const {
		return this->link;
	};
	void setLink(string link) {
		this->link = link;
	};
	Event();
	string eventToString();
};

ostream& operator<<(ostream& output, const Event& event);
istream& operator>>(istream& input, Event& event);