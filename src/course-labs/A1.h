#ifndef A1_HPP
#define A1_HPP
#include <algorithm>	// Included for use of std::swap()

template <class T>
int LinearSearch(T elements[], int nrOfElements, T element)
{
    for (int i = 0; i < nrOfElements; ++i) {
        if (elements[i] == element)
            return i;
    }
    return -1;
}

template <class T>
void Selectionsort(T elements[], int nrOfElements)
{
	int i, j, min_idx;

    // One by one move boundary of
    // unsorted subarray
    for (i = 0; i < nrOfElements-1; i++)
    {

        // Find the minimum element in
        // unsorted array
        min_idx = i;
        for (j = i+1; j < nrOfElements; j++)
        if (elements[j] < elements[min_idx])
            min_idx = j;

        // Swap the found minimum element
        // with the first element
        std::swap(elements[min_idx], elements[i]);
    }
}

template <class T>
void Insertionsort(T elements[], int nrOfElements)
{
    // Start from the second element, as the first element is trivially sorted
    for (int i = 1; i < nrOfElements; i++) {
        T key = elements[i];   // The element to be inserted
        int j = i - 1;

        // Move elements of elements[0..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && elements[j] > key) {
            elements[j + 1] = elements[j];  // Shift element to the right
            j = j - 1;
        }

        // Insert the key into the correct position
        elements[j + 1] = key;
    }
}


template <class T>
int BinarySearch(T elements[], int nrOfElements, T element)
{
    int low = 0;
    int high = nrOfElements - 1;

    while (low <= high) {
        // Calculate mid in a way that prevents overflow
        int mid = (low + high) / 2;

        // Comparison for element at mid
        if (elements[mid] == element) {
            return mid;
        }
        // Adjust the range based on comparison
        if (element < elements[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}


template <class T>
int LinearSearchRecursive(T elements[], int nrOfElements, T element) {
    if (nrOfElements == 0) {
        return -1; // Element not found
    }
    if (elements[0] == element) {
        return 0; // Element found at the first position
    }

    int result = LinearSearchRecursive(elements + 1, nrOfElements - 1, element);
    if (result == -1)
        return -1;

    return result + 1;
}

template <class T>
int BinarySearchRecursiveHelper(T elements[], int low, int high, T element) {
    if (low > high) {
        return -1; // Base case: element not found
    }

    int mid = (low + high) / 2;

    if (elements[mid] == element) {
        return mid; // Element found
    }
    if (element < elements[mid]) {
        return BinarySearchRecursiveHelper(elements, low, mid - 1, element); // Search left half
    }

    return BinarySearchRecursiveHelper(elements, mid + 1, high, element); // Search right half
}

template <class T>
int BinarySearchRecursive(T elements[], int nrOfElements, T element) {
    return BinarySearchRecursiveHelper(elements, 0, nrOfElements - 1, element);
}

//overkill
template <class T>
void BinaryInsertionsort(T elements[], int nrOfElements)
{
	// Implementera en iterativ insertionsort där du söker efter rätt plats att lägga in elementet m.h.a. binärsökning.
}
#endif
