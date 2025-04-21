#ifndef A2_HPP
#define A2_HPP

#include <algorithm>

template <class T>
void Merge(T* elements, T* left, T* right, int nrOfElements, int leftNrOfElements, int rightNrOfElements)
{
    int i = 0, j = 0, k = 0;

    while(j < leftNrOfElements and k < rightNrOfElements)
    {
        if(left[j] <= right[k])
        {
            elements[i] = left[j];
            ++j;
        }
        else
        {
            elements[i] = right[k];
            ++k;
        }
        ++i;
    }

    while(j < leftNrOfElements)
    {
        elements[i] = left[j];
        ++i;
        ++j;
    }
    while(k < rightNrOfElements)
    {
        elements[i] = right[k];
        ++i;
        ++k;
    }
}

template <class T>
void Mergesort(T elements[], int nrOfElements)
{
    if(nrOfElements <= 1)
        return;

    int mid = nrOfElements / 2;

    // Create temporary arrays for left and right halves
    T* left = new T[mid];
    T* right = new T[nrOfElements - mid];

    // Copy data to temporary arrays
    for(int i = 0; i < mid; ++i)
        left[i] = elements[i];
    for(int i = mid; i < nrOfElements; ++i)
        right[i - mid] = elements[i];

    // Recursive calls
    Mergesort(left, mid);
    Mergesort(right, nrOfElements - mid);
    // Merge sorted halves
    Merge(elements, left, right, nrOfElements, mid, nrOfElements - mid);

    // Clean up
    delete[] left;
    delete[] right;
}

template <class T>
void MergeBook(T elements[], int start, int mid, int end)
{
    // Calculate sizes of subarrays
    int n1 = mid - start + 1;
    int n2 = end - mid;

    // Create temporary arrays
    T* L = new T[n1];
    T* R = new T[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        L[i] = elements[start + i];
    for (int j = 0; j < n2; j++)
        R[j] = elements[mid + 1 + j];

    // Merge the temporary arrays back into elements[start..end]
    int i = 0;    // Initial index of first subarray
    int j = 0;    // Initial index of second subarray
    int k = start; // Initial index of merged subarray

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            elements[k] = L[i];
            i++;
        }
        else
        {
            elements[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        elements[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        elements[k] = R[j];
        j++;
        k++;
    }

    // Free dynamic memory
    delete[] L;
    delete[] R;
}

template <class T>
void MergesortBookRecursive(T elements[], int start, int end)
{
    if (start < end)
    {
        // Find the middle point
        int mid = (start + end) / 2;

        // Sort first and second halves
        MergesortBookRecursive(elements, start, mid);
        MergesortBookRecursive(elements, mid + 1, end);

        // Merge the sorted halves
        MergeBook(elements, start, mid, end);
    }
}

template <class T>
void MergesortBook(T elements[], int nrOfElements)
{
    // Call the recursive implementation with inclusive end index
    // Book variant uses inclusive end index, so we subtract 1 from nrOfElements
    MergesortBookRecursive(elements, 0, nrOfElements - 1);
}

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

template <class T>
void QuicksortHoareImproved(T elements[], int nrOfElements)
{
    // NOT NEEDED
}

template <class T>
int MedianOfThree(T elements[], int start, int end)
{
    /*int mid = (start+end)/2;
    if((elements[start] <= elements[mid] && elements[mid] <= elements[end]) || (elements[start] >= elements[mid] and elements[mid] >= elements[end]))
        return mid;
    if((elements[mid] <= elements[start] && elements[start] <= elements[end]) || (elements[mid] >= elements[start] and elements[start] >= elements[end]))
        return start;
    return end;*/
}

template <class T>
void QuicksortHoareImprovedMedian3(T elements[], int nrOfElements)
{
    // NOT NEEDED
}


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

#endif
