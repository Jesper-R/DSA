#ifndef HEAPLIST_HPP
#define HEAPLIST_HPP

#include "IndexedList.hpp"
#include <stdexcept>

template <class T>
class HeapList {
private:
    IndexedList<T> elements;
    
    void heapifyUp(int index);
    void heapifyDown(int index);
    int parent(int index) const { return (index - 1) / 2; }
    int leftChild(int index) const { return 2 * index + 1; }
    int rightChild(int index) const { return 2 * index + 2; }

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
int HeapList<T>::size() const {
    return elements.size();
}

template <class T>
bool HeapList<T>::isEmpty() const {
    return elements.isEmpty();
}

template <class T>
void HeapList<T>::heapifyUp(int index) {
    if (index <= 0) return;
    
    int parentIndex = parent(index);
    if (elements.getAt(parentIndex) < elements.getAt(index)) {
        T temp = elements.getAt(index);
        T parentVal = elements.getAt(parentIndex);
        
        elements.removeAt(parentIndex);
        elements.addAt(parentIndex, temp);
        
        elements.removeAt(index);
        elements.addAt(index, parentVal);
        
        heapifyUp(parentIndex);
    }
}

template <class T>
void HeapList<T>::heapifyDown(int index) {
    int leftIndex = leftChild(index);
    int rightIndex = rightChild(index);
    int largest = index;
    
    if (leftIndex < elements.size() && elements.getAt(leftIndex) > elements.getAt(largest)) {
        largest = leftIndex;
    }
    
    if (rightIndex < elements.size() && elements.getAt(rightIndex) > elements.getAt(largest)) {
        largest = rightIndex;
    }
    
    if (largest != index) {
        T temp = elements.getAt(index);
        T largestVal = elements.getAt(largest);
        
        elements.removeAt(index);
        elements.addAt(index, largestVal);
        
        elements.removeAt(largest);
        elements.addAt(largest, temp);
        
        heapifyDown(largest);
    }
}

template <class T>
void HeapList<T>::insert(const T& element) {
    elements.addAt(elements.size(), element);
    heapifyUp(elements.size() - 1);
}

template <class T>
T HeapList<T>::extract() {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty");
    }
    
    T max = elements.getAt(0);
    
    if (elements.size() > 1) {
        T last = elements.getAt(elements.size() - 1);
        elements.removeAt(0);
        elements.addAt(0, last);
        elements.removeAt(elements.size() - 1);
        heapifyDown(0);
    } else {
        elements.removeFirst();
    }
    
    return max;
}

template <class T>
T HeapList<T>::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty");
    }
    return elements.getAt(0);
}

#endif