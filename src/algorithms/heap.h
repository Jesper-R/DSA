#ifndef HEAP_H
#define HEAP_H
#include <algorithm>

// Helper function to "heapify" a subtree rooted at index i
template <class T>
void Heapify(T elements[], int n, int i)
{
    int largest = i;         // Initialize largest as root
    int left = 2 * i + 1;    // left child
    int right = 2 * i + 2;   // right child

    // If left child is larger than root
    if (left < n && elements[left] > elements[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && elements[right] > elements[largest])
        largest = right;

    // If largest is not root
    if (largest != i)
    {
        std::swap(elements[i], elements[largest]);

        // Recursively heapify the affected subtree
        Heapify(elements, n, largest);
    }
}

// Main Heapsort function
template <class T>
void Heapsort(T elements[], int nrOfElements)
{
    // Step 1: Build a max heap
    for (int i = nrOfElements / 2 - 1; i >= 0; i--)
        Heapify(elements, nrOfElements, i);

    // Step 2: One by one extract elements from heap
    for (int i = nrOfElements - 1; i > 0; i--)
    {
        // Move current root to end
        std::swap(elements[0], elements[i]);

        // Call max heapify on the reduced heap
        Heapify(elements, i, 0);
    }
}

#endif //HEAP_H
