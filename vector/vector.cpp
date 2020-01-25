#include "vector.h"

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
template <typename  T>
static Rank bin_search_a(T *elems, T const &elem, Rank low, Rank high) {
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
template <typename  T>
static Rank bin_search_b(T *elems, T const &elem, Rank low, Rank high) {
    while (high - low > 1) {
        Rank mid = (low + high) / 2;
        if (elems[mid] < elem) {
            // [mid, high)
            low = mid;
        } else {
            // [low, mid)
            high = mid;
        }
    }
    return elem == elems[low] ?
        low : -1;
}

/*
 * Binary search, version 3.0
 * Left/Right subinterval: both one comparison
 * Return the rank of the largest element not greater than elem
 */
template <typename  T>
static Rank bin_search_c(T *elems, T const &elem, Rank low, Rank high) {
    while (low < high) {
        Rank mid = (low + high) / 2;
        if (elems[mid] < elem) {
            // (mid, high)
            low = ++mid;
        } else {
            // [low, mid)
            high = mid;
        }
    }
    return --low;
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

    int i;
    while (_elem[i] == _elem[i + 1]) {
        i++;
    }

    // true: descending order (if ordered)
    // false: ascending order (if ordered)
    bool flag = _elem[i] > _elem[i + 1];
    for (i++; i < _size; i++) {
        if ((_elem[i] >= _elem[i + 1]) != flag) {
            return false;
        }
    }
    return true;
}

template <typename T>
int Vector<T>::sort() {
    return 0;
}

/*
 * Bubble sort between [low, high)
 */
template <typename T>
void Vector<T>::bubble_sort(Rank low, Rank high) {
    int times = high - low - 1;
    for (int i = 0; i < times; i++) {
        // Scan times: high - low
        int lower_bound = low + i;
        for (int j = high - 1; j > lower_bound; j--) {
            if (_elem[j] < _elem[j - 1]) {
                T tmp = _elem[j];
                _elem[j] = _elem[j - 1];
                _elem[j - 1] = tmp;
            }
        }
    }
}
/*
 * Return the rank of element elem
 * Return:
 *   -1 for element not existed
 *   other positive integer for the first matching result
 */
template <typename T>
Rank Vector<T>::find(T elem) {
    for (int i = 0; i < _size; i++) {
        if (_elem[i] == elem) {
            return i;
        }
    }
    return -1;
}

template <typename T>
T Vector<T>::search(T elem) {
    T t;
    return t;
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
Vector<T>& Vector<T>::operator=(Vector<T> const &vector) {
    return Vector<T>(vector);
}

// Overload operator "[]"
template <typename T>
T& Vector<T>::operator[](Rank rank) {
    return _elem[rank];
}
