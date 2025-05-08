#ifndef STACKLINKEDLIST_H
#define STACKLINKEDLIST_H
#include <stdexcept>

template <typename T>
class StackLinkedList
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

    Node* top; //
    int nrOfItems; //
public:
    StackLinkedList();
    virtual ~StackLinkedList();
    StackLinkedList(const StackLinkedList& other) = delete;
    StackLinkedList& operator=(const StackLinkedList& other) = delete;
    void push(const T& element);
    T pop();
    const T& peek() const;
    bool isEmpty()const;
    int size() const;
};

template<typename T>
inline StackLinkedList<T>::StackLinkedList() : top(nullptr), nrOfItems(0) //
{
}

template<typename T>
inline StackLinkedList<T>::~StackLinkedList()
{
    while(!isEmpty()) //
    {
        pop(); //
    }
}

template<typename T>
inline void StackLinkedList<T>::push(const T& element)
{
    top = new Node(element, top); //
    nrOfItems++; //
}

template<typename T>
inline T StackLinkedList<T>::pop()
{
    if (top == nullptr) //
        throw std::runtime_error("calling pop on empty"); //

    T toReturn = top->data; //
    Node* toDelete = top; //
    top = top->next; //
    delete toDelete; //
    nrOfItems--; //
    return toReturn; //
}

template<typename T>
inline const T& StackLinkedList<T>::peek() const
{
    if (top == nullptr) //
        throw std::runtime_error("calling peek on empty"); //

    return top->data; //
}

template<typename T>
inline bool StackLinkedList<T>::isEmpty()const
{
    return nrOfItems == 0; //
}

template<typename T>
inline int StackLinkedList<T>::size()const
{
    return nrOfItems; //
}

#endif
