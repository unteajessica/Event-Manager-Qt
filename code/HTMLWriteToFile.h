#pragma once
#include "WriteToFile.h"
#include <fstream>

class HTMLWriteToFile : public WriteToFile {
private:
	string filename;
public:
	HTMLWriteToFile(const string& file) : filename(file) {}
	void writeToFile(const vector<Event>& events) override {
		ofstream fout(filename);
        fout << "<HTML>\n<HEAD>\n<TITLE>Events</TITLE>\n</HEAD>\n<BODY>\n";
        fout << "<table border=\"1\">\n";
        fout << "<tr>\n"
            << "<td>Title</td>\n"
            << "<td>Description</td>\n"
            << "<td>Date</td>\n"
            << "<td>Time</td>\n"
            << "<td>Number of people</td>\n"
            << "<td>Link</td>\n"
            << "</tr>\n";

        for (const auto& event : events) {
            fout << "<tr>\n"
                << "<td>" << event.getTitle() << "</td>\n"
                << "<td>" << event.getDescription() << "</td>\n"
                << "<td>" << event.getDateTime().getDay() << " "
                << event.getDateTime().getMonth() << " "
                << event.getDateTime().getYear() << "</td>\n"
                << "<td>" << event.getDateTime().getHour() << " "
                << event.getDateTime().getMinutes() << "</td>\n"
                << "<td>" << event.getNumberOfPeople() << "</td>\n"
                << "<td><a href=\"" << event.getLink() << "\">" << event.getLink() << "</a></td>\n"
                << "</tr>\n";
        }
        fout << "</table>\n</BODY>\n</HTML>";
        fout.close();
	}
};
