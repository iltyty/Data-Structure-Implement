#include "pq_complete_heap.h"

template <typename T> void test_pq_complheap(int size);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <test size>" << endl;
        return -1;
    }

    int size = atoi(argv[1]);
    test_pq_complheap<int>(size);

    return 0;
}

template <typename T> void test_pq_complheap(int size) {
    PQ_ComplHeap<T> pq;
    for (int i = 0; i < size; i++) {
        cout << "enqueue " << i << ": ";
        pq.enqueue(i);
        cout << pq;
    }
    for (int i = 0; i < size; i++)  {
        cout << "dequeue " << pq.dequeue() << ": " ;
        cout << pq;
    }
}
