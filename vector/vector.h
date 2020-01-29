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

template <typename  T>
void Vector<T>::copy_from(T const *elems, Rank low, Rank high) {
    _capacity = 2 * (high - low);

    if (_elem) {
        delete[] _elem;
    }

    _elem = new T[_capacity];
    _size = 0;
    while (low < high) {
        _elem[_size++] = elems[low++];
    }
}

// Double the vector space when necessary
template <typename  T>
void Vector<T>::expand() {
    if (_size < _capacity) {
        return;
    }

    _capacity *= 2;

    T *old_elems = _elem;
    _elem = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        _elem[i] = old_elems[i];
    }

    delete[] old_elems;
}

// Halve the vector space when
// the loading factor is less than 0.5
template <typename  T>
void Vector<T>::shrink() {
    // Does not shrink below DEFAULT_CAPACITY
    if (_capacity < DEFAULT_CAPACITY / 2) {
        return;
    }

    // Keep the loading factor greater than 0.25
    if (_size > _capacity / 2) {
        return;
    }
    _capacity /= 2;

    T *old_elems = _elem;
    _elem = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        _elem[i] = old_elems[i];
    }

    delete old_elems;
}

/*
 * Binary search between [low, high), version 1.0
 * Right subinterval: one comparison
 * Left subinterval: two comparison
 * Prerequisite: a non-descending vector
 */
template <typename T>
Rank Vector<T>::bin_search_a(T *elems, T const &elem, Rank low, Rank high) {
    while (low < high) {
        Rank mid = (low + high) / 2;
        if (elems[mid] < elem) {
            // (mid, high)
            low = ++mid;
        } else if (elems[mid] > elem) {
            // [low, mid)
            high = mid;
        } else {
            return mid;
        }
    }
    // Search failed
    return -1;
}

/*
 * Binary search, version 2.0
 * Left/Right subinterval: both one comparison
 * Better under worst circumstances
 * Worse under best circumstances
 * More stable over all performance
 */
template <typename T>
Rank Vector<T>::bin_search_b(T *elems, T const &elem, Rank low, Rank high) {
    while (high - low > 1) {
        Rank mid = (low + high) / 2;
        if (elems[mid] > elem) {
            // [low, mid)
            high = mid;
        } else {
            // [mid, high)
            low = mid;
        }
    }
    return elem == elems[low] ? low : -1;
}

/*
 * Binary search, version 3.0
 * Left/Right subinterval: both one comparison
 * Return the rank of the largest element not greater than elem
 */
template <typename T>
Rank Vector<T>::bin_search_c(T *elems, T const &elem, Rank low, Rank high) {
    while (low < high) {
        Rank mid = (low + high) / 2;
        if (elems[mid] > elem) {
            // [low, mid)
            high = mid;
        } else {
            // (mid, high)
            low = ++mid;
        }
    }
    return --low;
}

template <typename  T>
void Vector<T>::swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename  T>
Vector<T>::Vector(int capacity) {
    _size = 0;
    _capacity = capacity;
    _elem = new T[capacity];
}

template <typename  T>
Vector<T>::Vector(T const *vector, Rank low, Rank high) {
    copy_from(vector, low, high);
}

template <typename  T>
Vector<T>::Vector(Vector<T> const &vector, Rank low, Rank high) {
    copy_from(vector._elem, low, high);
}

template <typename  T>
Vector<T>::Vector(Vector<T> const &vector) {
    copy_from(vector._elem, 0, vector._size);
}

template <typename  T>
Vector<T>::~Vector() {
    if (_elem) {
        delete[] _elem;
    }
}

template <typename T>
int Vector<T>::size() {
    return _size;
}

template <typename T>
int Vector<T>::capacity() {
    return _capacity;
}

template <typename T>
T Vector<T>::get(Rank rank) {
    return _elem[rank];
}

template <typename T>
void Vector<T>::print(T &elem) {
    cout << elem << " ";
}

template <typename T>
bool Vector<T>::empty() {
    return !_size;
}

/*
 * Place an element at the specified position
 * Args:
 *   rank: position ( [0, _size] )
 *   elem: target element to be put
 * Return:
 *   The result of the put operation:
 *   0 for success, -1 for error
 */
template <typename T>
int Vector<T>::put(Rank rank, T elem) {
    // Illegal rank value
    if (rank < 0 || rank > _size) {
        return -1;
    }
    // Expand when necessary
    expand();

    for (int i = _size; i > rank ; i--) {
        _elem[i] = _elem[i - 1];
    }

    _size++;
    _elem[rank] = elem;
    return 0;
}

template <typename T>
int Vector<T>::insert(Rank rank, T elem) {
    return put(rank, elem);
}

/*
 * Remove the element at position rank
 * Args:
 *   rank: position ( [0, _size) )
 * Return:
 *   Same as put
 */
template <typename T>
int Vector<T>::remove(Rank rank) {
    if (rank < 0 || rank >= _size) {
        return -1;
    }
    if (!_elem || !_size) {
        return 0;
    }

    for (int i = rank; i < _size - 1; i++) {
        _elem[i] = _elem[i + 1];
    }

    _size--;
    // Shrink when necessary
    shrink();
    return 0;
}

/* Whether the vector is disordered or not
 * Return:
 *   1 for ascending order
 *   -1 for descending order
 *   0 for disordered
 */
template <typename T>
int Vector<T>::disordered() {
    if (_size < 2) {
        return 1;
    }

    int i = 0;
    while (_elem[i] == _elem[i + 1]) {
        i++;
    }

    // true: descending order (if ordered)
    // false: ascending order (if ordered)
    bool flag = _elem[i] > _elem[i + 1];
    for (i++; i < _size - 1; i++) {
        if ((_elem[i] == _elem[i + 1])) {
            continue;
        }
        if ((_elem[i] > _elem[i + 1]) != flag) {
            return 0;
        }
    }
    return flag ? -1 : 1;
}

template <typename T>
void Vector<T>::sort() {
    merge_sort(0, _size);
}

 // Bubble sort between [low, high), version 1.0
template <typename T>
void Vector<T>::bubble_sort_a(Rank low, Rank high) {
    int times = high - low - 1;
    for (int i = 0; i < times; i++) {
        // Scan times: high - low
        Rank lower_bound = low + i;
        for (Rank j = high - 1; j > lower_bound; j--) {
            if (_elem[j] < _elem[j - 1]) {
                swap(_elem[j], _elem[j - 1]);
            }
        }
    }
}


// Bubble sort, version 2.0
template <typename T>
void Vector<T>::bubble_sort_b(Rank low, Rank high) {
    int ordered = true;
    int times = high - low - 1;
    for (int i = 0; i < times; i++) {
        Rank lower_bound = low + i;
        for (Rank j = high - 1; j > lower_bound; j--) {
            if (_elem[j] < _elem[j - 1]) {
                ordered = false;
                swap(_elem[j], _elem[j - 1]);
            }
        }
        if (ordered) {
            // The disordered part is ordered, exit sort
            return;
        }
    }
}

// Bubble sort, version 3.0
template <typename T>
void Vector<T>::bubble_sort_c(Rank low, Rank high) {
    int i = 0;
    while (i < high) {
        Rank last_swap = i + 1;
        for (Rank j = high - 1; j > i; j--) {
            if (_elem[j] < _elem[j - 1]) {
                last_swap = j;
                swap(_elem[j], _elem[j - 1]);
            }
        }
        i = last_swap;
    }
}

// Merge sort between [low, high)
template <typename T>
void Vector<T>::merge_sort(Rank low, Rank high) {
    if (high - low < 2) {
        // high - low == 1
        // Single element, ordered for sure
        return;
    }
    // Use the midpoint as the pivot
    Rank mid = (low + high) / 2;
    // Sort the first half: [low, mid)
    merge_sort(low, mid);
    // Sort the second half: [mid, high)
    merge_sort(mid, high);
    // Merge
    merge(low, mid, high);
}

// Merge [low, mid) and [mid, high)
template <typename T>
void Vector<T>::merge(Rank low, Rank mid, Rank high) {
    // result[0, high - low) = _elem[low, high)
    T *result = _elem + low;
    // Only need to duplicate the first half
    int len1 = mid - low;
    int len2 = high - mid;
    T *first = new T[len1];
    // Second half
    T *second = _elem + mid;

    // Duplicate the first half
    for (int i = 0; i < len1 ; i++) {
        first[i] = result[i];
    }

    int i = 0;
    int j = 0;
    int idx = 0;
    while (i < len1 && j < len2) {
        if (first[i] < second[j]) {
            result[idx++] = first[i++];
        } else {
            result[idx++] = second[j++];
        }
    }
    while (i < len1) {
        result[idx++] = first[i++];
    }
    while (j < len2) {
        result[idx++] = second[j++];
    }

    delete[] first;
}

template <typename T>
Rank Vector<T>::search(T const &elem) {
    return (_size > 0) ?
        search(elem, 0, _size) : -1;
}

template <typename T>
Rank Vector<T>::search(T const &elem, Rank low, Rank high) {
    return Vector<T>::bin_search_c(_elem, elem, low, high);
}

/*
 * Delete all duplicate elements
 * Prerequisite: an ordered vector
 * Return: number of elements deleted
 */
template <typename T>
int Vector<T>::uniquify() {
    Rank i = 0, j = 0;
    while (++j < _size) {
        if (_elem[i] != _elem[j]) {
            _elem[++i] = _elem[j];
        }
    }
    _size = ++i;
    shrink();
    return j - i;
}

// Similar to function map in JavaScript
template <typename T>
void Vector<T>::traverse(void (*visit) (T&)) {
    for (int i = 0; i < _size; i++) {
        visit(_elem[i]);
    }
}

// Overload operator "="
template <typename T>
Vector<T> Vector<T>::operator=(Vector<T> const &vector) {
    return Vector<T>(vector);
}

// Overload operator "[]"
template <typename T>
T& Vector<T>::operator[](Rank rank) {
    return _elem[rank];
}

#endif // __VECTOR_H_
