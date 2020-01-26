#ifndef __VECTOR_H_
#define __VECTOR_H_

#include<iostream>
using namespace std;

typedef int Rank;

#define DEFAULT_CAPACITY 3

template <typename T>
class Vector {
    private:
        Rank _size;    // current scale
        int _capacity; // total capacity
        T *_elem = nullptr;
    protected:
        // Internel functions
        void copy_from(T const *vector, Rank low, Rank high);
        void expand();
        void shrink();
        static Rank bin_search_a(T *elems, T const &elem, Rank low, Rank high);
        static Rank bin_search_b(T *elems, T const &elem, Rank low, Rank high);
        static Rank bin_search_c(T *elems, T const &elem, Rank low, Rank high);
        void swap(T &a, T &b);
    public:
        Vector<T>(int capacity = DEFAULT_CAPACITY);
        Vector<T>(T const *vector, Rank low, Rank high);
        Vector<T>(Vector<T> const &vector, Rank low, Rank high);
        Vector<T>(Vector<T> const &vector);
        ~Vector<T>();

        // Readonly interfaces
        int size();
        int capacity();
        T get(Rank rank);
        void print(T &elem);
        bool empty();
        // Writable interfaces
        int put(Rank rank, T elem);
        int insert(Rank rank, T elem);
        int remove(Rank rank);
        int disordered();
        void sort();
        // Bubble sort, all stable
        void bubble_sort_a(Rank low, Rank high);
        void bubble_sort_b(Rank low, Rank high);
        void bubble_sort_c(Rank low, Rank high);
        // Merge sort
        void merge_sort(Rank low, Rank high);
        void merge(Rank low, Rank mid, Rank high);
        // Iterator interfaces
        Rank search(T const &elem);
        Rank search(T const &elem, Rank low, Rank high);
        int uniquify();
        void traverse(void (*) (T&));
        // Overload operator
        Vector<T> operator=(Vector<T> const&);
        T& operator[](Rank rank);
        friend ostream & operator<<(ostream &os, Vector<T> &vector) {
            cout << "[ ";
            for (int i = 0; i < vector._size; i++) {
                cout << vector._elem[i] << " ";
            }
            cout << "]" << endl;
            return os;
        }
};


#endif // __VECTOR_H_
