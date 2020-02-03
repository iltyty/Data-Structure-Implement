#ifndef __RBTREE_H_
#define __RBTREE_H_

#include "bstree.h"

template <typename T>
class RBTree: public BST<T> {
    protected:
        void update_height(BinPos(T) x);
        void update_height_above(BinPos(T) x);
        void handle_double_red(BinPos(T) x);
        void handle_black_uncle(BinPos(T) x);
        void handle_red_uncle(BinPos(T) x, BinPos(T) u);

    public:
        BinPos(T)& insert(const T &e);
        void remove(const T &e);
};

template <typename T>
void RBTree<T>::update_height(BinPos(T) x) {
    int max = this->max(stature(x->lchild), stature(x->rchild));
    x->height = (x->is_black()) ? (1 + max) : max;
}

template <typename T>
void RBTree<T>::update_height_above(BinPos(T) x) {
    while (x) {
        update_height(x);
        x = x->parent;
    }
}

template <typename T>
void RBTree<T>::handle_red_uncle(BinPos(T) p, BinPos(T) u) {
    p->color = RBColor::Black;
    u->color = RBColor::Black;
    p->parent->color = RBColor::Red;
    p->height++;
    u->height++;
}

template <typename T>
void RBTree<T>::handle_black_uncle(BinPos(T) x) {
    BinPos(T) r = this->rotate_at(x);

    r->color = RBColor::Black;
    r->lchild->color = RBColor::Red;
    r->rchild->color = RBColor::Red;

    r->height--;
    r->lchild->height--;
    r->rchild->height--;
}

template <typename T>
void RBTree<T>::handle_double_red(BinPos(T) x) {
    BinPos(T) p;
    BinPos(T) g;
    BinPos(T) u;
    while (x && (p = x->parent) && p->is_red()) {
        // At this time, x must have a grandfather node
        // Otherwise, its parent is the root node, which is black
        g = p->parent;
        bool flag = false;
        if (!g->parent) {
            flag = true;
        }

        // Uncle node of x
        u = (p->is_lchild()) ? g->rchild : g->lchild;
        if (!u || u->is_black()) {
            handle_black_uncle(x);
            return;
        } else {
            handle_red_uncle(p, u);
        }
        x = g;
        if (x == this->_root) {
            x->color = RBColor::Black;
            x->height++;
            return;
        }
    }
}

template <typename T>
BinPos(T)& RBTree<T>::insert(const T &e) {
    BinPos(T) &x = this->search(e);
    if (x) {
        return x;
    }

    this->_size++;
    // Initial height: -1
    x = new BinNode<T>(e, this->_hot, -1);

    if (x == this->_root) {
        x->color = RBColor::Black;
        x->height++;
    }

    handle_double_red(x);

    return x;
}

template <typename T>
void RBTree<T>::remove(const T &e) {

}

#endif // __RBTREE_H_
