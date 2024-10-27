/*
Define a structure student with roll and score as attributes and with two member
functions to take input and to show the data. Use the member functions to take
data for a structure variable and to show. Write global function i) to modify score
and ii) to show the data again.
*/
#include <iostream>


struct Student {
    int roll;
    int score;

    int setDataFromConsole() {
        std::cout << "Enter roll number: ";
        std::cin >> this->roll;
        std::cout << "Enter score: ";
        std::cin >> this->score;
    }

    int printData() {
        std::cout << "Roll number: " << this->roll << "\nScore : " << this->score << '\n';
    }
};


void modifyStudentScore(Student& student) {
    std::cout << "Enter new roll number: ";
    std::cin >> student.roll;
    std::cout << "Enter score: ";
    std::cin >> student.score;
}


int printData(Student student) {
    std::cout << "Roll number: " << student.roll << "\nScore : " << student.score << '\n';
}


int main() {
    struct Student student;

    student.setDataFromConsole();
    student.printData();

    modifyStudentScore(student);
    printData(student);
    
    return 0;
}