/*
Design a class TIME which stores hour, minute and second. The class should
have the methods to support the following:
 User may give the time value in 24-hour format.
 User may give the time value in AM/PM format
 Display the time in 24-hour format.
 Display the time in AM/PM format.
 User may like to add minute with a time value.
*/

#include <iostream>
#include <stdexcept>
#include <string>

class TIME {
public:
    TIME(int hour, int minute, int second) {
        setTime(hour, minute, second);
    }

    TIME(int hour, int minute, const std::string& period) {
        if (period == "AM" || period == "PM") {
            if (period == "PM" && hour != 12) {
                hour += 12;
            } else if (period == "AM" && hour == 12) {
                hour = 0;
            }
            setTime(hour, minute, 0);
        } else {
            throw std::invalid_argument("Invalid period. Use 'AM' or 'PM'.");
        }
    }

    void setTime(int hour, int minute, int second) {
        if (hour < 0 || hour >= 24 || minute < 0 || minute >= 60 || second < 0 || second >= 60) {
            throw std::invalid_argument("Invalid time value.");
        }
        _hour = hour;
        _minute = minute;
        _second = second;
    }

    void display24HourFormat() const {
        std::cout << (_hour < 10 ? "0" : "") << _hour << ":"
                  << (_minute < 10 ? "0" : "") << _minute << ":"
                  << (_second < 10 ? "0" : "") << _second << std::endl;
    }

    void displayAMPMFormat() const {
        int displayHour = _hour % 12;
        if (displayHour == 0) {
            displayHour = 12;
        }
        std::string period = (_hour < 12) ? "AM" : "PM";
        std::cout << displayHour << ":"
                  << (_minute < 10 ? "0" : "") << _minute << " "
                  << period << std::endl;
    }

    void addMinutes(int minutesToAdd) {
        _minute += minutesToAdd;
        while (_minute >= 60) {
            _minute -= 60;
            _hour++;
        }
        while (_hour >= 24) {
            _hour -= 24;
        }
    }

private:
    int _hour;
    int _minute;
    int _second;
};

int main() {

    return 0;
}

