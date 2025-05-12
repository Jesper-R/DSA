#ifndef ORDEREDLIST_HPP
#define ORDEREDLIST_HPP

#include <stdexcept>

template <class T>
class OrderedList {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
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
    OrderedList();
    ~OrderedList();
    OrderedList(const OrderedList& other) = delete;
    OrderedList& operator=(const OrderedList& other) = delete;

    int size() const;
    bool isEmpty() const;
    void add(const T& element);
    T remove(const T& element);
    T removeAt(int index);
    T removeFirst();
    T removeLast();
    T get(const T& element) const;
    T first() const;
    T last() const;
};

template <class T>
OrderedList<T>::OrderedList() : front(nullptr), num_elements(0)
{
}

template <class T>
OrderedList<T>::~OrderedList() {
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
}
template <class T>
int OrderedList<T>::size() const {
    return num_elements;
}
template <class T>
bool OrderedList<T>::isEmpty() const {
    return num_elements == 0;
}
template <class T>
void OrderedList<T>::add(const T& element) {
    Node* newNode = new Node(element);

    if (front == nullptr || front->data >= element) {
        newNode->next = front;
        front = newNode;
    } else {
        Node* walker = front;
        while (walker->next != nullptr && walker->next->data < element) {
            walker = walker->next;
        }
        newNode->next = walker->next;
        walker->next = newNode;
    }

    num_elements++;
}

template <class T>
T OrderedList<T>::remove(const T& element) {
    if (isEmpty())
        throw std::runtime_error("empty");

    for (int i = 0; i < num_elements; i++)
    {
        if(element == getNodeAt(i)->data)
        {
            return removeAt(i);
        }
    }
    throw std::runtime_error("not found");
}



template <class T>
T OrderedList<T>::removeAt(int index) {
    if (index < 0 || index >= num_elements)
        throw std::runtime_error("out of bounds");

    Node* toDelete;
    T toReturn;

    if (index == 0) {
        toDelete = front;
        front = front->next;
    } else {
        Node* prev = getNodeAt(index - 1);
        toDelete = prev->next;
        prev->next = toDelete->next;
    }

    toReturn = toDelete->data;
    delete toDelete;
    num_elements--;
    return toReturn;
}

template <class T>
T OrderedList<T>::removeFirst() {
    if (isEmpty())
        throw std::runtime_error("empty");
    return removeAt(0);
}
template <class T>
T OrderedList<T>::removeLast() {
    if (isEmpty())
        throw std::runtime_error("empty");
    return removeAt(num_elements - 1);
}
template <class T>
T OrderedList<T>::get(const T& element) const {
    for (int i = 0; i < num_elements; i++)
    {
        if (getNodeAt(i)->data == element)
        {
            return getNodeAt(i)->data;
        }
    }

    throw std::runtime_error("");
}
template <class T>
T OrderedList<T>::first() const {
    if (isEmpty())
        throw std::runtime_error("empty");
    return getNodeAt(0)->data;
}
template <class T>
T OrderedList<T>::last() const {
    if (isEmpty())
        throw std::runtime_error("empty");
    return getNodeAt(num_elements - 1)->data;
}

#endif
