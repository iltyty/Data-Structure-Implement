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
        void handle_underflow(BTPos(T)&, T);

        bool try_to_lend_from_sibling(BTPos(T) x, int r);
        void borrow_from_left_sibling(BTPos(T) x, BTPos(T) sibling, int r);
        void borrow_from_right_sibling(BTPos(T) x, BTPos(T) sibling, int r);
        void merge_left_sibling(BTPos(T) x, BTPos(T) sibling, int r);
        void merge_right_sibling(BTPos(T) x, BTPos(T) sibing, int r);
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
    if (x->is_leaf_node()) {
        // x is a leaf node, delete e directly
        x->keys.remove(r);
        x->childs.remove(0);
    } else {
        // Find its in-order successor in a leaf node
        BTPos(T) succ = x->succ(r);
        // Replace e in x with its successor key code
        x->keys[r] = succ->keys[0];
        // Delete the successor in succ
        succ->keys.remove(0);
        succ->childs.remove(0);
        x = succ;
    }

    if (has_underflowed(x)) {
        handle_underflow(x, e);
    }

    _size--;
    return true;
}

template <typename T>
bool BTree<T>::has_overflowed(BTPos(T) &x) {
    return x && x->keys.size() >= _order;
}

template <typename T>
bool BTree<T>::has_underflowed(BTPos(T) &x) {
    return x && x->keys.size() < ceil((double) _order / 2) - 1;
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

/*
 * 1. Check if the siblings are able to lend out a key code
 * 2. If so, move a key from the parent to the node itself, then
 *    move a key from the sibling to the parent and finish
 * 3. Otherwise, merge the node, its sibling and a key from the parent.
 * 4. Then check whether the parent has underflowed or not.
 * 5. If so, move up and handle it.
 * 6. Otherwise, the handle process then is finished
 */
template <typename T>
void BTree<T>::handle_underflow(BTPos(T) &x, T e) {
    while (has_underflowed(x)) {
        BTPos(T) parent = x->parent;
        if (!parent) {
            if (x->keys.empty()) {
                // After a series of merge operation, the only key
                // in the root node has been moved to its child
                // At this moment, the root node has only one child
                _root = x->childs[0];
                if (x->childs[0]) {
                    x->childs[0]->parent = nullptr;
                }
                delete x;
                return;
            }
            return;
        }

        int r = x->get_index();
        bool res = try_to_lend_from_sibling(x, r);
        if (res) {
            return; // Borrowed successfully
        }

        BTPos(T) sibling;
        if (x->has_left_sibling(r)) {
            sibling = x->parent->childs[r - 1];
            merge_left_sibling(x, sibling, r);
        } else {
            // x must have a left or right sibling
            sibling = x->parent->childs[r + 1];
            merge_right_sibling(x, sibling, r);
        }

        x = parent;
    }
}

// At this time:
// x->parent->childs[r] == x
// x->parent->childs[r - 1] (if existed) == the left sibling
// x->parent->chlids[r + 1] (if existed) == the right sibling
template <typename T>
bool BTree<T>::try_to_lend_from_sibling(BTPos(T) x, int r) {
    BTPos(T) sibling;
    if (x->has_left_sibling(r)) {
        // x has left sibling
        sibling = x->parent->childs[r - 1];
        if (sibling->able_to_lend(_order)) {
            borrow_from_left_sibling(x, sibling, r);
            return true;
        }
    }

    if (x->has_right_sibling(r)) {
        // x has right sibling
        sibling = x->parent->childs[r + 1];
        if (sibling->able_to_lend(_order)) {
            borrow_from_right_sibling(x, sibling, r);
            return true;
        }
    }
    return false;
}

template <typename T>
void BTree<T>::borrow_from_left_sibling(BTPos(T) x, BTPos(T) sibling, int r) {
    T pd = x->parent->keys[r - 1];
    T sd = sibling->keys[sibling->keys.size() -1];

    int last = sibling->childs.size() - 1;
    x->keys.insert(0, pd);
    x->childs.insert(0, sibling->childs[last]);
    if (sibling->childs[last]) {
        sibling->childs[last]->parent = x;
    }

    x->parent->keys[r - 1] = sd;

    sibling->keys.remove(sibling->keys.size() - 1);
    sibling->childs.remove(sibling->childs.size() - 1);
}

template <typename T>
void BTree<T>::borrow_from_right_sibling(BTPos(T) x, BTPos(T) sibling, int r) {
    T pd = x->parent->keys[r];
    T sd = sibling->keys[0];

    x->keys.append(pd);
    x->childs.append(sibling->childs[0]);
    if (sibling->childs[0]) {
        sibling->childs[0]->parent = x;
    }

    x->parent->keys[r] = sd;

    sibling->keys.remove(0);
    sibling->childs.remove(0);
}

template <typename T>
void BTree<T>::merge_left_sibling(BTPos(T) x, BTPos(T) sibling, int r) {
    sibling->keys.append(x->parent->keys[r - 1]);
    sibling->keys.concat(x->keys);
    int size = x->childs.size();
    for (int i = 0; i < size; i++) {
        if (x->childs[i]) {
            x->childs[i]->parent = sibling;
        }
        sibling->childs.append(x->childs[i]);
    }

    x->parent->keys.remove(r - 1);
    x->parent->childs.remove(r);
    delete x;
}

template <typename T>
void BTree<T>::merge_right_sibling(BTPos(T) x, BTPos(T) sibling, int r) {
    x->keys.append(x->parent->keys[r]);
    x->keys.concat(sibling->keys);
    int size = sibling->childs.size();
    for (int i = 0; i < size; i++) {
        if (sibling->childs[i]) {
            sibling->childs[i]->parent = x;
        }
        x->childs.append(sibling->childs[i]);
    }

    x->parent->keys.remove(r);
    x->parent->childs.remove(r + 1);
    delete sibling;
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
