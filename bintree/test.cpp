#include <ctime>

#include "../vector/vector.h"
#include "bin_tree.h"

template <typename T>
struct Print {
    virtual void operator () (BinPos(T) root) {
        cout << "node: " << root->data << " height: " << root->height << endl;
    }
};

template <typename T>
void test_bin_tree(int size);
template <typename T>
void test_traverse_pre_recursive(BinTree<T> &tree);
template <typename T>
void test_traverse_pre_iteration_a(BinTree<T> &tree);
template <typename T>
void test_traverse_pre_iteration_b(BinTree<T> &tree);
template <typename T>
void test_traverse_in_recursive(BinTree<T> &tree);
template <typename T>
void test_traverse_in_iteration(BinTree<T> &tree);
template <typename T>
void test_traverse_post_recursive(BinTree<T> &tree);
template <typename T>
void test_traverse_post_iteration(BinTree<T> &tree);
template <typename T>
void test_traverse_level(BinTree<T> &tree);
template <typename T>
void test_clear(BinTree<T> &tree);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <test size>" << endl;
        return -1;
    }

    test_bin_tree<int>(atoi(argv[1]));

    return 0;
}

template <typename T>
void test_bin_tree(int size) {
    Vector<T> vector;
    for (int i = 0; i < size; i++) {
        vector.put(i, i);
    }

    BinTree<T> tree;
    tree.init(vector);

    BinPos(T) root = tree.root();

    test_traverse_pre_recursive(tree);
    test_traverse_pre_iteration_a(tree);
    test_traverse_pre_iteration_b(tree);
    test_traverse_in_recursive(tree);
    test_traverse_in_iteration(tree);
    test_traverse_post_recursive(tree);
    test_traverse_post_iteration(tree);
    test_traverse_level(tree);
    test_clear(tree);
}

template <typename T>
void test_traverse_pre_recursive(BinTree<T> &tree) {
    cout << "test1 pre-order traverse (recursive)\n";
    tree.traverse_pre_recursive(Print<T>(), tree.root());
    cout << endl;
}

template <typename T>
void test_traverse_pre_iteration_a(BinTree<T> &tree) {
    cout << "test2 pre-order traverse (iteration a)\n";
    tree.traverse_pre_iteration_a(Print<T>(), tree.root());
    cout << endl;
}

template <typename T>
void test_traverse_pre_iteration_b(BinTree<T> &tree) {
    cout << "test3 pre-order traverse (iteration b)\n";
    tree.traverse_pre_iteration_b(Print<T>(), tree.root());
    cout << endl;
}

template <typename T>
void test_traverse_in_recursive(BinTree<T> &tree) {
    cout << "test4 in-order traverse (recursive)\n";
    tree.traverse_in_recursive(Print<T>(), tree.root());
    cout << endl;
}

template <typename T>
void test_traverse_in_iteration(BinTree<T> &tree) {
    cout << "test5 in-order traverse (iteration)\n";
    tree.traverse_in_iteration(Print<T>(), tree.root());
    cout << endl;
}

template <typename T>
void test_traverse_post_recursive(BinTree<T> &tree) {
    cout << "test6 post-order traverse (recursive)\n";
    tree.traverse_post_recursive(Print<T>(), tree.root());
    cout << endl;
}

template <typename T>
void test_traverse_post_iteration(BinTree<T> &tree) {
    cout << "test7 post-order traverse (iteration)\n";
    tree.traverse_post_iteration(Print<T>(), tree.root());
    cout << endl;
}

template <typename T>
void test_traverse_level(BinTree<T> &tree) {
    cout << "test8 level-order traverse (iteration)\n";
    tree.traverse_level(Print<T>(), tree.root());
    cout << endl;
}

template <typename T>
void test_clear(BinTree<T> &tree) {
    cout << "test9 function clear\n";
    cout << "before clear: ";
    tree.traverse_pre_iteration_b(Print<T>(), tree.root());
    cout << "\nafter  clear: ";
    tree.clear();
    tree.traverse_pre_iteration_b(Print<T>(), tree.root());
    cout << endl;
}
