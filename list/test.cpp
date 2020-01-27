#include <ctime>

#include "list.h"

template <typename T>
struct Increase {
    virtual void operator () (T &elem) {
        elem++;
    }
};

template <typename T>
void test_list(int size);
template <typename T>
void test_constructor(List<T> &list);
template <typename T>
void test_opt_cout(List<T> &list);
template <typename T>
void test_opt_brk(List<T> &list);
template <typename T>
void test_insert(List<T> list);
template <typename T>
void test_clear(List<T> list);
template <typename T>
void test_remove(List<T> list);
template <typename T>
void test_selection_sort(List<T> &list);
template <typename T>
void test_insertion_sort(List<T> &list);
template <typename T>
void test_search(List<T> &list);
template <typename T>
void test_traverse(List<T> &list);


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
    srand(time(NULL));

    List<int> list;
    for (int i = 0; i < size; i++) {
        list.append(rand() % 100);
    }

    List<int> list1(list);
    List<int> list2(list);

    try {
        test_constructor(list);
    } catch (const char *msg) {
        cerr << "\t" << msg << endl;
    }
    test_opt_cout(list);
    test_opt_brk(list);
    test_insert(list);
    test_clear(list);
    try {
        test_remove(list);
    } catch (const char *msg) {
        cerr << "\t" <<  msg << endl;
    }
    test_selection_sort(list1);
    test_insertion_sort(list2);
    test_search(list);
    test_traverse(list);
}

template <typename T>
void test_constructor(List<T> &list) {
    cout << "test1 constructor" << endl;
    cout << "\toriginal list: " << list;
    List<T> list1(list);
    cout << "\tlist1: " << list1;
    List<T> list2(list, 0, list.size());
    cout << "\tlist2: " << list2;
    List<T> list3(list, 3, 5);
    cout << "\tlist3: " << list3;
    List<T> list4(list, 3, 100);
    cout << "\tlist4: " << list4;
    List<T> list5(list, 100, 4);
    cout << "\tlist5: " << list5;
}

template <typename T>
void test_opt_cout(List<T> &list) {
    cout << "test2 operator cout" << endl;
    cout << "\tlist: " << list;
}

template <typename T>
void test_opt_brk(List<T> &list) {
    cout << "test3 operator bracket" << endl;
    cout << "\tlist: " << list;
    cout << "\tlist[-10]: " << list[-10] << endl;
    cout << "\tlist[-1]: " << list[-1] << endl;
    cout << "\tlist[1]: " << list[1] << endl;
    cout << "\tlist[9]: " << list[9] << endl;
    cout << "\tlist[100]: ";
    try {
        T elem = list[100];
    } catch (const char *msg) {
        cout << msg << endl;
    }
}

template <typename T>
void test_insert(List<T> list) {
    cout << "test4 function insert" << endl;
    cout << "\toriginal list: " << list;
    list.insert(-100, -100);
    cout << "\tinsert(-100, -100): " << list;
    list.insert(0, 0);
    cout << "\tinsert(0, 0): " << list;
    list.insert(3, 3);
    cout << "\tinsert(3, 3): " << list;
    list.insert(100, 100);
    cout << "\tinsert(100, 100): " << list;
}

template <typename T>
void test_clear(List<T> list) {
    cout << "test5 function clear" << endl;
    cout << "\tbefore clear: " << list;
    list.clear();
    cout << "\tafter clear: " << list;
}

template <typename T>
void test_remove(List<T> list) {
    cout << "test6 function remove" << endl;
    cout << "\tbefore remove: " << list;
    T elem = list[5];
    list.remove(elem);
    cout << "\tafter remove " << elem << ": " << list;
    cout << "\tremove 999: " << endl;
    list.remove(999);
}

template <typename T>
void test_selection_sort(List<T> &list) {
    List<T> list1(list);
    List<T> list2(list);
    List<T> list3(list);
    List<T> list4(list);
    cout << "test7 function selection sort" << endl;
    cout << "\tbefore sort: " << list;
    list.selection_sort(0, list.size());
    cout << "\tsort(0, 10): " << list;
    list1.selection_sort(0, 5);
    cout << "\tsort(0, 5): " << list1;
    list2.selection_sort(3, 3);
    cout << "\tsort(3, 3): " << list2;
    list3.selection_sort(6, 100);
    cout << "\tsort(6, 100): " << list3;
    list4.selection_sort(0, 10, true);
    cout << "\treverse sort(0, 10): " << list4;
}

template <typename T>
void test_insertion_sort(List<T> &list) {
    List<T> list1(list);
    List<T> list2(list);
    List<T> list3(list);
    List<T> list4(list);
    cout << "test8 function insertion sort" << endl;
    cout << "\tbefore sort: " << list;
    list.insertion_sort(0, list.size());
    cout << "\tsort(0, 10): " << list;
    list1.insertion_sort(0, 5);
    cout << "\tsort(0, 5): " << list1;
    list2.insertion_sort(3, 3);
    cout << "\tsort(3, 3): " << list2;
    list3.insertion_sort(6, 100);
    cout << "\tsort(6, 100): " << list3;
    list4.insertion_sort(0, 10, true);
    cout << "\treverse sort(0, 10): " << list4;
}

template <typename T>
void test_search(List<T> &list) {
    cout << "test9 function search" << endl;
    cout << "\tlist: " << list;
    cout << "\tsearch " << list[5] << ": " << list.search(list[5]) << endl;
    cout << "\tsearch " << "999" << ": " << list.search(999) << endl;
}

template <typename T>
void test_traverse(List<T> &list) {
    cout << "test10 function traverse (add one to each element)" << endl;
    cout << "\tbefore increase: " << list;
    list.traverse(Increase<T>());
    cout << "\tafter increase:  " << list;
}
