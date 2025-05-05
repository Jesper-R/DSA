#ifndef QUICKLOMUTO_H
#define QUICKLOMUTO_H
#include <algorithm>

template <class T>
int PartitionLomuto(T elements[], int start, int end)
{
    T pivot = elements[end];
    int i = start - 1;

    for (int j = start; j < end; j++)
    {
        if (elements[j] < pivot)
        {
            i++;
            std::swap(elements[i], elements[j]);
        }
    }

    std::swap(elements[i + 1], elements[end]);
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
