#ifndef __NODE_H_
#define __NODE_H_

#include <iostream>
using namespace std;

#define Pos(T) Node<T>*

template <typename T>
struct Node {
    T data;
    // predecessor
    Pos(T) pre;
    // successor
    Pos(T) next;
    // constructer for header and trailer
    Node() {}
    // default constructor
    Node(T data, Pos(T) pre, Pos(T) next)
        : data(data), pre(pre), next(next) {}
    // Insert as predecessor
    Pos(T) insert_pre(T const &elem);
    // Insert as successor
    Pos(T) insert_next(T const &elem);
    // Overload operator <<
    friend ostream& operator << (ostream &os, Node<T> &node) {
        cout << node.data << " ";
        return os;
    }
};

#endif // __NODE_H_
