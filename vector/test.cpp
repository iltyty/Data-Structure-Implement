#include "vector.h"

template <typename T>
void increase(T&);
template <typename T>
void test_vector(int size);
template <typename T>
void test_opt_cout(Vector<T> &vector);
template <typename T>
void test_opt_eq(Vector<T> &vector);
template <typename T>
void test_opt_brk(Vector<T> &vector);
template <typename T>
void test_remove(Vector<T> &vector);
template <typename T>
void test_search(Vector<T> &vector);
template <typename T>
void test_traverse(Vector<T> &vector);
void test_uniquify();
template <typename T>
void test_bubble_sort_a(Vector<T> &vector);
template <typename T>
void test_bubble_sort_b(Vector<T> &vector);
template <typename T>
void test_bubble_sort_c(Vector<T> &vector);
template <typename T>
void test_merge_sort(Vector<T> &vector);
template <typename T>
void test_disordered(Vector<T> &vector);
template <typename T>
void test_search_seq(Vector<T> &vector);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <test size>" << endl;
        return -1;
    }

    test_vector<int>(atoi(argv[1]));
}

template <typename T>
void increase(T &elem) {
    elem++;
}

template <typename T>
void test_vector(int size) {
    srand((unsigned int) time(NULL));
    Vector<T> vector;

    for (int i = 0; i < size; i++) {
        vector.put(i, rand() % 100);
    }

    Vector<T> vector1(vector);
    Vector<T> vector2(vector);
    Vector<T> vector3(vector);
    Vector<T> vector4(vector);

    test_opt_cout(vector);
    test_opt_eq(vector);
    test_opt_brk(vector);
    test_remove(vector);
    test_search(vector);
    test_traverse(vector);
    test_uniquify();
    test_bubble_sort_a(vector);
    test_bubble_sort_b(vector1);
    test_bubble_sort_c(vector2);
    test_merge_sort(vector3);
    test_disordered(vector4);
    test_search_seq(vector);
}

template <typename T>
void test_opt_cout(Vector<T> &vector) {
    cout << "test1:  operator '<<' ";
    cout << vector;
}

template <typename T>
void test_opt_eq(Vector<T> &vector) {
    cout << "test2:  operator '='  ";
    Vector<T> vector1;
    vector1 = vector;
    cout << vector1;
}

template <typename T>
void test_opt_brk(Vector<T> &vector) {
    cout << "test3:  operator '[]' ";
    cout << "[ ";
    for (int i = 0; i < vector.size(); i++) {
        cout << vector[i] << " ";
    }
    cout << "]" << endl;
}

template <typename T>
void test_remove(Vector<T> &vector) {
    cout << "test4:  function remove ";
    vector.remove(5);
    cout << vector;
}

template <typename T>
void test_search(Vector<T> &vector) {
    Vector<T> vec(vector);
    vec.sort();
    cout << "test5:  function search " << vec[5] << " in " << vec;
    cout << "        search result: " << vec.search(vec[5]) << endl;
}

template <typename T>
void test_traverse(Vector<T> &vector) {
    Vector<T> vec(vector);
    cout << "test6:  function traverse (add one to each element)" << endl;
    cout << "        before traverse: " << vec;
    void (*fp) (T&) = increase<T>;
    vec.traverse(fp);
    cout << "        after traverse: " << vec;
}

void test_uniquify() {
    cout << "test7:  function uniquify" << endl;
    Vector<int> vector;
    vector.put(0, 1);
    vector.put(1, 1);
    vector.put(2, 2);
    vector.put(3, 3);
    cout << "        before uniquify: " << vector;
    vector.uniquify();
    cout << "        after uniquify: " << vector;
}

template <typename T>
void test_bubble_sort_a(Vector<T> &vector) {
    cout << "test8:  function bubble sort a" << endl;
    cout << "        before sort: " << vector;
    vector.bubble_sort_a(0, vector.size());
    cout << "        after sort: " << vector;
}

template <typename T>
void test_bubble_sort_b(Vector<T> &vector) {
    cout << "test9:  function bubble sort b" << endl;
    cout << "        before sort: " << vector;
    vector.bubble_sort_b(0, vector.size());
    cout << "        after sort: " << vector;
}

template <typename T>
void test_bubble_sort_c(Vector<T> &vector) {
    cout << "test10: function bubble sort c" << endl;
    cout << "        before sort: " << vector;
    vector.bubble_sort_c(0, vector.size());
    cout << "        after sort: " << vector;
}

template <typename T>
void test_merge_sort(Vector<T> &vector) {
    cout << "test11: function merge sort" << endl;
    cout << "        before sort: " << vector;
    vector.merge_sort(0, vector.size());
    cout << "        after sort: " << vector;
}

template <typename T>
void test_disordered(Vector<T> &vector) {
    cout << "test12: function disordered" << endl;
    cout << "        before sort: " << vector;
    cout << "        disordered: " << (vector.disordered() ?
        "true" : "false") << endl;
    vector.sort();
    cout << "        after sort: " << vector;
    cout << "        disordered: " << (vector.disordered() ?
        "true" : "false") << endl;
}

template <typename T>
void test_search_seq(Vector<T> &vector) {
    Vector<T> vec(vector);
    vec.sort();
    cout << "test13: function search_seq" << endl;
    cout << "        vector: " << vec;
    cout << "        search " << vec[3] << ": " << vec.search_seq(vec[3]) << endl;
    cout << "        search -100: " << vec.search_seq(-100) << endl;
    cout << "        search 9999: " << vec.search_seq(9999) << endl;
}
