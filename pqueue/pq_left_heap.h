#ifndef __PQ_LEFT_HEAP_H_
#define __PQ_LEFT_HEAP_H_

#include "pq.h"
#include "../bintree/bin_tree.h"

template <typename T>
class PQ_LeftHeap: public PQ<T>, public BinTree<T> {
    protected:
        BinPos(T) merge(BinPos(T) a, BinPos(T) b);
    public:
        T get();
        T enqueue(T e);
        T dequeue();
};

template <typename T>
BinPos(T) PQ_LeftHeap<T>::merge(BinPos(T) a, BinPos(T) b) {
    if (!a) {
        return b;
    }
    if (!b) {
        return a;
    }
    if (a->npl < b->npl) {
        BinPos(T) tmp = a;
        a = b;
        b = tmp;
    }

    a->attach_rchild(merge(a->rchild, b));

    // Has violated the leftist property of leftist heap
    if (!a->lchild || a->lchild->npl < a->rchild->npl) {
        BinPos(T) tmp = a->lchild;
        a->lchild = a->rchild;
        a->rchild = tmp;
    }

    // Update npl of a
    a->npl = a->rchild ? a->rchild->npl + 1 : 1;

    return a;
}

template <typename T> T PQ_LeftHeap<T>::get() {
    return this->_root->data;
}

template <typename T> T PQ_LeftHeap<T>::enqueue(T e) {
    BinPos(T) x = new BinNode<T>(e);
    this->_root = merge(this->_root, x);
    this->_root->parent = nullptr;
    this->_size++;

    return e;
}

template <typename T> T PQ_LeftHeap<T>::dequeue() {
    T max = this->_root->data;

    BinPos(T) lc = this->_root->lchild;
    BinPos(T) rc = this->_root->rchild;

    delete this->_root;
    this->_root = merge(lc, rc);
    if (this->_root) {
        this->_root->parent = nullptr;
    }
    this->_size--;

    return max;
}


#endif // __PQ_LEFT_HEAP_H_
