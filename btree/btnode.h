#ifndef __BTNODE_H_
#define __BTNODE_H_

#include <cmath>

#include "../vector/vector.h"

#define BTPos(T) BTNode<T> *

template <typename T> struct BTNode {
    BTPos(T) parent;
    // n key codes
    Vector<T> keys;
    // n+1 references
    Vector<BTPos(T)> childs;

    BTNode() {
        parent = nullptr;
        childs.insert(0, nullptr);
    }

    BTNode(const T &e) {
        parent = nullptr;
        keys.insert(keys.size(), e);
        childs.insert(0, nullptr);
        childs.insert(1, nullptr);
    }

    BTNode(const T &e, BTPos(T) p) {
        parent = p;
        keys.insert(keys.size(), e);
        childs.insert(0, nullptr);
        childs.insert(1, nullptr);
    }

    // Duplicate node x
    BTNode(const BTNode<T> &x)
        : parent(x.parent), keys(x.keys), childs(x.childs) {}

    BTNode(BTNode<T> &x, int low, int high) {
        parent = x.parent;
        keys = Vector<T>(x.keys, low, high);
        childs = Vector<BTPos(T)>(x.childs, low, high + 1);
    }

    // In-order successor of key code keys[r]
    // Assert: x is a non-leaf node, r is legal
    BTPos(T) succ(int r) {
        BTPos(T) p = this->childs[r + 1];
        while (p->childs[0]) {
            p = p->childs[0];
        }
        return p;
    }

    // Get the index of the current node
    // in its parent's childs vector
    int get_index() {
        if (!this->parent) {
            return -1;
        }

        Vector<BTPos(T)> childs = this->parent->childs;
        int size = childs.size();
        for (int i = 0; i < size; i++) {
            if (childs[i] == this) {
                return i;
            }
        }
        return -1;
    }

    bool is_leaf_node() {
        return !this->childs[0];
    }

    // Attach node x as the rth child
    bool attach_child(int r, BTPos(T) x) {
        // Illegal r
        if (r < 0 || r > childs.size()) {
            return false;
        }

        childs[r] = x;
        x->parent = this;
        return true;
    }

    bool able_to_lend(int order) {
        return keys.size() >= ceil((double) order / 2);
    }

    // r indicates the index of the current
    // node in its parent's childs vector
    bool has_left_sibling(int r) {
        if (!this->parent) {
            return false;
        }

        return (r - 1) >= 0;
    }

    // r: ditto
    bool has_right_sibling(int r) {
        if (!this->parent) {
            return false;
        }

        return (r + 1) < this->parent->childs.size();
    }

    /*
     * Divide the current node into two
     * Args:
     *   m: where to split in vector keys
     *   l: index of the left node in parent->childs
     *   r: index of the right node in parent->childs
     *   parent: parent of the two new nodes
     * Left child:
     *   keys: this->keys[0, m)
     *   childs: this->childs[0, m]
     * Right child:
     *   keys: this->keys(m, -1]
     *   childs: (m, -1]
     */
    void split(int m, int l, int r, BTPos(T) &parent) {
        BTPos(T) lchild = new BTNode<T>(*this, 0, m);
        BTPos(T) rchild = new BTNode<T>(*this, m + 1, this->keys.size());

        if (lchild->childs[0]) {
            for (int i = 0; i <= m; i++) {
                lchild->childs[i]->parent = lchild;
            }

            int size = rchild->childs.size();
            for (int i = 0; i < size; i++) {
                rchild->childs[i]->parent = rchild;
            }
        }

        parent->attach_child(l, lchild);
        parent->attach_child(r, rchild);
        delete this;
    }
};

#endif // __BTNODE_H_
