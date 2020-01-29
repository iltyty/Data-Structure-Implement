#ifndef __BIN_TREE_H_
#define __BIN_TREE_H_

#include "../queue/queue.h"
#include "../stack/stack.h"
#include "../vector/vector.h"
#include "bin_node.h"

// Delete subtree rooted at node in a bottom-up manner
template <typename T> struct Delete {
    virtual void operator () (BinPos(T)& node) {
        if (!node->parent) {
            // root node
            delete node;
            return;
        }

        if (node->parent->lchild == node) {
            node->parent->lchild = nullptr;
        } else {
            node->parent->rchild = nullptr;
        }
        delete node;
    }
};

template <typename T> class BinTree {
    protected:
        int _size;
        BinPos(T) _root;

    protected:
        int max(int a, int b);

    public:
        BinTree();
        BinTree(T &e);
        BinTree(BinPos(T) root);

        void init(Vector<T>&);

        BinPos(T) root() const;
        int size() const;
        bool empty() const;
        void clear();
        void remove(BinPos(T) &node);

        void update_height(BinPos(T) x);
        BinPos(T) insert_lchild(BinPos(T) x, const T &elem);
        BinPos(T) insert_rchild(BinPos(T) x, const T &elem);

        // Preorder traverse
        template <typename VST> void traverse_pre(VST, BinPos(T));
        template <typename VST> void traverse_pre_recursive(VST, BinPos(T));
        template <typename VST> void traverse_pre_iteration_a(VST, BinPos(T));
        template <typename VST> void traverse_pre_iteration_b(VST, BinPos(T));
        template <typename VST>
        void visit_along_left_branch(VST &, BinPos(T), Stack<BinPos(T)> &);
        // In-order traverse
        template <typename VST> void traverse_in(VST, BinPos(T));
        template <typename VST> void traverse_in_recursive(VST, BinPos(T));
        template <typename VST> void traverse_in_iteration(VST, BinPos(T));
        void go_along_left_branch(BinPos(T), Stack<BinPos(T)> &);
        // Postorder traverse
        template <typename VST> void traverse_post(VST, BinPos(T));
        template <typename VST> void traverse_post_recursive(VST, BinPos(T));
        template <typename VST> void traverse_post_iteration(VST, BinPos(T));
        // Hierarchical traverse
        template <typename VST> void traverse_level(VST, BinPos(T));
};

template <typename T> int BinTree<T>::max(int a, int b) {
    return a > b ? a : b;
}

template <typename T> BinTree<T>::BinTree() : _size(0), _root(nullptr) {}

template <typename T> BinTree<T>::BinTree(T &e) {
    _size = 1;
    _root = new BinNode<T>(e, nullptr);
}

template <typename T>
BinTree<T>::BinTree(BinPos(T) root): _size(1), _root(root) {}

template <typename T> BinPos(T) BinTree<T>::root() const { return _root; }

template <typename T> int BinTree<T>::size() const { return _size; }

template <typename T> bool BinTree<T>::empty() const { return !_size; }

template <typename T> void BinTree<T>::clear() { remove(_root); }

template <typename T>
void BinTree<T>::remove(BinPos(T) &node) {
    if (!node) {
        return;
    }

    bool flag = false;
    if (node == _root) {
        flag = true;
    }

    _size -= node->size();
    traverse_post_iteration(Delete<T>(), node);
    if (flag) {
        _root = nullptr;
    }
}

// Update the height of subtree x and all its ancestor nodes
template <typename T> void BinTree<T>::update_height(BinPos(T) x) {
    // All the way up to the root node
    while (x) {
        int lheight = x->lchild ? x->lchild->height : 0;
        int rheight = x->rchild ? x->rchild->height : 0;
        x->height = 1 + max(lheight, rheight);
    }
}

template <typename T>
BinPos(T) BinTree<T>::insert_lchild(BinPos(T) x, const T &elem) {
    BinPos(T) lchild = x->insert_lchild(elem);
    // x already has a left child
    if (!lchild) {
        return nullptr;
    }
    _size++;
    update_height(x);
    return lchild;
}

template <typename T>
BinPos(T) BinTree<T>::insert_rchild(BinPos(T) x, const T &elem) {
    BinPos(T) rchild = x->insert_rchild(elem);
    // x already has a right child
    if (!rchild) {
        return nullptr;
    }
    _size++;
    update_height(x);
    return rchild;
}

template <typename T>
template <typename VST>
void BinTree<T>::traverse_pre(VST visit, BinPos(T) root) {
    traverse_pre_iteration_b(visit, root);
}

template <typename T>
template <typename VST>
void BinTree<T>::traverse_pre_recursive(VST visit, BinPos(T) root) {
    if (!root) {
        return;
    }

    visit(root);
    traverse_pre_recursive(visit, root->lchild);
    traverse_pre_recursive(visit, root->rchild);
}

template <typename T>
template <typename VST>
void BinTree<T>::traverse_pre_iteration_a(VST visit, BinPos(T) root) {
    if (!root) {
        return;
    }

    Stack<BinPos(T)> stack;
    stack.push(root);

    while (!stack.empty()) {
        root = stack.pop();
        visit(root);
        if (root->rchild) {
            stack.push(root->rchild);
        }
        if (root->lchild) {
            stack.push(root->lchild);
        }
    }
}

template <typename T>
template <typename VST>
void BinTree<T>::traverse_pre_iteration_b(VST visit, BinPos(T) root) {
    if (!root) {
        return;
    }

    Stack<BinPos(T)> stack;
    while (true) {
        visit_along_left_branch(visit, root, stack);
        if (stack.empty()) {
            return;
        }
        root = stack.pop();
    }
}

template <typename T>
template <typename VST>
void BinTree<T>::visit_along_left_branch(VST &visit, BinPos(T) root,
                             Stack<BinPos(T)> &stack) {
    while (root) {
        visit(root);
        stack.push(root->rchild);
        root = root->lchild;
    }
}

template <typename T>
template <typename VST>
void BinTree<T>::traverse_in(VST visit, BinPos(T) root) {
    traverse_in_iteration(visit, root);
}

template <typename T>
template <typename VST>
void BinTree<T>::traverse_in_recursive(VST visit, BinPos(T) root) {
    if (!root) {
        return;
    }

    traverse_in_recursive(visit, root->lchild);
    visit(root);
    traverse_in_recursive(visit, root->rchild);
}

template <typename T>
template <typename VST>
void BinTree<T>::traverse_in_iteration(VST visit, BinPos(T) root) {
    if (!root) {
        return;
    }

    Stack<BinPos(T)> stack;
    while (true) {
        go_along_left_branch(root, stack);
        if (stack.empty()) {
            return;
        }
        root = stack.pop();
        visit(root);
        root = root->rchild;
    }
}

template <typename T>
void BinTree<T>::go_along_left_branch(BinPos(T) root, Stack<BinPos(T)> &stack) {
    while (root) {
        stack.push(root);
        root = root->lchild;
    }
}

template <typename T>
template <typename VST>
void BinTree<T>::traverse_post(VST visit, BinPos(T) root) {
    traverse_post_iteration(visit, root);
}

template <typename T>
template <typename VST>
void BinTree<T>::traverse_post_recursive(VST visit, BinPos(T) root) {
    if (!root) {
        return;
    }

    traverse_post_recursive(visit, root->lchild);
    traverse_post_recursive(visit, root->rchild);
    visit(root);
}

template <typename T>
template <typename VST>
void BinTree<T>::traverse_post_iteration(VST visit, BinPos(T) root) {
    if (!root) {
        return;
    }

    BinPos(T) pre = nullptr;
    Stack<BinPos(T)> stack;
    stack.push(root);

    while (!stack.empty()) {
        root = stack.top();
        if ((!root->lchild && !root->rchild) ||
            (pre && (pre == root->lchild || pre == root->rchild))) {
            stack.pop();
            visit(root);
            pre = root;
        } else {
            if (root->rchild) {
                stack.push(root->rchild);
            }
            if (root->lchild) {
                stack.push(root->lchild);
            }
        }
    }
}

template <typename T>
template <typename VST>
void BinTree<T>::traverse_level(VST visit, BinPos(T) root) {
    if (!root) {
        return;
    }

    Queue<BinPos(T)> queue;
    queue.enqueue(root);
    while (!queue.empty()) {
        root = queue.dequeue();
        visit(root);
        if (root->lchild) {
            queue.enqueue(root->lchild);
        }
        if (root->rchild) {
            queue.enqueue(root->rchild);
        }
    }
}

template <typename T>
void BinTree<T>::init(Vector<T> &vector) {
    if (vector.empty()) {
        return;
    }

    int size = vector.size();
    BinPos(T) *nodes = new BinPos(T)[size];
    for (int i = 0; i < size; i++) {
        nodes[i] = new BinNode<T>(vector[i]);
    }

    Queue<BinPos(T)> queue;
    queue.enqueue(nodes[0]);

    int idx = 0;
    BinPos(T) root;
    while (idx < size) {
        root = queue.dequeue();
        if (++idx < size) {
            queue.enqueue(nodes[idx]);
            root->lchild = queue.rear();
            root->lchild->parent = root;
        }
        if (++idx < size) {
            queue.enqueue(nodes[idx]);
            root->rchild = queue.rear();
            root->rchild->parent = root;
        }
    }
    _size = size;
    _root = nodes[0];
}

#endif // __BIN_TREE_H_
