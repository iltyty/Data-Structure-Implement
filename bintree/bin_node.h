#ifndef __BIN_NODE_H_
#define __BIN_NODE_H_

#define BinPos(T) BinNode<T>*
// x: BinPos(T)
#define stature(x) ((x) ? (x)->height : -1)

template <typename T>
struct BinNode {
    // data field
    T data;
    // subtree height
    int height;
    // parent node
    BinPos(T) parent;
    // left child node
    BinPos(T) lchild;
    // right child node
    BinPos(T) rchild;

    BinNode(const T &data):
        data(data), height(0), parent(nullptr),
        lchild(nullptr), rchild(nullptr) {}

    BinNode(const T &data, BinPos(T) parent):
        data(data), parent(parent), height(0),
        lchild(nullptr), rchild(nullptr) {}

    BinPos(T) insert_lchild(const T &data) {
        if (lchild) {
            return nullptr;
        }

        return lchild = new BinNode<T>(data, this);
    }

    BinPos(T) insert_rchild(const T &data) {
        if (rchild) {
            return nullptr;
        }

        return rchild = new BinNode<T>(data, this);
    }

    bool is_lchild() {
        if (!this->parent) {
            return false;
        }

        return this->parent->lchild == this;
    }

    bool is_rchild() {
        if (!this->parent) {
            return false;
        }

        return this->parent->rchild == this;
    }

    // Find the successor under the in-order traversal
    BinPos(T) successor() {
        BinPos(T) p = this;
        if (!this->rchild) {
            while (is_rchild()) {
                p = p->parent;
            }
            p = p->parent;
        } else {
            p = this->rchild;
            while (p->lchild) {
                p = p->lchild;
            }
        }

        return p;
    }

    // Return the taller child of current node
    // Used in rotation of AVL tree
    BinPos(T) taller_child() {
        return stature(this->lchild) >= stature(this->rchild) ?
            this->lchild : this->rchild;
    }

    int size() {
        int res = 1;
        if (lchild) {
            res += lchild->size();
        }
        if (rchild) {
            res += rchild->size();
        }
        return res;
    }
};


#endif // __BIN_NODE_H_
