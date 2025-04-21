#ifndef MERGE_H
#define MERGE_H

template <class T>
void Merge(T* elements, T* left, T* right, int nrOfElements, int leftNrOfElements, int rightNrOfElements)
{
    int i = 0, j = 0, k = 0;

    while(j < leftNrOfElements and k < rightNrOfElements)
    {
        if(left[j] <= right[k])
        {
            elements[i] = left[j++];
        }
        else
        {
            elements[i] = right[k++];
        }
        ++i;
    }

    while (j < leftNrOfElements)
        elements[i++] = left[j++];

    while (k < rightNrOfElements)
        elements[i++] = right[k++];
}

template <class T>
void Mergesort(T elements[], int nrOfElements)
{
    if(nrOfElements > 1)
    {
        int leftNrOfElements = nrOfElements / 2;
        int rightNrOfElements = nrOfElements - leftNrOfElements;

        T* left = new T[leftNrOfElements];
        T* right = new T[rightNrOfElements];

        for (int i = 0; i < leftNrOfElements; ++i)
            left[i] = elements[i];
        for (int i = 0; i < rightNrOfElements; ++i)
            right[i] = elements[i + leftNrOfElements];

        Mergesort(left, leftNrOfElements);
        Mergesort(right, rightNrOfElements);
        Merge(elements, left, right, nrOfElements, leftNrOfElements, rightNrOfElements);
    }
}

#endif //MERGE_H
