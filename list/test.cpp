#include "list.h"

template <typename T>
void test_list(int size);
template <typename T>
void test_opt_cout(List<T> &list);
template <typename T>
void test_opt_brk(List<T> &list);
template <typename T>
void test_insert(List<T> list);
template <typename T>
void test_clear(List<T> list);
template <typename T>
void test_constructor(List<T> &list);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <test size>" << endl;
        return -1;
    }

    try {
        test_list<int>(atoi(argv[1]));
    } catch (const char *msg) {
        cerr << msg << endl;
    }
}

template <typename T>
void test_list(int size) {
    List<int> list;
    for (int i = 0; i < size; i++) {
        list.append(rand() % 100);
    }

    try {
        test_constructor(list);
    } catch (const char *msg) {
        cerr << msg << endl;
    }
    test_opt_cout(list);
    test_opt_brk(list);
    test_insert(list);
    test_clear(list);
}

template <typename T>
void test_constructor(List<T> &list) {
    cout << "test1 constructor" << endl;
    cout << "\t original list: " << list;
    List<T> list1(list);
    cout << "list1: " << list1;
    List<T> list2(list, 0, list.size());
    cout << "list2: " << list2;
    List<T> list3(list, 3, 5);
    cout << "list3: " << list3;
    List<T> list4(list, 3, 100);
    cout << "list4: " << list4;
    List<T> list5(list, 100, 4);
    cout << "list5: " << list5;
}

template <typename T>
void test_opt_cout(List<T> &list) {
    cout << "test2 operator cout" << endl;
    cout << "list: " << list;
}

template <typename T>
void test_opt_brk(List<T> &list) {
    cout << "test3 operator bracket" << endl;
    cout << "\t list[4]: " << list[4] << endl;
}

template <typename T>
void test_insert(List<T> list) {
    cout << "test4 function insert" << endl;
    cout << "\t original list: " << list;
    list.insert(-100, -100);
    cout << "\t insert(-100, -100): " << list;
    list.insert(0, 0);
    cout << "\t insert(0, 0): " << list;
    list.insert(3, 3);
    cout << "\t insert(3, 3): " << list;
    list.insert(100, 100);
    cout << "\t insert(100, 100): " << list;
}

template <typename T>
void test_clear(List<T> list) {
    cout << "test5 function clear" << endl;
    cout << "\t before clear: " << list;
    list.clear();
    cout << "\t after clear: " << list;
}
