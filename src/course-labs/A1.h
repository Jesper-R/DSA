#ifndef A1_HPP
#define A1_HPP
#include <algorithm>	// Included for use of std::swap()

template <class T>
int LinearSearch(T elements[], int nrOfElements, T element)
{
    for (int i = 0; i < nrOfElements; ++i) {
        if (elements[i] == element) {
            return i;
        }
    }
    return -1;
}

template <class T>
void Selectionsort(T elements[], int nrOfElements)
{
    // Implementera en iterativ selectionsort.
}

template <class T>
void Insertionsort(T elements[], int nrOfElements)
{
    // Implementera en iterativ insertionsort.
}

template <class T>
int BinarySearch(T elements[], int nrOfElements, T element)
{
    int low = 0;
    int high = nrOfElements - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (element == elements[mid])
            return mid;

        if (element < elements[mid])
            high = mid - 1;

        if (element > elements[mid])
            low = mid + 1;
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
    return (result == -1) ? -1 : result + 1; // Adjust index if found
}

template <class T>
int BinarySearchRecursive(T elements[], int nrOfElements, T element)
{
    // Implementera en rekursiv binärsökning.
    // Anropa er egna rekursiva funktion härifrån.
    return -11;
}

template <class T>
void BinaryInsertionsort(T elements[], int nrOfElements)
{
    // Implementera en iterativ insertionsort där du söker efter rätt plats att lägga in elementet m.h.a. binärsökning.
}
#endif
