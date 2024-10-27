/*
Write a function that will have income and tax rate as arguments and will return
tax amount. In case tax rate is not provided it will be automatically taken as 10%.
Call it with and without tax rate.
*/

#include <iostream>


float getTaxValue(float principle, float interestRate = 10.0) {
    return principle * interestRate / 100;
}


int main() {
    float principle = 100;
    float rate = 45.3;

    std::cout << "Tax amount = " << getTaxValue(principle, rate) << '\n';

    return 0;
}