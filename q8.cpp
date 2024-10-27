/*
Create a STACK class with operation for initialization, push and pop. Support for
checking underflow and overflow condition are also to be provided.
*/


#include <iostream>


template <class type>

class Stack {
public:
    Stack(size_t size) {
        this->capacity = size;
        this->arr = new type[this->capacity];
        this->top = -1;
    }

    void push(type val) {
        if (this->top == this->capacity - 1) {
            std::cout << "Overflow! Cannot push value.\n";
            return;
        }

        (this->top)++;
        (this->arr)[top] = val;
    }

    void pop(type val) {
        if (this->top == -1) {
            std::cout << "Underflow! Cannot pop value.\n";
            return;
        }

        (this->top)--;
    }

    void print() {
        for (int i = 0; i <= this->top; i++) {
            std::cout << (this->arr)[i] << '\n';
        }
        std::cout << '\n';
    }

private:
    size_t capacity;
    type *arr;
    int top;
};


int main() {
    // Client code

    return 0;
}