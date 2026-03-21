#include <iostream>
#include "Queue.h"
#include "Node.h"
using namespace std;
#ifndef PLAYER_H
#define PLAYER_H

/*  Each player has three symbols (X or O) after using
    all their available symbols, remove the latest one
    before adding the new one*/
template <typename T> class Player : public Queue<T>
{
    private:
        static const int MAX_SIZE = 3;
        int count;
    public:
        Player() {
            this->rear = nullptr;
            count = 0;
        }

        void enqueue(T data) {
            Node<T>* new_node = new Node<T>(data);

            // Case 1: Queue is empty
            if (this->rear == nullptr) {
                this->rear = new_node;
                this->rear->next = this->rear;
                count = 1;
            // Case 2: Queue has more than one but less than three elements
            } else if (count < MAX_SIZE) {
                new_node->next = this->rear->next;
                this->rear->next = new_node;
                this->rear = new_node;
                count++;
            // Case 3: Queue is at limit
            } else {
                Node<T>* front = this->rear->next;
                this->rear->next = new_node;
                new_node->next = front->next;
                this->rear = new_node;
                delete front;
            }
        }
        void dequeue() {
            if (this->rear == nullptr) return;

            Node<T>* front = this->rear->next;
            if (this->rear == front) {
                delete front;
                this->rear = nullptr;
                count = 0;
            } else {
                this->rear->next = front->next;
                delete front;
                count--;
            }
        }
};

#endif // PLAYER_H
