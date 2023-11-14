#pragma once
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cmath>
using namespace std;
namespace linkedList {

    template<typename T>
    class Node {
    public:
        T _cofficient;
        Node* _next;
        Node(T cofficient) :_cofficient(cofficient), _next(nullptr) {}
    };

    template <typename T>
    class LinkedList {
    private:
        int _size;
        Node<T>* _head;
    public:
        LinkedList() : _size(0), _head(nullptr) {}
        LinkedList(int size, int upper_bound, int lover_bound);
        LinkedList(int size);
        ~LinkedList();
    };
}