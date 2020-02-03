#include "btree.h"
#include "../vector/vector.h"

template <typename T>
struct Print {
    virtual void operator () (T e) {
        // cout << "node: " << x->keys;
        // if (x->parent) {
        //     cout << "parent: " << x->parent->keys;
        // }
        // int size = x->childs.size();
        // for (int i = 0; i < size; i++) {
        //     if (x->childs[i]) {
        //         cout << "child " << i << ": " << x->childs[i]->keys;
        //     }
        // }
        // cout << endl;
        cout << e << " ";
    }
};

template <typename T>
void test_btree(int size);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <test size>" << endl;
        return -1;
    }

    int size = atoi(argv[1]);
    test_btree<int>(size);
    return 0;
}

template <typename T>
void test_btree(int size) {
    Vector<T> vector;
    BTree<T> btree(3);

    srand(time(0));
    for (int i = 0; i < size; i++) {
        int r = rand() % 100;
        btree.insert(r);
        vector.append(r);
    }

    btree.traverse_in(Print<T>(), btree.root());

    cout << endl;
    for (int i = 0; i < size; i++) {
        cout << "remove " << vector[i] << ": ";
        btree.remove(vector[i]);
        btree.traverse_in(Print<T>(), btree.root());
        cout << endl;
    }

    cout << "size: " << btree.size();
}
