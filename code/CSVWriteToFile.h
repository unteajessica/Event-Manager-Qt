#pragma once
#include "WriteToFile.h"
#include <fstream>
using namespace std;

class CSVWriteToFile : public WriteToFile {
private:
	string filename;
public:
	CSVWriteToFile(const string& file) : filename(file) {}

	void writeToFile(const vector<Event>& events) override {
		ofstream fout(filename);
		fout << "Title,Description,Date,Time,Number of people,Link \n";
		for (auto& event : events) {
			fout << event.getTitle() << ","
				<< event.getDescription() << ","
				<< event.getDateTime().getDay() << "/"
				<< event.getDateTime().getMonth() << "/"
				<< event.getDateTime().getYear() << ","
				<< event.getDateTime().getHour() << ":"
				<< event.getDateTime().getMinutes() << ","
				<< event.getNumberOfPeople() << ","
				<< event.getLink() << "\n";
		}
		fout.close();
	}
};