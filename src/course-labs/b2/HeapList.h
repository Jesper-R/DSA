#ifndef HEAPLIST_HPP
#define HEAPLIST_HPP

#include "IndexedList.hpp"
#include <stdexcept>

template <class T>
class HeapList {
private:
    IndexedList<T> elements;

    void percolateUp(int index); //
    void percolateDown(int index); //

public:
    HeapList() = default;
    ~HeapList() = default;
    HeapList(const HeapList& other) = delete;
    HeapList& operator=(const HeapList& other) = delete;

    int size() const;
    bool isEmpty() const;
    void insert(const T& element);
    T extract();
    T peek() const;
};

template <class T>
int HeapList<T>::size() const{
    return elements.size();
}

template <class T>
bool HeapList<T>::isEmpty() const {
    return elements.isEmpty();
}
template <class T>
void HeapList<T>::insert(const T& element) {
    elements.addAt(elements.size(), element);
    percolateUp(elements.size() - 1);
}

template <class T>
void HeapList<T>::percolateUp(int index) {
    if (index > 0) {
        int parent = (index - 1) / 2;
        if (elements.getAt(index) > elements.getAt(parent)) {
            elements.swap(index, parent);
            percolateUp(parent);
        }
    }
}

template <class T>
T HeapList<T>::extract() {
    if (elements.isEmpty())
        throw std::runtime_error("");

    T top = elements.getAt(0);
    T last = elements.removeAt(elements.size() - 1);

    if(!isEmpty())
    {
        elements.removeAt(0);
        elements.addAt(0, last);
        percolateDown(0);
    }

    return top;
}

template <class T>
void HeapList<T>::percolateDown(int index) {
    if(index < elements.size())
    {
        int size = elements.size();
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left >= size)
            return;

        int bestChild = left;
        if (right < size && elements.getAt(right) > elements.getAt(left)) {
            bestChild = right;
        }

        if (elements.getAt(index) < elements.getAt(bestChild)) {
            elements.swap(index, bestChild);
            percolateDown(bestChild);
        }
    }
}

template <class T>
T HeapList<T>::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty");
    }
    return elements.first();
}

#endif