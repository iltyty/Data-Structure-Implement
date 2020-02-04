#ifndef __SPLAY_H_
#define __SPLAY_H_

#include "bstree.h"

// Splay tree data structure

template <typename T>
class Splay: public BST<T> {
    protected:
        BinPos(T) splay(BinPos(T) v);
    public:
        BinPos(T)& search(const T &e);
        BinPos(T)& insert(const T &e);
        void remove(const T &e);
};

// Stretch v to the root of the splay tree
template <typename T>
BinPos(T) Splay<T>::splay(BinPos(T) v) {
    if (!v) {
        return nullptr;
    }

    BinPos(T) p;
    BinPos(T) g;
    while ((p = v->parent) && (g = p->parent)) {
        // New parent of v after splay
        BinPos(T) gg = g->parent;

        if (v->is_lchild()) {
            if (p->is_lchild()) {
                g->attach_lchild(p->rchild);
                p->attach_lchild(v->rchild);
                p->attach_rchild(g);
                v->attach_rchild(p);
            } else {
                g->attach_rchild(v->lchild);
                p->attach_lchild(v->rchild);
                v->attach_lchild(g);
                v->attach_rchild(p);
            }
        } else {
            if (p->is_lchild()) {
                p->attach_rchild(v->lchild);
                g->attach_lchild(v->rchild);
                v->attach_lchild(p);
                v->attach_rchild(g);
            } else {
                g->attach_rchild(p->lchild);
                p->attach_lchild(g);
                p->attach_rchild(v->lchild);
                v->attach_lchild(p);
            }
        }

        if (gg) {
            if (g == gg->lchild) {
                gg->attach_lchild(v);
            } else {
                gg->attach_rchild(v);
            }
        } else {
            v->parent = nullptr;
        }
        this->update_height(g);
        this->update_height(p);
        this->update_height(v);
    }

    // After the splay, there must be: g == nullptr
    if (p) {
        // p is the root node, perform a single rotation
        if (v->is_lchild()) {
            p->attach_lchild(v->rchild);
            v->attach_rchild(p);
        } else {
            p->attach_rchild(v->lchild);
            v->attach_lchild(p);
        }
        this->update_height(p);
        this->update_height(v);
    }
    v->parent = nullptr;
    return v;
}

template <typename T>
BinPos(T)& Splay<T>::search(const T &e) {
    BinPos(T) x = this->search_in(e, this->_root, this->_hot = nullptr);

    // Whether the search succeeded or failed, the
    // last accessed node will be splayed to the root
    this->_root = splay(x ? x : this->_hot);
    return this->_root;
}

template <typename T>
BinPos(T)& Splay<T>::insert(const T &e) {
    if (!this->_root) {
        // The tree is currently empty
        this->_root = new BinNode<T>(e);
        this->_size++;
        return this->_root;
    }

    BinPos(T) &x = this->search(e);

    if (x->data == e) {
        // Prohibit repeat element
        return x;
    }

    this->_size++;
    BinPos(T) v = new BinNode<T>(e);
    if (e > x->data) {
        // Insert e as rchild
        v->attach_lchild(x);
        v->attach_rchild(x->rchild);
        x->rchild = nullptr;
    } else {
        // Insert e as lchild
        v->attach_lchild(x->lchild);
        v->attach_rchild(x);
        x->lchild = nullptr;
    }
    this->update_height_above(x);

    // Set v as the new root node
    x = v;
    return x;
}

template <typename T>
void Splay<T>::remove(const T &e) {
    if (!this->_root) {
        return;
    }

    BinPos(T) &x = search(e);
    BinPos(T) p = x;
    if (x->data != e) {
        // Search failed, e does not exist, no need to remove
        return;
    }

    this->_size--;
    if (!x->lchild) {
        x = x->rchild;
        if (x) {
            x->parent = nullptr;
        }
    } else if (!x->rchild) {
        x = x->lchild;
        if (x) {
            x->parent = nullptr;
        }
    } else {
        // Cut the right subtree temporarily
        BinPos(T) rchild = x->rchild;
        x->rchild = nullptr;
        // Change the root to the original left child
        x = x->lchild;
        x->parent = nullptr;
        // Search e in the new tree (will fail for sure)
        search(e);
        // At this time, the new root will be the node
        // that is largest in the original left subtree
        // Splice the original right subtree
        x->attach_rchild(rchild);
    }
    delete p;
    if (x) {
        this->update_height(x);
    }
}


#endif // __SPLAY_H_
