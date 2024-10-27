/*
Write a function swap (a, b) to interchange the values of two variables. Do not
use pointers.
*/


#include <iostream>


void swap(int& a, int& b) {
    a = a^b;
    b = a^b;
    a = a^b;
}


int main() {
    int a, b;
    std::cout << "Enter 2 integers: ";
    std::cin >> a >> b;

    swap(a, b);

    std::cout << "Swapped ints: " << a << " " << b << '\n';
}