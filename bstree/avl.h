#ifndef __AVL_H_
#define __AVL_H_

#include "bstree.h"

// x: BinPos(T)
#define BalFac(x)                               \
    (stature((x)->lchild) - stature((x)->rchild))
#define Balanced(x)                             \
    (-2 < BalFac(x) && BalFac(x) < 2)

template <typename T> class AVL: public BST<T> {
    public:
        BinPos(T)& insert(const T &e);
        void remove(const T &e);
};

template <typename T>
BinPos(T)& AVL<T>::insert(const T &e) {
    BinPos(T) &x = this->search(e);
    // No repeat element
    if (x) {
        return x;
    }

    // insert
    x = new BinNode<T>(e, this->_hot);
    this->_size++;

    // The lowest one of all ancestor nodes is
    // not lower than the grandfather node
   
    for (BinPos(T) g = this->_hot; g; g = g->parent) {
        if (!Balanced(g)) {
            // Imbalanced, perform rotation operation
            this->rotate_at(g->taller_child()->taller_child());
            // Need at most only one rebalance
            break;
        } else {
            // Balanced, update height of node g only
            this->update_height(g);
        }
    }

    return x;
}

template <typename T>
void AVL<T>::remove(const T &e) {
    BinPos(T) &x = this->search(e);
    if (!x) {
        // e does not exist
        return;
    }

    this->remove_at(x, this->_hot);
    this->_size--;

    // x->parent may be nullptr
    for (BinPos(T) g = this->_hot; g; g = g->parent) {
        if (!Balanced(g)) {
            this->rotate_at(g->taller_child()->taller_child());
        }
        this->update_height(g);
    }
}


#endif // __AVL_H_
