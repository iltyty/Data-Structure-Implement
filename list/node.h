#ifndef __NODE_H_
#define __NODE_H_

#define Pos(T) Node<T>*

template <typename T>
struct Node {
    T data;
    // predecessor
    Pos(T) pre;
    // successor
    Pos(T) next;
    // constructer for header and trailer
    Node() {}
    // default constructor
    Node(T data, Pos(T) pre, Pos(T) next)
        : data(data), pre(pre), next(next) {}
    // insert as predecessor
    Pos(T) insert_pre(T const &elem);
    // insert as successor
    Pos(T) insert_next(T const &elem);

};

#endif // __NODE_H_
