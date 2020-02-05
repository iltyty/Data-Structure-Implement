#ifndef __PQUEUE_H_
#define __PQUEUE_H_

#include "../vector/vector.h"

#define Parent(x) ((x - 1) / 2)
#define LChild(x) (2 * x + 1)
#define RChild(x) (2 * x + 2)

template <typename T> class PQ {
    public:
        virtual T get() = 0;
        virtual T enqueue(T e) = 0;
        virtual T dequeue() = 0;
};

#endif // __PQUEUE_H_
