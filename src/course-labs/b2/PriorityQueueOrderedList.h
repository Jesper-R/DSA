#ifndef PRIORITYQUEUEORDEREDLIST_HPP
#define PRIORITYQUEUEORDEREDLIST_HPP

#include "OrderedList.hpp"
#include <stdexcept>

template<typename T>
class PriorityQueueOrderedList {
private:
    OrderedList<T> list;

public:
    PriorityQueueOrderedList();
    ~PriorityQueueOrderedList() = default;
    PriorityQueueOrderedList(const PriorityQueueOrderedList& other) = delete;
    PriorityQueueOrderedList& operator =(const PriorityQueueOrderedList& other) = delete;

    int size() const;
    void enqueue(const T& element);
    T dequeue();
    T peek() const;
    bool isEmpty() const;
};

template <class T>
PriorityQueueOrderedList<T>::PriorityQueueOrderedList(){

}
template <class T>
int PriorityQueueOrderedList<T>::size() const {
    return list.size();
}
template <class T>
void PriorityQueueOrderedList<T>::enqueue(const T& element) {
    list.add(element);
}
template <class T>
T PriorityQueueOrderedList<T>::dequeue() {
    if (isEmpty())
        throw std::runtime_error("pq is empty");
    return list.removeFirst();
}
template <class T>
T PriorityQueueOrderedList<T>::peek() const {
    if (isEmpty())
        throw std::runtime_error("pq is empty");
    return list.first();
}
template <class T>
bool PriorityQueueOrderedList<T>::isEmpty() const {
    return list.size() == 0;
}

#endif
