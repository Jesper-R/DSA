#ifndef HEAP_HPP
#define HEAP_HPP

#include <stdexcept>
#include <algorithm>

template <class T>
class Heap {
private:
    int capacity;
    int nrOfElements;
    T* elements;
    void expand();

    void percolateUp(int index); //
    void percolateDown(int index); //
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
void Heap<T>::expand()
{
    capacity *= 2;
    T* temp = new T[capacity];
    for(int i = 0; i < nrOfElements; i++)
        temp[i] = elements[i];
    delete[] elements;
    elements = temp;
}

template <class T>
int Heap<T>::size() const{
    return nrOfElements;
}

template <class T>
bool Heap<T>::isEmpty() const {
    return nrOfElements == 0;
}

template <class T>
void Heap<T>::insert(const T& element) {
    if(nrOfElements == capacity)
        expand();

    elements[nrOfElements++] = element; // add to end
    percolateUp(nrOfElements-1);
}

template <class T>
void Heap<T>::percolateUp(int index) {
    if (index > 0)
    {
        int parent = (index - 1) / 2; // gets parent index
        if(elements[index] > elements[parent])
        {
            std::swap(elements[index], elements[parent]);
            percolateUp(parent);
        }
    }
}

template <class T>
T Heap<T>::extract() {
    if(isEmpty())
        throw std::runtime_error("empty");

    T temp = elements[0];
    elements[0] = elements[--nrOfElements]; // last in heap is up top and now we need to percolate down
    percolateDown(0);
    return temp;
}

template <class T>
void Heap<T>::percolateDown(int index) {
    if (index < nrOfElements)
    {
        int leftChild = index * 2 + 1;
        int rightChild = index * 2 + 2;

        if (leftChild >= nrOfElements)
            return;

        int bestChild = leftChild;

        if(rightChild < nrOfElements && elements[rightChild] > elements[bestChild]) // is right child valid and is it better than left?
            bestChild = rightChild;

        if(elements[index] < elements[bestChild]) // if child is bigger than parent
        {
            std::swap(elements[index], elements[bestChild]);
            percolateDown(bestChild);
        }
    }
}

template <class T>
T Heap<T>::peek() const {
    if(isEmpty())
        throw std::runtime_error("empty");
    return elements[0];
}

#endif
