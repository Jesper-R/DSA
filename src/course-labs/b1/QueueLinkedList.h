#ifndef QUEUELINKEDLIST_H
#define QUEUELINKEDLIST_H
#include <stdexcept>

template <typename T>
class QueueLinkedList
{
private:
    class Node
    {
    public:
        T data;
        Node* next;
        Node(T data, Node* next = nullptr)
            : data(data), next(next) {}
    };

    Node* front; //
    Node* rear;  //
    int count;   //

public:
    QueueLinkedList();
    virtual ~QueueLinkedList();
    QueueLinkedList(const QueueLinkedList& other) = delete;
    QueueLinkedList& operator=(const QueueLinkedList& other) = delete;
    void enqueue(const T& element);
    T dequeue();
    const T& peek() const;
    bool isEmpty() const;
    int size() const;
};

template<typename T>
inline QueueLinkedList<T>::QueueLinkedList()
    : front(nullptr), rear(nullptr), count(0) //
{
}

template<typename T>
inline QueueLinkedList<T>::~QueueLinkedList()
{
    while (!isEmpty()) //
    {
        dequeue(); //
    }
}

template<typename T>
inline void QueueLinkedList<T>::enqueue(const T& element)
{
    Node* newNode = new Node(element); //
    if (isEmpty()) //
    {
        front = rear = newNode; //
    }
    else
    {
        rear->next = newNode; //
        rear = newNode; //
    }
    ++count; //
}

template<typename T>
inline T QueueLinkedList<T>::dequeue()
{
    if (isEmpty()) //
        throw std::underflow_error("Queue is empty"); //

    Node* temp = front; //
    T data = temp->data; //
    front = front->next; //
    delete temp; //
    --count; //
    if (front == nullptr) //
        rear = nullptr; //
    return data; //
}

template<typename T>
inline const T& QueueLinkedList<T>::peek() const
{
    if (isEmpty()) //
        throw std::underflow_error("Queue is empty"); //
    return front->data; //
}

template<typename T>
inline bool QueueLinkedList<T>::isEmpty() const
{
    return count == 0; //
}

template<typename T>
inline int QueueLinkedList<T>::size() const
{
    return count; //
}

#endif
