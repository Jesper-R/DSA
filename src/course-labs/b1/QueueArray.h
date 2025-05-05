#ifndef QUEUEARRAY_H
#define QUEUEARRAY_H
#include <stdexcept>

template <typename T>
class QueueArray
{
private:
    T* elements;
    int capacity;
    int front; //
    int rear;  //
    int count; //
    void expand(); //
public:
    QueueArray();
    virtual ~QueueArray();
    QueueArray(const QueueArray& other) = delete;
    QueueArray& operator=(const QueueArray& other) = delete;
    void enqueue(const T& element);
    T dequeue();
    const T& peek() const;
    bool isEmpty() const;
    int size() const;
};

template<typename T>
inline QueueArray<T>::QueueArray()
    : capacity(10), front(0), rear(0), count(0) //
{
    elements = new T[capacity]; //
}

template<typename T>
inline QueueArray<T>::~QueueArray()
{
    delete[] elements; //
}

template<typename T>
inline void QueueArray<T>::expand()
{
    int newCapacity = capacity * 2; //
    T* newElements = new T[newCapacity]; //
    for (int i = 0; i < count; ++i) //
    {
        newElements[i] = elements[(front + i) % capacity]; //
    }
    delete[] elements; //
    elements = newElements; //
    front = 0; //
    rear = count; //
    capacity = newCapacity; //
}

template<typename T>
inline void QueueArray<T>::enqueue(const T& element)
{
    if (count == capacity) //
        expand(); //
    elements[rear] = element; //
    rear = (rear + 1) % capacity; //
    ++count; //
}

template<typename T>
inline T QueueArray<T>::dequeue()
{
    if (isEmpty()) //
        throw std::underflow_error("Queue is empty"); //
    T data = elements[front]; //
    front = (front + 1) % capacity; //
    --count; //
    return data; //
}

template<typename T>
inline const T& QueueArray<T>::peek() const
{
    if (isEmpty()) //
        throw std::underflow_error("Queue is empty"); //
    return elements[front]; //
}

template<typename T>
inline bool QueueArray<T>::isEmpty() const
{
    return count == 0; //
}

template<typename T>
inline int QueueArray<T>::size() const
{
    return count; //
}

#endif
