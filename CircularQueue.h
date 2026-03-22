#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <stdexcept>
#include "Node.h"

template <typename T>
class CircularQueue {
private:
    // Points to the last node in the queue
    Node<T>* rear;

    // Number of elements in the queue
    int count;

public:
    CircularQueue() : rear(nullptr), count(0) {}

    ~CircularQueue() {
        // Remove all nodes to avoid memory leak
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        // Queue is empty if rear is null
        return rear == nullptr;
    }

    int size() const {
        return count;
    }

    T front() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty.");
        }

        // In a circular queue, rear->next is the front node
        return rear->next->data;
    }

    void enqueue(const T& value) {
        Node<T>* newNode = new Node<T>(value);

        if (isEmpty()) {
            // First node points to itself
            rear = newNode;
            rear->next = rear;
        } else {
            // Insert new node after rear, then move rear
            newNode->next = rear->next;
            rear->next = newNode;
            rear = newNode;
        }

        count++;
    }

    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty.");
        }

        // Front node is the node after rear
        Node<T>* frontNode = rear->next;
        T removedData = frontNode->data;

        if (rear == frontNode) {
            // Only one node in the queue
            rear = nullptr;
        } else {
            // Skip over the front node
            rear->next = frontNode->next;
        }

        delete frontNode;
        count--;
        return removedData;
    }
};

#endif