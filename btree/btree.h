#ifndef __BTREE_H_
#define __BTREE_H_

#include <cmath>

#include "btnode.h"
#include "../stack/stack.h"

template <typename T> class BTree {
    private:
        int _size;
        int _order;
        BTPos(T) _hot;
        BTPos(T) _root;
    protected:
        bool has_overflowed(BTPos(T)&);
        bool has_underflowed(BTPos(T)&);
        void handle_overflow(BTPos(T)&);
        void handle_underflow(BTPos(T)&);
    public:
        BTree(int order);
        ~BTree();

        int size() const;
        int order() const;
        BTPos(T) root() const;
        bool empty() const;

        BTPos(T) search(const T &e);
        BTPos(T) insert(const T &e);
        bool remove(const T &e);

        template <typename VST> void traverse_in(VST, BTPos(T));
};

template <typename T>
BTree<T>::BTree(int order)
    : _size(0), _order(order), _hot(nullptr) {
    _root = new BTNode<T>();
}

// TODO: destructor
template <typename T>
BTree<T>::~BTree() {
    if (_root) {
        delete _root;
    }
}

template <typename T>
int BTree<T>::size() const { return _size; }

template <typename T>
int BTree<T>::order() const { return _order; }

template <typename T>
BTPos(T) BTree<T>::root() const { return _root; }

template <typename T>
bool BTree<T>::empty() const { return !_size; }

template <typename T>
BTPos(T) BTree<T>::search(const T &e) {
    // Tree is empty
    if (!_root) {
        return nullptr;
    }

    _hot = nullptr;
    BTPos(T) x = _root;
    while (x) {
        // Sequential search is faster than binary search
        // when the dataset is relatively small
        int rank = x->keys.search_seq(e);
        if (rank >= 0 && x->keys[rank] == e) {
            // Search succeeded
            return x;
        }

        _hot = x;
        // Determined by the semantic rule of search interface
        x = x->childs[rank + 1];
    }
    // Search failed
    return nullptr;
}

template <typename T>
BTPos(T) BTree<T>::insert(const T &e) {
    BTPos(T) x = search(e);
    if (x) {
        // No repeat element
        return x;
    }

    _size++;
    Rank r = _hot->keys.search_seq(e);
    _hot->keys.insert(r + 1, e);
    _hot->childs.insert(_hot->childs.size(), nullptr);

    if (has_overflowed(_hot)) {
        handle_overflow(_hot);
    }

    return _hot;
}

template <typename T>
bool BTree<T>::remove(const T &e) {
    BTPos(T) x = search(e);
    if (!x) {
        // e does not exist, no need to remove
        return false;
    }

    Rank r = x->keys.search_seq(e);
    x->keys.remove(r);

    if (has_overflowed(x)) {
        handle_underflow(x);
    }

    return true;
}

template <typename T>
bool BTree<T>::has_overflowed(BTPos(T) &x) {
    return x && x->keys.size() >= _order;
}

template <typename T>
bool BTree<T>::has_underflowed(BTPos(T) &x) {
    return x && x->key.size() < ceil(_order / 2) - 1;
}

template <typename T>
void BTree<T>::handle_overflow(BTPos(T) &x) {
    while (has_overflowed(x)) {
        int median = _order / 2;
        BTPos(T) parent = x->parent;
        if (!parent) {
            // x is the root node
            parent = new BTNode<T>();
            _root = parent;
        }
        // Move the key code keys[median] one level up
        int r = parent->keys.search_seq(x->keys[median]);
        parent->keys.insert(r + 1, x->keys[median]);
        parent->childs.insert(r + 2, nullptr);
        // Split the current node
        x->split(median, r + 1, r + 2, parent);
        x = parent;
    }
}

// In-order traversal of subtree x
template <typename T>
template <typename VST>
void BTree<T>::traverse_in(VST visit, BTPos(T) x) {
    Stack<BTPos(T)> stack;
    if (!x) {
        return;
    }

    int size = x->keys.size();
    for (int i = 0; i < size; i++) {
        traverse_in(visit, x->childs[i]);
        visit(x->keys[i]);
    }
    traverse_in(visit, x->childs[size]);
}

#endif // __BTREE_H_
