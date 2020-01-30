#ifndef __ENTRY_H_
#define __ENTRY_H_

template <typename K, typename V>
// Binary research tree node
struct Entry {
    // Unique key code, id
    K key;
    // Data field
    V value;
    Entry(K k, V v) : key(k), value(v) {}
    Entry(const Entry<K, V> &e) : key(e.key), value(e.value) {}
    bool operator<(const Entry<K, V> &e) { return value < e.value; }

    bool operator>(const Entry<K, V> &e) { return value > e.value; }

    Entry operator=(const Entry<K, V> &e) { return Entry(e); }

    bool operator==(const Entry<K, V> &e) { return value == e.value; }

    bool operator!=(const Entry<K, V> &e) { return value != e.value; }
};

#endif // __ENTRY_H_
