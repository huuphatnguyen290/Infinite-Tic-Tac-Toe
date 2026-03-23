#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

        // Default Constructor
        Node() : data(T()), next(nullptr) {}

        // Parameterized Constructor
        Node(const T& data) : data(data), next(nullptr) {};

        ~Node() {};
}; 

#endif
