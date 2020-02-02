#include "btree.h"

template <typename T>
struct Print {
    virtual void operator () (T e) {
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
    BTree<T> btree(2);

    srand(time(0));
    for (int i = 0; i < size; i++) {
        btree.insert(rand() % 1000);
    }

    btree.traverse_in(Print<T>(), btree.root());
}
