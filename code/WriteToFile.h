#pragma once
#include <vector>
#include "event.h"
using namespace std;

class WriteToFile {
public:
	virtual void writeToFile(const vector<Event>& events) = 0;
	virtual ~WriteToFile() {}
};