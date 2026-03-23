#include <iostream>
#include "Node.h"
#ifndef QUEUE_H
#define QUEUE_H

/*  A Queue implemented using a template circularly linked list:
    - Last-In First-Out (LIFO)
    - Functions: enqueue, dequeue, top, isEmpty, length, printQueue
    - Structure: Front -> node -> Rear -> Front -> ...*/
template <typename T> class Queue {
public:
    // This queue is implemented using a circularly linked list
    Node<T>* rear;

    // Default Constructor
    Queue<T>() {
        rear = nullptr;
    }

    // Destructor
    ~Queue() {
        while (rear != nullptr)
            dequeue();
    }

    void enqueue(T data) {
        // Create new node
        Node<T>* new_node = new Node<T>(data);

        // Case 1: queue is empty
        if (rear == nullptr) {
            // Assigns the new node as the rear
            rear = new_node;
            rear->next = rear;
        // Case 2: queue is not empty
        } else {
            // New node points to rear's next node
            new_node->next = rear->next;
            // Rear now points to new node
            rear->next = new_node;
            // Set new node as rear
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
        if (rear == nullptr) {
            std::cout << "Empty Queue" << std::endl;
            return;
        }

        // Iterator that start from the front
        Node<T>* itr = this->rear->next;
        do {
            std::cout << itr->data;

            /*  Add arrow if the current node
                is not the last node in queue*/
            if (itr->next != rear->next) std::cout << " -> ";

            // Move to next node
            itr = itr->next;
        } while (itr != rear->next);
        std::cout << std::endl;
    }
};
#endif // QUEUE_H
