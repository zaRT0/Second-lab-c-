#pragma once
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cmath>
using namespace std;
namespace list {

    template<typename T>
    class Node {
    public:
        T _cofficient;
        Node* _next;
        int _power;
        int get_coeff();
        Node(T cofficient, int power) :_cofficient(cofficient), _next(nullptr), _power(power) {}
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
        T& operator[](int index);
        T operator[](int index) const;
        LinkedList(const LinkedList<T>& other);
        LinkedList& operator=(const LinkedList<T>& other);
        void push_head(T cofficient, int power);
        void push_head(LinkedList<T> other);
        void push_tail(T cofficient, int power);
        void push_tail(LinkedList<T> other);
        void print_power()const;
        void pop_head();
        void pop_tail();
        void delete_node(Node<T>& node_to_delede);
        T evaluate_at(T x)const;
        void print_coeff()const;
    };

    template<typename T>
    void LinkedList<T>::print_power()const {
        Node<T>* current = _head;
        do {
            std::cout << current->_cofficient << "x^" << current->_power;
            current = current->_next;
            if (current != _head) {
                if (current->_cofficient > 0) std::cout << "+";
                else std::cout << "";
            }
        } while (current != _head);

        std::cout << std::endl;
    }

    template <typename T>
    int Node<T>::get_coeff() {
        return this->_cofficient;
    }

    template<typename T>
    LinkedList<T>::LinkedList(int size, int upper_bound, int lover_bound) : _head(nullptr) {
        srand(time(nullptr));
        for (int i = 0; i < size; ++i) {
            T cofficient = rand() % upper_bound + lover_bound;
            int power = rand() % 10 + 1;
            push_head(cofficient, power);
        }
    }

    LinkedList<float>::LinkedList(int size) : _head(nullptr)
    {
        srand(time(nullptr));
        for (int i = 0; i < size; ++i) {
            float cofficient = 0.001 * rand();
            int power = rand() % 10 + 1;
            push_head(cofficient, power);
        }
    }

    template<typename T>
    LinkedList<T>::~LinkedList()
    {
        while (_head) {
            pop_head();
        }
    }

    template<typename T>
    T& LinkedList<T>::operator[](int index)
    {
        int counter = 0;
        Node<T>* current = this->_head;
        do {
            if (counter == index) {
                return current->_cofficient;
            }
            current = current->_next;
            counter++;
        } while (current != this->_head);
    }

    template<typename T>
    T LinkedList<T>::operator[](int index) const {
        int counter = 0;
        Node<T>* current = _head;

        if (!current)
            throw std::out_of_range("List is empty");

        do {
            if (counter == index) {
                return current->_cofficient;
            }
            current = current->_next;
            counter++;
        } while (current != _head);

        throw std::out_of_range("Index out of range");
    }

    template<typename T>
    LinkedList<T>::LinkedList(const LinkedList<T>& other) : _head(nullptr), _size(0)
    {
        if (other._head) {
            Node<T>* otherCurrent = other._head;
            do {
                push_tail(otherCurrent->_cofficient, otherCurrent->_power);
                otherCurrent = otherCurrent->_next;
            } while (otherCurrent != other._head);
        }
    }

    template<typename T>
    LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
        if (this == &other) {
            return *this;
        }
        while (_head) {
            pop_head();
        }
        if (other._head) {
            Node<T>* otherCurrent = other._head;
            do {
                push_tail(otherCurrent->_cofficient, otherCurrent->_power);
                otherCurrent = otherCurrent->_next;
            } while (otherCurrent != other._head);
        }
        return *this;
    }

    template<typename T>
    void LinkedList<T>::push_head(T cofficient, int power)
    {
        if (cofficient == 0) {
            return;
        }
        Node<T>* _newmode = new Node<T>(cofficient, power);
        if (!_head) {
            _head = _newmode;
            _head->_next = _head;
        }
        Node<T>* current = _head;
        while (current->_next != _head) {
            current = current->_next;
        }
        _newmode->_next = _head;
        current->_next = _newmode;
        _head = _newmode;
        _size++;
    }

    template<typename T>
    void LinkedList<T>::push_head(LinkedList<T> other) {
        Node<T>* otherCurrent = other._head;
        LinkedList<T> reversed_other;
        if (otherCurrent) {
            do {
                reversed_other.push_head(otherCurrent->_cofficient, otherCurrent->_power);
                otherCurrent = otherCurrent->_next;
            } while (otherCurrent != other._head);
            otherCurrent = reversed_other._head;
            do {
                push_head(otherCurrent->_cofficient, otherCurrent->_power);
                otherCurrent = otherCurrent->_next;
            } while (otherCurrent != reversed_other._head);
        }
    }

    template<typename T>
    void LinkedList<T>::push_tail(T coefficient, int power) {
        if (coefficient == 0) {
            return;
        }
        Node<T>* new_node = new Node<T>(coefficient, power);
        if (!_head) {
            _head = new_node;
            _head->_next = _head;
        }
        else {
            Node<T>* current = _head;
            while (current->_next != _head) {
                current = current->_next;
            }
            current->_next = new_node;
            new_node->_next = _head;
        }
    }

     template<typename T>
    void LinkedList<T>::push_tail(LinkedList<T> other) {
        if (other._head) {
            Node<T>* otherCurrent = other._head;
            Node<T>* otherHead = other._head;
            do {
                Node<T>* new_node = new Node<T>(otherCurrent->_cofficient,otherCurrent->_power);
                if (!_head) {
                    _head = new_node;
                    _head->_next = _head;
                }
                else {
                    Node<T>* current = _head;
                    while (current->_next != _head) {
                        current = current->_next;
                    }
                    new_node->_next = _head;
                    current->_next = new_node;
                }
                otherCurrent = otherCurrent->_next;
            } while (otherCurrent != otherHead);
            other._head = nullptr;
        }
    }

    template<typename T>
    void LinkedList<T>::pop_head() {
        if (_head) {
            Node<T>* temp = _head;
            if (_head->_next != _head) {
                Node<T>* current = _head;
                while (current->_next != _head) {
                    current = current->_next;
                }
                _head = _head->_next;
                current->_next = _head;
            }
            else {
                _head = nullptr;
            }
            delete temp;
        }
    }

    template<typename T>
    void LinkedList<T>::pop_tail() {
        if (_head) {
            Node<T>* current = _head;
            Node<T>* previous = nullptr;

            while (current->_next != _head) {
                previous = current;
                current = current->_next;
            }
            if (previous) {
                previous->_next = _head;
            }
            else {
                _head = nullptr;
            }
            delete current;
        }
    }

    template<typename T>
    void LinkedList<T>::delete_node(Node<T>& node) {
        if (!_head) {
            return;
        }
        Node<T>* current = _head;
        while (current->_next != _head) {
            if (current->_next->_cofficient == node._cofficient) {
                Node<T>* temp = current->_next;
                current->_next = current->_next->_next;
                if (temp == _head) {
                    _head = _head->_next;
                }
                delete temp;
            }
            else {
                current = current->_next;
            }
        }

        if (_head && _head->_cofficient == node._cofficient) {
            pop_head();
        }
    }

    template<typename T>
    T LinkedList<T>::evaluate_at(T x) const {
        if (!_head) {
            cerr << "List is empty." << endl;
            return 0;
        }

        Node<T>* current = _head;
        T result = 0;
        do {
            result += current->_cofficient * pow(x, current->_power);
            current = current->_next;
            current->_power;
        } while (current != _head);

        return result;
    }

    template<typename T>
    void LinkedList<T>::print_coeff() const {
        if (!_head) {
            cout << "List is empty." << endl;
            return;
        }

        Node<T>* current = _head;
        int exponent = 0;

        do {
            if (current->_cofficient != 0) {
                if (exponent == 0) {
                }
                else {
                    cout << (current->_cofficient > 0 ? "+" : "") << current->_cofficient << "*x^" << exponent;
                }
            }
            current = current->_next;
            exponent++;
        } while (current != _head);

        cout << endl;
    }
}