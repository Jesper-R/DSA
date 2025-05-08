#ifndef STACKARRAY_H
#define STACKARRAY_H
#include <stdexcept>

template <typename T>
class StackArray
{
private:
    T* elements;
    int capacity;

    int topIndex; //
    void expand(); //
public:
    StackArray(int initialCapacity = 10);
    virtual ~StackArray();
    StackArray(const StackArray& other) = delete;
    StackArray& operator=(const StackArray& other) = delete;
    void push(const T& element);
    T pop();
    const T& peek() const;
    bool isEmpty()const;
    int size() const;
};

template<typename T>
inline StackArray<T>::StackArray(int initialCapacity) : capacity(initialCapacity), topIndex(-1) //
{
    if (capacity <= 0) //
        throw std::runtime_error("cap must be greater than 0"); //

    elements = new T[capacity]; //
}

template<typename T>
inline StackArray<T>::~StackArray()
{
    delete[] elements; //
}


template<typename T>
inline void StackArray<T>::push(const T& element)
{
    if (topIndex + 1 == capacity) //
        expand(); //
    elements[++topIndex] = element; //
}

template<typename T>
inline T StackArray<T>::pop()
{
    if (isEmpty()) //
        throw std::runtime_error("stack underflow, empty"); //
    return elements[topIndex--]; //
}

template<typename T>
inline const T& StackArray<T>::peek() const
{
    if (isEmpty()) //
        throw std::runtime_error("stack is empty"); //
    return elements[topIndex]; //
}

template<typename T>
inline bool StackArray<T>::isEmpty()const
{
    return topIndex == -1; //
}

template<typename T>
inline int StackArray<T>::size()const
{
    return topIndex + 1; //
}

template<typename T>
inline void StackArray<T>::expand()
{
    int newCapacity = capacity * 2; //
    T* newElements = new T[newCapacity]; //
    for(int i = 0; i <= topIndex; i++) //
        newElements[i] = elements[i]; //
    delete[] elements; //
    elements = newElements; //
    capacity = newCapacity; //
}

#endif
