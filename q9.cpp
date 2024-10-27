/*
Create an APPLICANT class with application id (auto generated as last id +1),
name and score. Support must be there to receive applicant data, show applicant
details and to find out number of applicants.
*/


#include <iostream>
#include <string>


class Applicant {
public:
    Applicant(std::string name, int score) {
        _count++;
        _id = _count + 1;
        _name = name;
        _score = score;
    }

    void print() {
        std::cout << "Name: " << _name << '\n';
        std::cout << "Score: " << _score << '\n';
    }

    static void showApplicantCount() {
        std::cout << "Applicant count = " << _count << '\n';
    }

private:
    int _id;
    std::string _name;
    int _score;

    static int _count;
};

int Applicant::_count = 0;


int main() {
    // Client code

    return 0;
}