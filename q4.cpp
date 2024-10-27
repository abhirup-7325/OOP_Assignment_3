/*
Write a function void f(int) that prints “inside f(int)”. Call the function with actual
argument of type: i) int, ii) char, iii) float and iv) double. Add one more function
f(float) that prints “inside f(float)”. Repeat the calls again and observe the
outcomes.
*/


#include <iostream>


void f(int a) {
    std::cout << "Inside f(int)\n";
}


void f(float a) {
    std::cout << "Inside f(float)\n";
}


int main() {
    int a = 1;
    char b = 'b';
    float c = 5.5;
    double d = 6.9;

    // f(a);
    // f(b);
    // f(c);
    // f(d);
}