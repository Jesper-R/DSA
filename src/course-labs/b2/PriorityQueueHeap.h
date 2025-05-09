#ifndef PRIORITYQUEUEHEAP_HPP
#define PRIORITYQUEUEHEAP_HPP

#include "Heap.hpp"
#include <stdexcept>

template <typename T>
class PriorityQueueHeap {
private:
    Heap<T> heap;

public:
    PriorityQueueHeap();
    ~PriorityQueueHeap() = default;
    PriorityQueueHeap(const PriorityQueueHeap& other) = delete;
    PriorityQueueHeap& operator =(const PriorityQueueHeap& other) = delete;

    int size() const;
    void enqueue(const T& element);
    T dequeue();
    T peek() const;
    bool isEmpty() const;
};

template <class T>
PriorityQueueHeap<T>::PriorityQueueHeap()
{

}

template <class T>
int PriorityQueueHeap<T>::size() const {
    return heap.size();
}

template <class T>
void PriorityQueueHeap<T>::enqueue(const T& element) {
    heap.insert(element);
}

template <class T>
T PriorityQueueHeap<T>::dequeue() {
    if (isEmpty())
        throw std::out_of_range("Priority queue is empty");
    return heap.extract();
}

template <class T>
T PriorityQueueHeap<T>::peek() const {
    if (isEmpty())
        throw std::out_of_range("Priority queue is empty");
    return heap.peek();
}

template <class T>
bool PriorityQueueHeap<T>::isEmpty() const {
    return heap.size() == 0;
}

#endif
