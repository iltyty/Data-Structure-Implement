#ifndef __BIN_NODE_H_
#define __BIN_NODE_H_

#define BinPos(T) BinNode<T>*
// x: BinPos(T)
#define stature(x) ((x) ? (x)->height : -1)

typedef enum {
    Red, Black
}RBColor;

template <typename T>
struct BinNode {
    // data field
    T data;
    // subtree height
    int height;
    // null path length
    int npl;
    // color (Red-black tree)
    RBColor color;
    // parent node
    BinPos(T) parent;
    // left child node
    BinPos(T) lchild;
    // right child node
    BinPos(T) rchild;

    BinNode(const T &data, int height = 0):
        data(data), height(height), parent(nullptr), npl(1),
        lchild(nullptr), rchild(nullptr), color(RBColor::Red) {}

    BinNode(const T &data, BinPos(T) parent, int height = 0):
        data(data), parent(parent), height(height), npl(1),
        lchild(nullptr), rchild(nullptr), color(RBColor::Red) {}

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

    void attach_lchild(BinPos(T) v) {
        lchild = v;
        if (v) {
            v->parent = this;
        }
    }

    void attach_rchild(BinPos(T) v) {
        rchild = v;
        if (v) {
            v->parent = this;
        }
    }

    bool is_red() {
        return color == Red;
    }

    bool is_black() {
        return color == Black;
    }

};



#endif // __BIN_NODE_H_
