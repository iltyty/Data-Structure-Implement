#include "avl.h"
#include "splay.h"
#include "rbtree.h"

template <typename T>
struct Print {
    virtual void operator () (BinPos(T) node) {
        cout << "node: " << node->data;
        if (node->parent) {
            cout << " parent: " << node->parent->data;
        }
        if (node->lchild) {
            cout << " lchild: " << node->lchild->data;
        }
        if (node->rchild) {
            cout << " rchild: " << node->rchild->data;
        }
        cout << " height: " << node->height;
        cout << " color: " << (node->is_black() ? "black" : "red");
        cout << endl;

        // cout << node->data << " ";
    }
};

template <typename T>
void test_avl(int size);
template <typename T>
void test_splay(int size);
template <typename T>
void test_rbtree(int size);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <test size>" << endl;
        return -1;
    }

    int size = atoi(argv[1]);

    // test_avl<int>(size);
    // test_splay<int>(size);
    test_rbtree<int>(size);
    return 0;
}

template <typename T>
void test_avl(int size) {
    AVL<T> avl;

    srand(time(0));
    for (int i = 0; i < 10; i++) {
        // avl.insert(rand() % 1000);
        avl.insert(i);
    }
    // avl.insert(340);

    // cout << "before remove: ";
    avl.traverse_in(Print<T>(), avl.root());

    // cout << endl;
    // avl.remove(340);
    // cout << "after remove 340: ";
    // avl.traverse_in(Print<T>(), avl.root());
}

template <typename T>
void test_splay(int size) {
    Splay<T> splay;

    srand(time(0));
    for (int i = 0; i < 10; i++) {
        int r = rand() % 100;
        cout << r << " ";
        splay.insert(r);
        // cout << "insert: " << i;
        // splay.insert(9 - i);
        // cout << " current root: " << splay.root()->data << endl;
    }

    splay.traverse_in(Print<T>(), splay.root());
    // cout << endl << "remove 7" << endl;
    // splay.remove(0);
    // splay.traverse_in(Print<T>(), splay.root());
}

template <typename T>
void test_rbtree(int size) {
    RBTree<T> rbtree;

    srand(time(0));
    for (int i = 0; i < size; i++) {
        // cout << rand() % 100 << endl;
        rbtree.insert(rand() % 100);
    }

    rbtree.traverse_in(Print<T>(), rbtree.root());
}
