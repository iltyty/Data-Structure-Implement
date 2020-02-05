#include "pq_left_heap.h"
#include "pq_complete_heap.h"

template <typename T> void test_pq_complheap(int size);
template <typename T> void test_pq_leftheap(int size);

template <typename T>
struct Print {
    virtual void operator () (BinPos(T) root) {
        cout << root->data << " ";
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <test size>" << endl;
        return -1;
    }

    int size = atoi(argv[1]);
    test_pq_complheap<int>(size);
    test_pq_leftheap<int>(size);

    return 0;
}

template <typename T> void test_pq_complheap(int size) {
    cout << "-----test 1: complete heap-----" << endl;
    PQ_ComplHeap<T> pq;
    for (int i = 0; i < size; i++) {
        cout << "enqueue " << i << ": ";
        pq.enqueue(i);
        cout << pq;
    }

    cout << endl;

    for (int i = 0; i < size; i++)  {
        cout << "dequeue " << pq.dequeue() << ": " ;
        cout << pq;
    }
}

template <typename T> void test_pq_leftheap(int size) {
    cout << endl << "-----test 2: leftist heap-----" << endl;
    PQ_LeftHeap<T> pq;
    for (int i = 0; i < size; i++) {
        cout << "enqueue " << i << ": ";
        pq.enqueue(i);
        pq.traverse_level(Print<T>(), pq.root());
        cout << endl;
    }

    cout << endl;

    for (int i = 0; i < size; i++) {
        cout << "dequeue " << pq.dequeue() << ": ";
        pq.traverse_level(Print<T>(), pq.root());
        cout << endl;
    }
}
