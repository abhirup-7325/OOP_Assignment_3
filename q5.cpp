/*
Define functions f(int, int) and f (char, int). Call the functions with arguments of
type (int, char), (char,char) and (float, float). Observe and analyze the outcome.
*/

#include <iostream>


void f(int, int) {
    std::cout << "Hi\n";
}


void f(char, int) {
    std::cout << "Bye\n";
}


int main() {
    int a = 5;
    char b = 'b';
    float c = 5.5;

    // f(a, b);
    // f(b, b);
    // f(c, c);
}