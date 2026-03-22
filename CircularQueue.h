#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <stdexcept>
#include "Node.h"

template <typename T>
class CircularQueue {
private:
    Node<T>* rear;
    int count;

public:
    CircularQueue() : rear(nullptr), count(0) {}

    ~CircularQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return rear == nullptr;
    }

    int size() const {
        return count;
    }

    T front() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty.");
        }
        return rear->next->data;
    }

    void enqueue(const T& value) {
        Node<T>* newNode = new Node<T>(value);

        if (isEmpty()) {
            rear = newNode;
            rear->next = rear;
        } else {
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

        Node<T>* frontNode = rear->next;
        T removedData = frontNode->data;

        if (rear == frontNode) {
            rear = nullptr;
        } else {
            rear->next = frontNode->next;
        }

        delete frontNode;
        count--;
        return removedData;
    }
};

#endif
