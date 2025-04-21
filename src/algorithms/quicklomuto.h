#ifndef QUICKLOMUTO_H
#define QUICKLOMUTO_H
#include <algorithm>

template <class T>
int PartitionLomuto(T elements[], int start, int end)
{
    // Choose the rightmost element as pivot
    T pivot = elements[end];

    // Index of smaller element
    int i = start - 1;

    // Traverse through all elements
    // compare each element with pivot
    for (int j = start; j < end; j++)
    {
        // If current element is smaller than or equal to pivot
        if (elements[j] < pivot)
        {
            // Increment index of smaller element
            i++;
            std::swap(elements[i], elements[j]);
        }
    }

    // Place the pivot element at its correct position
    std::swap(elements[i + 1], elements[end]);

    // Return the partition index
    return i + 1;
}

template <class T>
void QuicksortLomutoRecursive(T elements[], int start, int end)
{
    if(start < end)
    {
        int pivot = PartitionLomuto(elements, start, end);
        QuicksortLomutoRecursive(elements, start, pivot-1);
        QuicksortLomutoRecursive(elements, pivot+1, end);
    }
}

template <class T>
void QuicksortLomuto(T elements[], int nrOfElements)
{
    QuicksortLomutoRecursive(elements, 0, nrOfElements-1);
}

#endif //QUICKLOMUTO_H
