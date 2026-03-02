#pragma once
#include "event.h"
#include <stdexcept>
#include <string>
using namespace std;

class EventValidator {
public:
    static void validate(const Event& event) {
        if (event.getTitle().empty()) {
            throw invalid_argument("Title cannot be empty!");
        }
        if (event.getDescription().empty()) {
            throw invalid_argument("Description cannot be empty!");
        }
        if (event.getDateTime().getDay() < 1 || event.getDateTime().getDay() > 31) {
            throw invalid_argument("Day must be between 1 and 31.");
        }
        if (event.getDateTime().getMonth() < 1 || event.getDateTime().getMonth() > 12) {
            throw invalid_argument("Month must be between 1 and 12.");
        }
        if (event.getDateTime().getYear() < 2020 || event.getDateTime().getYear() > 2030) {
            throw invalid_argument("Year must be between 2020 and 2030.");
        }
        if (event.getDateTime().getHour() < 0 || event.getDateTime().getHour() > 24) {
            throw invalid_argument("Hour must be between 0 and 24.");
        }
        if (event.getDateTime().getMinutes() < 0 || event.getDateTime().getMinutes() > 59) {
            throw invalid_argument("Minutes must be between 0 and 59.");
        }
        if (event.getNumberOfPeople() < 0) {
            throw invalid_argument("Number of people cannot be negative.");
        }
    }
};
