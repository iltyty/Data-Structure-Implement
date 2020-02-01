#ifndef __BSTREE_H_
#define __BSTREE_H_

#include "../bintree/bin_tree.h"
#include "entry.h"

template <typename T> class BST : public BinTree<T> {
    protected:
        BinPos(T) _hot = nullptr;

    protected:
        BinPos(T)& search_in(const T &e, BinPos(T) & root, BinPos(T) & hot);
        BinPos(T) remove_at(BinPos(T) &x, BinPos(T) &hot);

    public:
        virtual BinPos(T)& search(const T &e);
        virtual BinPos(T)& insert(const T &e);
        virtual void remove(const T &e);
};


template <typename T> BinPos(T)& BST<T>::search(const T &e) {
    return search_in(e, this->_root, _hot = nullptr);
}

template <typename T> BinPos(T)& BST<T>::search_in(
    const T &e,
    BinPos(T) & root,
    BinPos(T) & hot
){
    if (!root || root->data == e) {
        // Search failed or succeeded
        return root;
    }

    // parent of the search result
    hot = root;
    if (e < root->data) {
        return search_in(e, root->lchild, hot);
    } else {
        return search_in(e, root->rchild, hot);
    }
}

template <typename T> BinPos(T)& BST<T>::insert(const T &e) {
    BinPos(T)& res = search(e);
    if (!res) {
        // Prohibit repeat element
        res = new BinNode<T>(e, _hot);
        this->_size++;
        this->update_height_above(res);
    }

    return res;
}

template <typename T>
BinPos(T) BST<T>::remove_at(BinPos(T) &x, BinPos(T) &hot) {
    // Node actually deleted
    BinPos(T) p = x;
    // Takeover node
    BinPos(T) q = nullptr;

    if (!x->lchild) {
        // Left subtree is empty
        x = x->rchild;
        q = x;
    } else if (!x->rchild) {
        // Right subtree is empty
        x = x->lchild;
        q = x;
    } else {
        // Left and right subtrees coexist
        // Find the successor of x under in-order traversal
        p = x->successor();
        // Exchange data between x and succ
        this->swap(x->data, p->data);
        // succ has no left child
        q = p->rchild;
        if (p->parent->lchild == p) {
            p->parent->lchild = q;
        } else {
            p->parent->rchild = q;
        }

    }

    hot = p->parent;
    if (q) {
        q->parent = hot;
    }
    delete p;
    return q;
}

template <typename T> void BST<T>::remove(const T &e) {
    BinPos(T) res = search(e);
    if (!res) {
        // e does not exist
        return;
    }

    remove_at(res, _hot);
    this->_size--;
    this->update_height_above(_hot);
}

#endif // __BSTREE_H_
