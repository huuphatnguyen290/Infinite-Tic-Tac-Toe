#include <iostream>
#include "Node.h"
#ifndef QUEUE_H
#define QUEUE_H

/*  A Queue implemented using a templated circularly linked list:
    - Last-In First-Out (LIFO)
    - Functions: enqueue, dequeue, top, isEmpty, length, printQueue*/
template <typename T> class Queue {
public:
    // This queue is implemented using a circularly linked list
    Node<T>* rear;

    // Default Constructor
    Queue<T>() {
        rear = nullptr;
    }

    // Add at the rear
    void enqueue(T data) {
        // Create new node
        Node<T>* new_node = new Node<T>(data);

        // Case 1: queue is empty
        if (rear == nullptr) {
            rear = new_node;
            rear->next = rear;
        // Case 2: queue is not empty
        } else if (rear->next == nullptr) {
            rear->next = new_node;
            new_node->next = rear;
            rear = new_node;
        }

    }

    // Remove at the front
    void dequeue() {
        if (rear == nullptr) {
            std::cout << "Error: empty queue." << std::endl;
            return;
        }

        Node<T>* front = rear->next;
        if (rear == front) {
            delete front;
            rear = nullptr;
        } else {
            rear->next = front->next;
            delete front;
        }
    }

    T top() {
        if (rear == nullptr) std::cout << "Queue is empty" << std::endl;
        return rear->next->data;
    }

    T bottom() {
        if (rear == nullptr) std::cout << "Queue is empty" << std::endl;
        return rear->data;
    }

    bool isEmpty() {
        return rear == nullptr;
    }

    int length() {
        if (rear == nullptr) return 0;

        int count = 1;
        Node<T>* itr = rear->next;
        while(itr != rear) {
            itr = itr->next;
            count++;
        }
        return count;
    }

    void printQueue() {
        Node<T>* itr = rear->next;
        while (itr != rear){
           std::cout << itr->data;
            if (itr->next != rear) std::cout << " <- ";
            itr = itr->next;
        }
        std::cout << std::endl;
    }
};
#endif // QUEUE_H
