#ifndef NODE_H
#define NODE_H

// This node is used for singly-Linked List
template <typename T> class Node
{
    public:
        T data;
        Node<T>* next;

        // Default Constructor
        Node() : next(nullptr) {}

        // Parameterized Constructor
        Node(T data) {
            this->data = data;
            this->next = nullptr;
        }

        virtual ~Node() {};
};

#endif // NODE_H
