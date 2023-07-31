#include "include/Sorting.h"
#include <vector>
#include <algorithm> // For std::max and std::min

// Utility function to swap two elements
void _swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

// Selection Sort
void selectionSort(int* &arr, int n) {
    for (int i = 0; i < n; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                _swap(arr[i], arr[j]);
            }
        }
    }
}

// Insertion Sort
void insertionSort(int* &arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Bubble Sort
void bubbleSort(int* &arr, int n) {
    for (int i = n - 1; i >= 0; i--) {
        bool isSwap = false;
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                isSwap = true;
                _swap(arr[j], arr[j + 1]);
            }
        }
        if (!isSwap) {
            return;	// If no swap occurs in a pass, the array is already sorted
        }
    }
}

// Shaker Sort (Cocktail Sort)
void shakerSort(int* &arr, int n) {
    int left = 0;
    int right = n - 1;
    int k = 0;
    for (int i = left; i <= right; i++) {
        bool isSwap = false;

        for (int j = left; j < right; j++) {
            if (arr[j] > arr[j + 1]) {
                isSwap = true;
                _swap(arr[j], arr[j + 1]);
                k = j;
            }
        }
        if (!isSwap) {
            return; // If no swap occurs in a pass, the array is already sorted
        }
        right = k;

        isSwap = false;
        for (int j = right; j > left; j--) {
            if (arr[j] < arr[j - 1]) {
                isSwap = true;
                _swap(arr[j], arr[j - 1]);
                k = j;
            }
        }
        if (!isSwap) {
            return; // If no swap occurs in a pass, the array is already sorted
        }
        left = k;
    }
}

// Shell Sort
void shellSort(int* &arr, int n) {
    // Rearrange elements at each n/2, n/4, n/8 ... intervals
    for (int interval = n / 2; interval > 0; interval /= 2) {
    	for (int i = interval; i < n; ++i) {
    		int temp = arr[i];
    		int j;
    		for (j = i; j >= interval && arr[j - interval] > temp; j -= interval) {
    			arr[j] = arr[j - interval];
			}
			arr[j] = temp;
		}
	}
}

/* ----------------- Heap Sort ----------------- */
void heapRebuild(int* &arr, int pos, int n) {
    while (2 * pos + 1 < n) {
        int j = 2 * pos + 1;
        if (j < n - 1 && arr[j] < arr[j + 1]) {
            j++;
        }
        if (arr[pos] >= arr[j]) {
            return;
        }
        _swap(arr[pos], arr[j]);
        pos = j;
    }
}

void heapConstruct(int* &arr, int n) {
    for (int i = (n - 1) / 2; i >= 0; i--) {
        heapRebuild(arr, i, n);
    }
}

void heapSort(int* &arr, int n) {
    heapConstruct(arr, n);
    int r = n - 1;
    while (r > 0) {
        _swap(arr[0], arr[r]);
        heapRebuild(arr, 0, r);
        r--;
    }
}
/* ----------------------------------------------- */

/* ----------------- Merge Sort ----------------- */
void merge(int* &arr, int first, int mid, int last) {
    int n1 = mid - first + 1;
    int n2 = last - mid;
    int *L = new int[n1];
    int *R = new int[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = arr[first + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + j + 1];
    }
    int i = 0;
    int j = 0;
    int k = first;
    while (i < n1 && j < n2) {
        arr[k++] = (L[i] < R[j]) ? L[i++] : R[j++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
    while (i < n1) {
        arr[k++] = L[i++];
    }
    delete[] L;
    delete[] R;
}

void _mergeSort(int* &arr, int first, int last) {
    if (first < last) {
        int mid = first + (last - first) / 2;
        _mergeSort(arr, first, mid);
        _mergeSort(arr, mid + 1, last);
        merge(arr, first, mid, last);
    }
}

void mergeSort(int* &arr, int n) {
    _mergeSort(arr, 0, n - 1);
}
/* ----------------------------------------------- */

/* ----------------- Quick Sort ----------------- */
int partition(int* &arr, int l, int r) {
    int pivot = arr[(l + r) / 2];
    while (l <= r) {
        while (arr[l] < pivot) {
            l++;
        }
        while (arr[r] > pivot) {
            r--;
        }
        if (l <= r) {
            _swap(arr[l], arr[r]);
            l++;
            r--;
        }
    }
    return l;
}

void _quickSort(int* &arr, int l, int r) {
    if (l < r) {
        int pivot = partition(arr, l, r);
        _quickSort(arr, l, pivot - 1);
        _quickSort(arr, pivot, r);
    }
}

void quickSort(int* &arr, int n) {
    _quickSort(arr, 0, n - 1);
}
/* ----------------------------------------------- */

/* ----------------- Counting Sort ----------------- */
void countingSort(int* &arr, int n, int exp) {
    int* out = new int[n];
    int* count = new int[10];

    for (int i = 0; i < n; i++)
        out[i] = 0;
    for (int i = 0; i < 10; i++)
        count[i] = 0;

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        out[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++)
        arr[i] = out[i];

    delete[] out, count;
}

void countingSort(int* &arr, int n) {
    int maxVal = *std::max_element(arr, arr + n);
    int* count = new int[maxVal + 1];
    for (int i = 0; i <= maxVal; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    int curId = 0;
    for (int i = 0; i <= maxVal; i++) {
        while (count[i]--) {
            arr[curId] = i;
            curId++;
        }
    }
    delete[] count;
}
/* ----------------------------------------------- */

/* ----------------- Radix Sort ----------------- */
void radixSort(int* &arr, int n) {
    int maxVal = *std::max_element(arr, arr + n);
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSort(arr, n, exp);
    }
}
/* ----------------------------------------------- */

/* ----------------- Flash Sort ----------------- */
void flashSort(int* &arr, int n) {
    int m = int(0.45 * n); // number of partitions
    std::vector<int> l(m);
    int minVal = arr[0], maxIndex = 0;
    for (int i = 0; i < n; i++) {
        minVal = std::min(minVal, arr[i]);
        if (arr[maxIndex] < arr[i]) {
            maxIndex = i;
        }
    }
    if (arr[maxIndex] == minVal) {
        return;	// If all elements are equal, the array is already sorted
    }

    double c = (double)(m - 1) / (arr[maxIndex] - minVal);
    for (int i = 0; i < n; i++) {
        int cls = int(c * (arr[i] - minVal));
        l[cls]++;
    }
    for (int i = 1; i < m; i++) {
        l[i] += l[i - 1];
    }

    _swap(arr[maxIndex], arr[0]);

    int nmove = 0;
    int j = 0;
    int k = m - 1;
    int t = 0;
    int flash;
    while (nmove < n - 1) {
        while (j > l[k] - 1) {
            j++;
            k = int(c * (arr[j] - minVal));
        }
        flash = arr[j];
        if (k < 0) break;
        while (j != l[k]) {
            k = int(c * (flash - minVal));
            int hold = arr[t = --l[k]];
            arr[t] = flash;
            flash = hold;
            ++nmove;
        }
    }
    insertionSort(arr, n);	// Use insertion sort to finalize the sorting
}
