#ifndef HEAP_HPP
#define HEAP_HPP

#include <stdexcept>

template <class T>
class Heap {
private:
    int capacity;
    int nrOfElements;
    T* elements;
    void expand();
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
    int newCapacity = capacity * 2;
    T* newElements = new T[newCapacity];

    for (int i = 0; i < nrOfElements; i++) {
        newElements[i] = elements[i];
    }

    delete[] elements;
    elements = newElements;
    capacity = newCapacity;
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
    if (nrOfElements == capacity) {
        expand();
    }

    elements[nrOfElements] = element;

    int currentIndex = nrOfElements;
    int parentIndex = (currentIndex - 1) / 2;

    while (currentIndex > 0 && elements[currentIndex] > elements[parentIndex]) {
        T temp = elements[currentIndex];
        elements[currentIndex] = elements[parentIndex];
        elements[parentIndex] = temp;

        currentIndex = parentIndex;
        parentIndex = (currentIndex - 1) / 2;
    }

    nrOfElements++;
}

template <class T>
T Heap<T>::extract() {
    if (isEmpty()) {
        throw std::runtime_error("Cannot extract from an empty heap");
    }

    T maxElement = elements[0];
    elements[0] = elements[nrOfElements - 1];
    nrOfElements--;

    int currentIndex = 0;
    int leftChildIndex = 2 * currentIndex + 1;
    int rightChildIndex = 2 * currentIndex + 2;

    while (leftChildIndex < nrOfElements) {
        int maxChildIndex = leftChildIndex;

        if (rightChildIndex < nrOfElements && elements[rightChildIndex] > elements[leftChildIndex]) {
            maxChildIndex = rightChildIndex;
        }

        if (elements[currentIndex] < elements[maxChildIndex]) {
            T temp = elements[currentIndex];
            elements[currentIndex] = elements[maxChildIndex];
            elements[maxChildIndex] = temp;

            currentIndex = maxChildIndex;
            leftChildIndex = 2 * currentIndex + 1;
            rightChildIndex = 2 * currentIndex + 2;
        } else {
            break;
        }
    }

    return maxElement;
}

template <class T>
T Heap<T>::peek() const {
    if (isEmpty())
        throw std::runtime_error("empty");

    return elements[0];
}

#endif

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
