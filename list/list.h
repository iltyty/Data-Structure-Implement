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
        void swap(T &a, T &b);
    public:
        List();
        List(const List<T> &list);
        List(const List<T> &list, Rank low, int n);
        ~List();
        Pos(T) first() const;
        Pos(T) last() const;
        Pos(T) get(Rank n) const;

        int size();
        bool empty();

        void insert(Rank rank, T elem);
        void append(T elem);
        T remove(T elem);
        void clear();

        void selection_sort(Rank rank, int n, bool reverse=false);
        void insertion_sort(Rank rank, int n, bool reverse=false);
        void sort(bool reverse=false);

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
        throw "IndexError: Cannot copy starting from where out of index";
    }

    Pos(T) node = list.get(rank);
    n = (rank + n) <= list._size ? n : (list._size - rank);
    for (int i = 0; i < n; i++) {
        this->append(node->data);
        node = node->next;
    }
}

template <typename T>
void List<T>::swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
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
        delete header;
    }
    if (trailer) {
        delete trailer;
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
Pos(T) List<T>::get(Rank n) const {
    if (n < 0 || n > _size) {
        return nullptr;
    }

    Pos(T) node = header->next;
    for (int i = 0; i < n; i++) {
        node = node->next;
    }
    return node;
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


/*
 * Remove elememt elem
 * Throw an error if elem is not in list
 * Delete the first one when multiple elem exists
 */
template <typename T>
T List<T>::remove(T elem) {
    Pos(T) node = header;
    for (int i = 0; i < _size; i++) {
        node = node->next;
        if (node->data == elem) {
            // delete current node and return
            node->next->pre = node->pre;
            node->pre->next = node->next;
            delete node;
            _size--;
            return elem;
        }
    }
    // elem does not exist
    throw "ValueError: list.remove(x): x not in list";
}

template <typename T>
void List<T>::clear() {
    if (!_size) {
        return;
    }

    Pos(T) node = header;
    for (int i = 0; i < _size; i++) {
        node = node->next;
        delete node;
    }

    _size = 0;
    Pos(T) header_tmp = header;
    Pos(T) trailer_tmp = trailer;
    header = nullptr;
    trailer = nullptr;
    delete header_tmp;
    delete trailer_tmp;
}

// Sort the total n elements in the list starting at position
// rank using selection sort (unstable, input insensitive)
template <typename T>
void List<T>::selection_sort(int rank, int n, bool reverse) {
    if (!_size) {
        return;
    }

    if (rank >= _size || rank < 0) {
        throw "IndexError: Cannot sort starting from where out of index";
    }

    Pos(T) node = get(rank);
    n = (rank + n) <= _size ? n : _size - rank;
    for (int i = 0; i < n - 1; i++) {
        // n-1 times
        Pos(T) p = node->next;
        Pos(T) min = node;
        bool flag = false;
        for (int j = i; j < n - 1; j++) {
            if (reverse) {
                if (p->data > min->data) {
                    min = p;
                    flag = true;
                }
            } else {
                if (p->data < min->data) {
                    min = p;
                    flag = true;
                }
            }
            p = p->next;
        }
        if (flag) {
            swap(node->data, min->data);
        }
        node = node->next;
    }
}

// Insertion sort (stable, input sensitive)
template <typename T>
void List<T>::insertion_sort(Rank rank, int n, bool reverse) {
    if (!_size) {
        return;
    }

    if (rank >= _size || rank < 0) {
        throw "IndexError: Cannot sort starting from where out of index";
    }

    Pos(T) node = get(rank);
    Pos(T) base = node;
    n = (rank + n) <= _size ? n : _size - rank;
    for (int i = 1; i < n; i++) {
        node = node->next;
        Pos(T) p = node;
        while (p != base) {
            if (reverse) {
                if (p->data > p->pre->data) {
                    swap(p->data, p->pre->data);
                } else {
                    break;
                }
            } else {
                if (p->data < p->pre->data) {
                    swap(p->data, p->pre->data);
                } else {
                    break;
                }
            }
            p = p->pre;
        }
    }
}

// Sort the whole list
template <typename T>
void List<T>::sort(bool reverse) {
    insertion_sort(0, _size, reverse);
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
