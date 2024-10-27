/*
Create a class for linked list. Consider a separate class NODE for basic node
activities and use it in class for linked list.
*/


#include <iostream>


class Node {
public:
    Node(int val, Node* next = nullptr) {
        _val = val;
        _next = next;
    }

    int getVal() {
        return _val;
    }

    Node* next() {
        return _next;
    }

private:
    int _val;
    Node* _next;
};


class LinkedList {
public:
    LinkedList(Node* head = nullptr) {
        _head = head;
    }

    void display() {
        Node* node = _head;

        while (node != nullptr) {
            std::cout << node->getVal() << " -> ";
            node = node->next();
        }
        std::cout << "NULL\n";
    }

    void appendAtHead(int val) {
        Node* node = new Node(val, _head);
        _head = node;
    }

    void deleteAtHead() {
        if (_head == nullptr) {
            return;
        }

        Node* node = _head;
        _head = node->next();
        delete node;
    }

private:
    Node* _head;
};


int main() {
    LinkedList list;
    for (int i = 0; i < 5; i++) {
        list.appendAtHead(i + 1);
    }

    list.deleteAtHead();

    list.display();

    return 0;
}