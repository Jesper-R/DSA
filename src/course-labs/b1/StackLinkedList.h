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
    Node* toDelete = this->top; //
    while (this->top != nullptr) //
    {
        this->top = this->top->next; //
        delete toDelete; //
        toDelete = this->top; //
    }
}

// look into and potentially easy solutions in other ones aswell
/*
template<typename T>
inline StackLinkedList<T>::~StackLinkedList()
{
while (!isEmpty()) //
{
pop(); //
}
}
*/


template<typename T>
inline void StackLinkedList<T>::push(const T& element)
{
    //Node* newNode = new Node(element); //
    //newNode->next = this->top; //
    //this->top = newNode; //
    this->top = new Node(element, this->top); // samma resultat som ovan
    ++this->nrOfItems; //
}

template<typename T>
inline T StackLinkedList<T>::pop()
{
    if (this->top == nullptr) //
        throw std::runtime_error("calling pop() on empty stack"); //
    T toReturn = this->top->data; //
    Node* toDelete = this->top; //
    this->top = this->top->next; //
    delete toDelete; //
    --this->nrOfItems; //
    return toReturn; //
}

template<typename T>
inline const T& StackLinkedList<T>::peek() const
{
    if (this->top == nullptr) //
        throw std::runtime_error("calling peek() on empty stack"); //
    return this->top->data; //
}

template<typename T>
inline bool StackLinkedList<T>::isEmpty()const
{
    return this->top == nullptr; // kan ocks[ titta p[ nrofitems
}

template<typename T>
inline int StackLinkedList<T>::size()const
{
    return this->nrOfItems; //
}

#endif
