#ifndef QUICKHOARE_H
#define QUICKHOARE_H
#include <algorithm>

template <class T>
int PartitionHoare(T elements[], int start, int end)
{
    // Choose the first element as pivot
    T pivot = elements[start];

    int i = start;
    int j = end;

    while (true)
    {
        // Move i to the right as long as elements[i] < pivot
        while (elements[i] < pivot) {
            i++;
        }

        // Move j to the left as long as elements[j] > pivot
        while (elements[j] > pivot) {
            j--;
        }

        // If the pointers have crossed, return the partition index
        if (i >= j)
            return j;

        // Swap out-of-place elements
        std::swap(elements[i], elements[j]);

        // Move pointers to avoid infinite loop if elements[i] == elements[j]
        i++;
        j--;
    }
}

template <class T>
void QuicksortHoareRecursive(T elements[], int start, int end)
{
    if(start < end)
    {
        int pivot = PartitionHoare(elements, start, end);
        QuicksortHoareRecursive(elements, start, pivot);
        QuicksortHoareRecursive(elements, pivot+1, end);
    }
}

template <class T>
void QuicksortHoare(T elements[], int nrOfElements)
{
    QuicksortHoareRecursive(elements, 0, nrOfElements-1);
}

#endif //QUICKHOARE_H
