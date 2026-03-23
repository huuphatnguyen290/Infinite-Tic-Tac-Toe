#include <iostream>
#include "Node.h"
#ifndef QUEUE_H
#define QUEUE_H

/*  A Queue implemented using a templated circularly linked list:
    - Last-In First-Out (LIFO)
    - Functions: enqueue, dequeue, top, isEmpty, length, printQueue*/

    
template <typename T> class Queue {
// This queue is implemented using a circularly linked list
protected:
    Node<T>* rear;
    int count;
public:
    // Default Constructor
    Queue() {
        rear = nullptr;
        count =0;
    }

    virtual ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }


    // Add at the rear
    void enqueue(const T& data) {
        // Create new node
        Node<T>* new_node = new Node<T>(data);

        // Case 1: queue is empty
        if (rear == nullptr) {
            rear = new_node;
            rear->next = rear;
        // Case 2: queue is not empty
        } 
        else {
            new_node->next = rear->next; // new node points to front
            rear->next = new_node;       // old rear points to new node
            rear = new_node;             // update rear
        }
        count++;
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
        return count;
    }

    void printQueue() {

        if (rear == nullptr) {
            std::cout << "Queue is empty.\n";
            return;
        }

        Node<T>* itr = rear->next; //front
        
        do {
            std::cout << itr->data;
            itr = itr->next;
            if (itr != rear->next) {
                std::cout << " <- ";
            }
        } while (itr != rear->next);

        std::cout << std::endl;
    }
};
#endif // QUEUE_H
