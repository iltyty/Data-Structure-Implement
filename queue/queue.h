#ifndef __QUEUE_H_
#define __QUEUE_H_

#include "../list/list.h"

template <typename T>
class Queue: public List<T> {
    public:
        void enqueue(const T &e) {
            this->append(e);
        }

        T dequeue() {
            return this->remove_first();
        }

        T & front() {
            return this->first()->data;
        }
};

#endif // __QUEUE_H_
