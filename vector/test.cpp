#include "vector.cpp"

template <typename T>
void print_(T&);
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
void test_find(Vector<T> &vector);
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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <test size>" << endl;
        return -1;
    }

    test_vector<int>(atoi(argv[1]));
}

template <typename T>
void print_(T &elem) {
    cout << elem << " ";
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

    test_opt_cout(vector);
    test_opt_eq(vector);
    test_opt_brk(vector);
    test_remove(vector);
    test_find(vector);
    test_traverse(vector);
    test_uniquify();
    test_bubble_sort_a(vector);
    test_bubble_sort_b(vector1);
    test_bubble_sort_c(vector2);
    test_merge_sort(vector3);
}

template <typename T>
void test_opt_cout(Vector<T> &vector) {
    cout << "test1: operator '<<' ";
    cout << vector;
}

template <typename T>
void test_opt_eq(Vector<T> &vector) {
    cout << "test2: operator '='  ";
    Vector<T> vector1 = vector;
    cout << vector1;
}

template <typename T>
void test_opt_brk(Vector<T> &vector) {
    cout << "test3: operator '[]' ";
    cout << "[ ";
    for (int i = 0; i < vector.size(); i++) {
        // TODO
        // link error: undefined reference to `Vector<int>::print(int&)`
        // vector.print(vector[i]);
        cout << vector[i] << " ";
    }
    cout << "]" << endl;
}

template <typename T>
void test_remove(Vector<T> &vector) {
    cout << "test4: function remove ";
    vector.remove(5);
    cout << vector;
}

template <typename T>
void test_find(Vector<T> &vector) {
    cout << "test5: function find ";
    cout << vector.find(vector[5]) << endl;
}

template <typename T>
void test_traverse(Vector<T> &vector) {
    cout << "test6: function traverse ";
    void (*fp) (T&) = print_;
    vector.traverse(fp);
    cout << endl;
}

void test_uniquify() {
    cout << "test7: function uniquify ";
    Vector<int> vector;
    vector.put(0, 1);
    vector.put(1, 1);
    vector.put(2, 2);
    vector.put(3, 3);
    vector.uniquify();
    cout << vector;
}

template <typename T>
void test_bubble_sort_a(Vector<T> &vector) {
    cout << "test8: function bubble sort a" << endl;
    cout << "       before sort: " << vector;
    vector.bubble_sort_a(0, vector.size());
    cout << "       after sort: " << vector;
}

template <typename T>
void test_bubble_sort_b(Vector<T> &vector) {
    cout << "test9: function bubble sort b" << endl;
    cout << "       before sort: " << vector;
    vector.bubble_sort_b(0, vector.size());
    cout << "       after sort: " << vector;
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
