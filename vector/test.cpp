#include "vector.h"
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
    test_opt_cout(vector);
    test_opt_eq(vector);
    test_opt_brk(vector);
    test_remove(vector);
    test_find(vector);
    test_traverse(vector);
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
}
