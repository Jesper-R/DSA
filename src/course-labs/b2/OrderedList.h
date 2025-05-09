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

    if (front->data == element) {
        Node* toDelete = front;
        T toReturn = toDelete->data;
        front = front->next;
        delete toDelete;
        num_elements--;
        return toReturn;
    }

    Node* walker = front;
    while (walker->next != nullptr && walker->next->data != element) {
        walker = walker->next;
    }

    if (walker->next == nullptr)
        throw std::runtime_error("element not found");

    Node* toDelete = walker->next;
    T toReturn = toDelete->data;
    walker->next = toDelete->next;
    delete toDelete;
    num_elements--;
    return toReturn;
}
template <class T>
T OrderedList<T>::removeAt(int index) {
    if (index < 0 || index >= num_elements)
        throw std::runtime_error("out of bounds");

    Node* toDelete;
    T toReturn;

    if (index == 0) {
        toDelete = front;
        toReturn = toDelete->data;
        front = front->next;
    } else {
        Node* prev = getNodeAt(index - 1);
        toDelete = prev->next;
        toReturn = toDelete->data;
        prev->next = toDelete->next;
    }

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
    Node* walker = front;
    while (walker != nullptr) {
        if (walker->data == element) {
            return walker->data;
        }
        walker = walker->next;
    }
    throw std::runtime_error("element not found");
}
template <class T>
T OrderedList<T>::first() const {
    if (isEmpty())
        throw std::runtime_error("empty list");
    return getNodeAt(0)->data;
}
template <class T>
T OrderedList<T>::last() const {
    if (isEmpty())
        throw std::runtime_error("empty list");
    return getNodeAt(num_elements - 1)->data;
}

#endif
