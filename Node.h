#ifndef NODE_H
#define NODE_H

// Singly-Linked List
template <typename T> class Node
{
    public:
        T data;
        Node<T>* next;

        // Default Constructor
        Node() : data(T()), next(nullptr) {}

        // Parameterized Constructor
        Node(const T& data) : data(data), next(nullptr) {};

        virtual ~Node() {};
};

#endif // NODE_H
