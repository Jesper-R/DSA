//
// Created by Jesper on 5/21/2025.
//

#ifndef HEAP_H
#define HEAP_H

#include <stdexcept>
#include <string>

template <class T>
class Heap {
private:
    int capacity;
    int nrOfElements;
    T* elements;
    void expand();
    void percolateUp(int index);
    void percolateDown(int index);
public:
    Heap(int initialCapacity = 10);
    ~Heap();
    Heap(const Heap& other) = delete;
    Heap& operator=(const Heap& other) = delete;

    int size() const;
    bool isEmpty() const;
    void insert(const T& element);
    T extract();
    T peek() const;
    std::string to_string() const;
};

template <class T>
Heap<T>::Heap(int initialCapacity)
{
    this->capacity = initialCapacity;
    this->nrOfElements = 0;
    this->elements = new T[this->capacity];
}

template <class T>
Heap<T>::~Heap()
{
    delete [] this->elements;
}

template <class T>
int Heap<T>::size() const{
    return this->nrOfElements;
}

template <class T>
std::string Heap<T>::to_string() const {
    std::string result = "[";
    for (int i = 0; i < this->nrOfElements; i++) {
        result += std::to_string(elements[i]);
        if (i < this->nrOfElements - 1) {
            result += ", ";
        }
    }
    result += "]";
    return result;
}

template <class T>
void Heap<T>::expand()
{
    this->capacity *= 2;
    T* temp = new T[this->capacity];
    for(int i = 0; i < this->nrOfElements; ++i)
        temp[i] = this->elements[i];
    delete [] this->elements;
    this->elements = temp;
}

template <class T>
bool Heap<T>::isEmpty() const {
    return this->nrOfElements == 0;
}

template <class T>
void Heap<T>::percolateUp(int index) {
    if (index > 0) {
        int parent = (index - 1) / 2;
        if (elements[index] < elements[parent]) {
            std::swap(elements[index], elements[parent]);
            percolateUp(parent);
        }
    }
}

template <class T>
void Heap<T>::percolateDown(int index) {
    int l_child = 2 * index + 1;
    if (l_child >= this->nrOfElements) {
        return;
    }

    int r_child = l_child + 1;
    int best_child = l_child;
    if (r_child < this->nrOfElements && elements[r_child] < elements[l_child]) {
        best_child = r_child;
    }

    if (elements[best_child] < elements[index]) {
        std::swap(elements[best_child], elements[index]);
        percolateDown(best_child);
    }
}

template <class T>
void Heap<T>::insert(const T& element) {
    if (this->nrOfElements == this->capacity)
        this->expand();
    int index = this->nrOfElements;
    this->elements[this->nrOfElements++] = element;
    percolateUp(index);
}

template <class T>
T Heap<T>::extract() {
    if (this->nrOfElements == 0) {
        throw std::out_of_range("called extract() on empty Heap");
    }
    if (this->nrOfElements == 1) {
        return this->elements[--this->nrOfElements];
    }
    T temp = elements[0];
    elements[0] = this->elements[--this->nrOfElements];
    percolateDown(0);
    return temp;
}

template <class T>
T Heap<T>::peek() const {
    if (this->nrOfElements == 0) {
        throw std::out_of_range("called peek() on empty Heap");
    }
    return elements[0];
}

#endif