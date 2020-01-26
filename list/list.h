#ifndef __LIST_H_
#define __LIST_H_

#include<iostream>
#include<cmath>

#include"node.h"

using namespace std;

#define Rank int

// doubly linked list with header and trailer
template <typename T>
class List {
    private:
        Pos(T) header;
        Pos(T) trailer;
        int _size;
    protected:
        void init();
        void copy_from(const List<T> &list, Rank rank, int n);
    public:
        List();
        List(const List<T> &list);
        List(const List<T> &list, Rank low, Rank high);
        ~List();
        Pos(T) first() const;
        Pos(T) last() const;
        int size();
        bool empty();
        void insert(Rank rank, T elem);
        void append(T elem);
        void clear();

        T& operator [](int rank);
        friend ostream& operator <<(ostream &os, List<T> &list) {
            cout << "[ ";
            Pos(T) node = list.header;
            for (int i = 0; i < list._size; i++) {
                node = node->next;
                cout << node->data << " ";
            }
            cout << "]" << endl;
            return os;
        }
};

template <typename T>
void List<T>::init() {
    header = new Node<T>;
    trailer = new Node<T>;
    header->pre = nullptr;
    header->next = trailer;
    trailer->pre = header;
    trailer->next = nullptr;
    _size = 0;
}

/*
 * Copy n elements starting from rank of list
 */
template <typename T>
void List<T>::copy_from(const List<T> &list, Rank rank, int n) {
    if (_size) {
        this->clear();
    }
 
    if (rank >= list._size || rank < 0) {
        throw "Cannot copy starting from where out of index";
    }

    Pos(T) node = list.first();
    for (int i = 0; i < rank; i++) {
        node = node->next;
    }
    n = (rank + n) <= list._size ? n : (list._size - rank);
    for (int i = 0; i < n; i++) {
        this->append(node->data);
        node = node->next;
    }
}

template <typename T>
List<T>::List() {
    init();
}

template <typename T>
List<T>::List(const List<T> &list) {
    init();
    copy_from(list, 0, list._size);
}

// [low, high)
template <typename T>
List<T>::List(const List<T> &list, Rank rank, int n) {
    init();
    copy_from(list, rank, n);
}

template <typename T>
List<T>::~List() {
    if (header) {
        delete[] header;
    }
    if (trailer) {
        delete[] trailer;
    }
}

template <typename T>
Pos(T) List<T>::first() const {
    return header->next;
}

template <typename T>
Pos(T) List<T>::last() const {
    return trailer->pre;
}

template <typename T>
int List<T>::size() {
    return _size;
}

template <typename T>
bool List<T>::empty() {
    return !_size;
}


/*
 * Args:
 *   elem: target element
 *   pos: position
 *     pos <= 0: insert as the first element
 *     0 < pos < _size: place at position pos
 *     pos >= _size: insert as the last element
 */
template <typename T>
void List<T>::insert(Rank rank, T elem) {
    _size += 1;
    if (rank <= 0) {
        Pos(T) node = new Node<T>(elem, header, header->next);
        header->next->pre = node;
        header->next = node;
    } else if (rank >= _size) {
        Pos(T) node = new Node<T>(elem, trailer->pre, trailer);
        trailer->pre->next = node;
        trailer->pre = node;
    } else {
        Pos(T) pre_node = header;
        for (int i = 0; i < rank; i++) {
            pre_node = pre_node->next;
        }
        Pos(T) node = new Node<T>(elem, pre_node, pre_node->next);
        pre_node->next->pre = node;
        pre_node->next = node;
    };
}

template <typename T>
void List<T>::clear() {
    if (!_size) {
        return;
    }

    Pos(T) node = header;
    for (int i = 0; i < _size; i++) {
        node = node->next;
        // cout << node->data << endl;
        delete node;
    }
    header->next = trailer;
    trailer->pre = header;
    _size = 0;
}

// Append elem to the end of the list
template <typename T>
void List<T>::append(T elem) {
    Pos(T) node = new Node<T>(elem, trailer->pre, trailer);
    trailer->pre->next = node;
    trailer->pre = node;
    _size += 1;
}

// Support negative rank access
template <typename T>
T& List<T>::operator [](int rank) {
    if (rank >= _size || rank < -_size) {
        throw "IndexError: list index out of range";
    } else if (rank >= 0) {
        Pos(T) node = header;
        for (int i = 0; i <= rank; i++) {
            node = node->next;
        }
        return node->data;
    } else {
        Pos(T) node = trailer;
        rank *= -1;
        for (int i = 0; i < rank; i++) {
            node = node->pre;
        }
        return node->data;
    }
}

#endif // __LIST_H_
