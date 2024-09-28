/*
Write a function swap (a, b) to interchange the values of two variables. Do not use
pointers.
*/


#include <iostream>
using namespace std;


void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}


int main() {
    int a, b;

    cout << "Enter 2 numbers: ";
    cin >> a >> b;

    swap(a, b);

    cout << "Swapped value: " << a << ' ' << b;

    return 0;
}