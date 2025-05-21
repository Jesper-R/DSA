//
// Created by Jesper on 5/21/2025.
//

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "Heap.h"
#include <stdexcept>

template <typename T>
class PriorityQueue {
private:
    Heap<T> heap;

public:
    PriorityQueue();
    ~PriorityQueue() = default;
    PriorityQueue(const PriorityQueue& other) = delete;
    PriorityQueue& operator =(const PriorityQueue& other) = delete;

    int size() const;
    void enqueue(const T& element);
    T dequeue();
    T peek() const;
    bool isEmpty() const;
};
template <class T>
PriorityQueue<T>::PriorityQueue()
{

}

template <class T>
int PriorityQueue<T>::size() const {
    // Returns size of PQ
    return this->heap.size();
}

template <class T>
void PriorityQueue<T>::enqueue(const T& element) {
    this->heap.insert(element);
}

template <class T>
T PriorityQueue<T>::dequeue() {
    if (this->isEmpty()) {
        throw std::out_of_range("calling dequeue() on empty PriorityQueue");
    }
    return this->heap.extract();
}

template <class T>
T PriorityQueue<T>::peek() const {
    if (this->isEmpty()) {
        throw std::out_of_range("calling peek() on empty PriorityQueue");
    }
    return this->heap.peek();
}

template <class T>
bool PriorityQueue<T>::isEmpty() const {
    return this->heap.isEmpty();
}


#endif //PRIORITYQUEUE_H
