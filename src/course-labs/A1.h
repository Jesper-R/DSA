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
    for (int j = 0; j < nrOfElements; ++j) {
        int minIndex = j;
        for (int i = j + 1; i < nrOfElements; ++i) {
            if (elements[i] < elements[minIndex]) {
                minIndex = i;
            }
        }
        std::swap(elements[j], elements[minIndex]);
    }
}

template <class T>
void Insertionsort(T elements[], int nrOfElements)
{
    // Implementera en iterativ insertionsort.
}

template <class T>
int BinarySearch(T elements[], int nrOfElements, T element)
{
    // Implementera en iterativ binärsökning.
    return -11;
}

template <class T>
int LinearSearchRecursive(T elements[], int nrOfElements, T element)
{
    // Implementera en rekursiv linjärsökning.
    // Anropa er egna rekursiva funktion härifrån.
    return -11;
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
