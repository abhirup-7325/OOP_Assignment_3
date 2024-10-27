/*
Write a function max (a, b) that will return the reference of larger value. Store the
returned information to x where x is a i) variable of type a or b, ii) variable
referring to type of a or b. In both the cases modify x. Check also the values of a
and b.
*/

#include <iostream>


int maxVal(int a, int b) {
    return ((a > b) ? a : b);
}

int& maxRef(int& a, int& b) {
    return ((a > b) ? a : b);   
}


int main() {
    int a, b;
    std::cout << "Enter 2 integers: ";
    std::cin >> a >> b;

    int x_val = maxVal(a, b);
    int x_ref = maxRef(a, b);

    std::cout << "Max by value = " << x_val << '\n';
    std::cout << "Max by reference = " << x_ref << '\n';
}