#ifndef INDEXEDLIST_HPP
#define INDEXEDLIST_HPP

#include <stdexcept>

template <class T>
class IndexedList {
private:
    class Node {
    public:
        T data;
        Node* next;

        Node(T data = nullptr) : data(data), next(nullptr) {}
    };
    Node* front;
    int num_elements;

    Node* getNodeAt(int index) const {
        if (index < 0 || index >= num_elements)
            throw std::runtime_error("out of bounds");
        Node* walker = front;
        for (int i = 0; i < index; i++)
            walker = walker->next;
        return walker;
    }

public:
    IndexedList();
    ~IndexedList();
    IndexedList(const IndexedList& other) = delete;
    IndexedList& operator=(const IndexedList& other) = delete;

    int size() const;
    bool isEmpty() const;
    T getAt(int index) const;
    T get(T element) const;
    void addAt(int index, const T& element);
    T removeFirst();
    T removeAt(int index);
    T removeLast();
    T first() const ;
    T last() const;
};

template<class T>
IndexedList<T>::IndexedList() : front(nullptr), num_elements(0)
{
}

template <class T>
IndexedList<T>::~IndexedList()
{
    while (front)
    {
        Node *toDelete = front;
        front = front->next;
        delete toDelete;
    }
}

template <class T>
int IndexedList<T>::size() const {
    return num_elements;
}

template <class T>
bool IndexedList<T>::isEmpty() const {
    return num_elements == 0;
}

template <class T>
T IndexedList<T>::getAt(int index) const{
    return getNodeAt(index)->data;
}
template <class T>
T IndexedList<T>::get(T element) const{
    Node* walker = front;

    while (walker != nullptr) {
        if (walker->data == element)
            return walker->data;
        walker = walker->next;
    }

    throw std::runtime_error("element not found");
}
template <class T>
void IndexedList<T>::addAt(int index, const T& element) {
    if (index < 0 || index > num_elements)
        throw std::runtime_error("out of bounds");

    Node* newNode = new Node(element);

    if(index == 0) {
        newNode->next = front;
        front = newNode;
    } else {
        Node* prev = getNodeAt(index - 1);
        newNode->next = prev->next;
        prev->next = newNode;
    }
    num_elements++;
}

template <class T>
T IndexedList<T>::removeFirst() {
    if (isEmpty())
        throw std::runtime_error("empty list");
    Node* toDelete = front;
    T toReturn = toDelete->data;
    front = front->next;
    delete toDelete;
    num_elements--;
    return toReturn;
}

template <class T>
T IndexedList<T>::removeAt(int index) {
    if (index < 0 || index >= num_elements)
        throw std::runtime_error("out of bounds");
    if (index == 0)
        return removeFirst();

    Node* prev = getNodeAt(index - 1);
    Node* toDelete = prev->next;
    T toReturn = toDelete->data;
    prev->next = toDelete->next;
    delete toDelete;
    num_elements--;
    return toReturn;
}

template <class T>
T IndexedList<T>::removeLast() {
    if (isEmpty())
        throw std::runtime_error("empty");
    return removeAt(num_elements - 1);
}

template <class T>
T IndexedList<T>::first() const {
    if (isEmpty())
        throw std::runtime_error("empty");
    return front->data;
}

template <class T>
T IndexedList<T>::last() const {
    if (isEmpty())
        throw std::runtime_error("empty");
    return getNodeAt(num_elements - 1)->data;
}
#endif
