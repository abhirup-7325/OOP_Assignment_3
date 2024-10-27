/*
Design a STUDENT class to store roll, name, course, admission date and marks
in 5 subjects. Provide methods corresponding to admission (marks are not
available then), receiving marks and preparing mark sheet. Support must be
there to show the number of students who have taken admission.
*/


#include <iostream>


class Student {
public:
    Student(int roll, std::string name) {
        _roll = roll;
        _name = name;

        _totalCount++;
    }

    void admission(std::string course, std::string _admissionDate) {
        _course = course;
        _admissionDate = _admissionDate;
    }

    void setMarks(int* marks) {
        for (int i = 0; i < 5; i++) {
            _marks[i] = marks[i];
        }
    }

    void printMarksSheet() {
        std::cout << "Roll number: " << _roll << '\n';
        std::cout << "Name: " << _name << '\n';
        std::cout << "Course: " << _course << '\n';
        std::cout << "Admission date: " << _admissionDate << '\n';
        std::cout << "Marks in the 5 subjects: ";
        for (int i = 0; i < 5; i++) {
            std::cout << _marks[i] << ' ';
        }
        std::cout << '\n';
    }

    static printTotalStudentCount() {
        std::cout << "Total number of students: " << _totalCount << '\n';
    }

private:
    int _roll;
    std::string _name;
    std::string _course;
    std::string _admissionDate;
    int _marks[5];

    static int _totalCount;
};

int Student::_totalCount = 0;


int main() {
    // Client code

    return 0;
}