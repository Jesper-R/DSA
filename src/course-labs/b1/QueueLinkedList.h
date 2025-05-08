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
    Node* rear; //
    int nrOfItems; //
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
inline QueueLinkedList<T>::QueueLinkedList() : front(nullptr), rear(nullptr), nrOfItems(0) //
{
}

template<typename T>
inline QueueLinkedList<T>::~QueueLinkedList()
{
    while(!isEmpty()) //
    {
        dequeue(); //
    }
}

template<typename T>
inline void QueueLinkedList<T>::enqueue(const T& element)
{
    Node* newNode = new Node(element); //
    if (isEmpty())//
        front = rear = newNode; //
    else
    {
        rear->next = newNode; //
        rear = newNode; //
    }
    nrOfItems++; //
}

template<typename T>
inline T QueueLinkedList<T>::dequeue()
{
    if(isEmpty())//
        throw std::runtime_error("underflow, queue empty"); //

    T toReturn = front->data; //
    Node* toDelete = front; //
    front = front->next; //
    delete toDelete; //
    nrOfItems--; //
    return toReturn; //
}

template<typename T>
inline const T& QueueLinkedList<T>::peek() const
{
    if(isEmpty())//
        throw std::runtime_error("underflow, queue empty"); //
    return front->data; //
}

template<typename T>
inline bool QueueLinkedList<T>::isEmpty() const
{
    return nrOfItems == 0; //
}

template<typename T>
inline int QueueLinkedList<T>::size() const
{
    return nrOfItems; //
}

#endif
