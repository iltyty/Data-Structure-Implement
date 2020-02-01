#include "avl.h"

template <typename T>
struct Print {
    virtual void operator () (BinPos(T) node) {
        // cout << "node: " << node->data;
        // if (node->parent) {
        //     cout << " parent: " << node->parent->data;
        // }
        // if (node->lchild) {
        //     cout << " lchild: " << node->lchild->data;
        // }
        // if (node->rchild) {
        //     cout << " rchild: " << node->rchild->data;
        // }
        // cout << " height: " << node->height;
        // cout << endl;
        cout << node->data << " ";
    }
};

template <typename T>
void test_avl(int size);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <test size>" << endl;
        return -1;
    }

    test_avl<int>(atoi(argv[1]));
    return 0;
}

template <typename T>
void test_avl(int size) {
    AVL<T> avl;

    srand(time(0));
    for (int i = 0; i < 100; i++) {
        avl.insert(rand() % 1000);
    }

    BinPos(T) root = avl.root();
    avl.traverse_in(Print<T>(), root);
}
