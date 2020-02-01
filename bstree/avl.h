#ifndef __AVL_H_
#define __AVL_H_

#include "bstree.h"

// x: BinPos(T)
#define BalFac(x)                               \
    (stature((x)->lchild) - stature((x)->rchild))
#define Balanced(x)                             \
    (-2 < BalFac(x) && BalFac(x) < 2)

template <typename T> class AVL: public BST<T> {
    protected:
        void rotate_at(BinPos(T) x);
        void rotate_ll(BinPos(T) g, BinPos(T) p, BinPos(T) x, bool flag);
        void rotate_lr(BinPos(T) g, BinPos(T) p, BinPos(T) x, bool flag);
        void rotate_rl(BinPos(T) g, BinPos(T) p, BinPos(T) x, bool flag);
        void rotate_rr(BinPos(T) g, BinPos(T) p, BinPos(T) x, bool flag);
    public:
        BinPos(T)& insert(const T &e);
        void remove(const T &e);
};

// Grandfather of x is imbalanced, rebalance
template <typename T>
void AVL<T>::rotate_at(BinPos(T) x) {
    BinPos(T) p = x->parent;
    BinPos(T) g = p->parent;

    bool flag = false;
    if (!g->parent) {
        // g is the root node
        flag = true;
    }

    if (x->is_lchild()) {
        if (p->is_lchild()) {
            /*   g
                / \
               p  ...
              / \
             x  ...  */
            rotate_ll(g, p, x, flag);
        } else {
            /*   g
                / \
               ... p
                  / \
                 x  ...
                / \
              ... ...    */
            rotate_lr(g, p, x, flag);
        }
    } else {
        if (p->is_lchild()) {
            /*     g
             *    / \
             *   p  ...
             *  / \
             * ... x
             *    / \
             *  ... ...  */
            rotate_rl(g, p, x, flag);
        } else {
            /*     g
             *    / \
             *  ...  p
             *      / \
             *     ... x */
            rotate_rr(g, p, x, flag);
        }
    }
}

template <typename T>
void AVL<T>::rotate_ll(BinPos(T) g, BinPos(T) p, BinPos(T) x, bool flag) {
    // Rotate clockwise around g
    g->lchild = p->rchild;
    if (p->rchild) {
        p->rchild->parent = g;
    }
    p->rchild = g;
    p->parent = g->parent;
    if (flag) {
        this->_root = p;
    } else {
        if (g->is_lchild()) {
            g->parent->lchild = p;
        } else {
            g->parent->rchild = p;
        }
    }
    g->parent = p;
    this->update_height(g);
    this->update_height(p);
}

template <typename T>
void AVL<T>::rotate_lr(BinPos(T) g, BinPos(T) p, BinPos(T) x, bool flag) {
    // Rotate clockwise around p
    p->lchild = x->rchild;
    if (x->rchild) {
        x->rchild->parent = p;
    }
    x->rchild = p;
    x->parent = p->parent;
    p->parent = x;
    // Then rotate counterclockwise around g
    g->rchild = x->lchild;
    if (x->lchild) {
        x->lchild->parent = g;
    }
    x->lchild = g;
    x->parent = g->parent;
    if (flag) {
        this->_root = x;
    } else {
        if (g->is_lchild()) {
            g->parent->lchild = x;
        } else {
            g->parent->rchild = x;
        }
    }
    g->parent = x;
    this->update_height(g);
    this->update_height(p);
    this->update_height(x);
}

template <typename T>
void AVL<T>::rotate_rl(BinPos(T) g, BinPos(T) p, BinPos(T) x, bool flag) {
    // Rotate counterclockwise around p
    p->rchild = x->lchild;
    if (x->lchild) {
        x->lchild->parent = p;
    }
    x->lchild = p;
    x->parent = p->parent;
    p->parent = x;
    // Then rotate clockwise around g
    g->lchild = x->rchild;
    if (x->rchild) {
        x->rchild->parent = g;
    }
    x->rchild = g;
    x->parent = g->parent;
    if (flag) {
        this->_root = x;
    } else {
        if (g->is_lchild()) {
            g->parent->lchild = x;
        } else {
            g->parent->rchild = x;
        }
    }
    g->parent = x;
    this->update_height(g);
    this->update_height(p);
    this->update_height(x);
}

template <typename T>
void AVL<T>::rotate_rr(BinPos(T) g, BinPos(T) p, BinPos(T) x, bool flag) {
    // Rotate counterclockwise around g
    g->rchild = p->lchild;
    if (p->lchild) {
        p->lchild->parent = g;
    }
    p->lchild = g;
    p->parent = g->parent;
    if (flag) {
        this->_root = p;
    } else {
        if (g->is_lchild()) {
            g->parent->lchild = p;
        } else {
            g->parent->rchild = p;
        }
    }
    g->parent = p;
    this->update_height(g);
    this->update_height(p);
}

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
   
    for (BinPos(T) g = x->parent; g; g = g->parent) {
        if (!Balanced(g)) {
            // Imbalanced, perform rotation operation
            rotate_at(g->taller_child()->taller_child());
            // Need at most only one rebalance
            break;
        } else {
            // Balanced, update height of node g only
            g->height = 1 + this->max(stature(g->lchild), stature(g->rchild));
        }
    }

    return x;
}

template <typename T>
void AVL<T>::remove(const T &e) {
   
}


#endif // __AVL_H_
