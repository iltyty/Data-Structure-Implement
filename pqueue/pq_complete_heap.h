#ifndef __PQ_COMPLETE_HEAP_H_
#define __PQ_COMPLETE_HEAP_H_

#include <cmath>

#include "pq.h"
#include "../vector/vector.h"

// Priority queue data structure
template <typename T>
class PQ_ComplHeap: public PQ<T>, public Vector<T> {
    protected:
        int percolate_up(Rank r);
        int percolate_down(Rank r);
        int bigger_child(Rank r);
        void heapify(int n);
    public:
        PQ_ComplHeap() {}
        PQ_ComplHeap(T *a, int n);

        T get();
        T enqueue(T e);
        T dequeue();
};

template <typename T> PQ_ComplHeap<T>::PQ_ComplHeap(T *a, int n) {
    this->copy_from(a, 0, n);
    heapify(n);
}

template <typename T> void PQ_ComplHeap<T>::heapify(int n) {
    int r = floor((double) n / 2) - 1;
    for (int i = r; i >= 0; i--) {
        percolate_down(i);
    }
}

template <typename T> int PQ_ComplHeap<T>::percolate_up(Rank r) {
    int i;
    T *elems = this->_elem;
    while ((i = Parent(r)) >= 0 && elems[r] > elems[i]) {
        this->swap(elems[r], elems[i]);
        r = i;
    }
    return r;
}

template <typename T> int PQ_ComplHeap<T>::percolate_down(Rank r) {
    int i;
    T *elems = this->_elem;
    while ((i = bigger_child(r)) != -1) {
        this->swap(elems[r], elems[i]);
        r = i;
    }

    return r;
}

template <typename T> int PQ_ComplHeap<T>::bigger_child(Rank r) {
    int max = this->_elem[r];
    int res = -1;
    int i = LChild(r);
    int j = RChild(r);
    bool lc = i < this->_size;
    bool rc = j < this->_size;

    if (lc && this->_elem[i] > max) {
        max = this->_elem[i];
        res = i;
    }
    if (rc && this->_elem[j] > max) {
        max = this->_elem[j];
        res = j;
    }

    return res;
}

template <typename T> T PQ_ComplHeap<T>::get() {
    return this->_elem[0];
}

template <typename T> T PQ_ComplHeap<T>::enqueue(T e) {
    this->append(e);
    percolate_up(this->_size - 1);
    return e;
}

template <typename T> T PQ_ComplHeap<T>::dequeue() {
    T max = this->_elem[0];
    this->_elem[0] = this->_elem[--this->_size];
    percolate_down(0);
    return max;
}

#endif // __PQ_COMPLETE_HEAP_H_
