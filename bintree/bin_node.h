#ifndef __BIN_NODE_H_
#define __BIN_NODE_H_

#define BinPos(T) BinNode<T>*

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
