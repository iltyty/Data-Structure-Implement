#ifndef __STACK_H_
#define __STACK_H_

#include "../list/list.h"

template <typename T>
class Stack: public List<T> {
    public:
        void push(const T &e);
        T pop();
        T & top();
};


template <typename T>
void Stack<T>::push(const T &e) {
    this->append(e);
}

// Delete the last element
template <typename T>
T Stack<T>::pop() {
    if (!this->size()) {
        throw "Error: Cannot pop when stack is empty";
    }

    return this->remove();
}

template <typename T>
T & Stack<T>::top() {
    if (!this->size()) {
        throw "Error: Stack is not accessible when empty";
    }

    return (*this)[this->size() - 1];
}


#endif // __STACK_H_
