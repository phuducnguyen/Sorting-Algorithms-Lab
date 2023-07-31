#include <vector>
using namespace std;

// Utility function to swap two elements
void swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

// Selection Sort
// Time Complexity: O(n^2)
long long selectionSortComp(int* &arr, int n) {
    long long cnt = 0;
    for (int i = 0; i < n; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            cnt++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
    return cnt;
}

// Insertion Sort
// Time Complexity: O(n^2)
long long insertionSortComp(int* &arr, int n) {
    long long cnt = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            cnt++;
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    return cnt;
}

// Bubble Sort
// Time Complexity: O(n^2)
long long bubbleSortComp(int* &arr, int n) {
    long long cnt = 0;
    for (int i = 0; i < n - 1; i++) {
        bool isSwap = false;
        for (int j = 0; j < n - i - 1; j++) {
            cnt++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                isSwap = true;
            }
        }
        if (!isSwap) {
            // If no swaps occurred, the array is already sorted
            break;
        }
    }
    return cnt;
}

// Shaker Sort (Cocktail Sort)
// Time Complexity: O(n^2)
long long shakerSortComp(int* &arr, int n) {
    long long cnt = 0;
    int left = 0;
    int right = n - 1;
    int k = 0;
    while (left <= right) {
        bool isSwap = false;

        // Move the largest element to the right
        for (int j = left; j < right; j++) {
            cnt++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                isSwap = true;
                k = j;
            }
        }
        right = k;

        // Move the smallest element to the left
        for (int j = right; j > left; j--) {
            cnt++;
            if (arr[j] < arr[j - 1]) {
                swap(arr[j], arr[j - 1]);
                isSwap = true;
                k = j;
            }
        }
        left = k + 1;

        if (!isSwap) {
            // If no swaps occurred, the array is already sorted
            break;
        }
    }
    return cnt;
}

// Shell Sort
// Time Complexity: O(n log^2 n)
long long shellSortComp(int* &arr, int n) {
    long long cnt = 0;
    for (int interval = n / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= interval && arr[j - interval] > temp) {
                cnt++;
                arr[j] = arr[j - interval];
                j -= interval;
            }
            arr[j] = temp;
        }
    }
    return cnt;
}

// Heap Sort
// Time Complexity: O(n log n)
// Utility function to maintain the heap property
long long heapRebuildComp(int* &arr, int pos, int n) {
    long long cnt = 0;
    while (2 * pos + 1 < n) {
        int j = 2 * pos + 1;
        if (j < n - 1 && arr[j] < arr[j + 1]) {
            j++;
        }
        if (arr[pos] >= arr[j]) {
            // If the heap property is satisfied, no need to continue
            break;
        }
        cnt++;
        swap(arr[pos], arr[j]);
        pos = j;
    }
    return cnt;
}

// Function to construct the initial heap
long long heapConstructComp(int* &arr, int n) {
    long long cnt = 0;
    for (int i = (n - 1) / 2; i >= 0; i--) {
        cnt += heapRebuildComp(arr, i, n);
    }
    return cnt;
}

long long heapSortComp(int* &arr, int n) {
    long long cnt = 0;
    cnt += heapConstructComp(arr, n);
    int r = n - 1;
    while (r > 0) {
        cnt++;
        swap(arr[0], arr[r]);
        cnt += heapRebuildComp(arr, 0, r);
        r--;
    }
    return cnt;
}

// Merge Sort
// Time Complexity: O(n log n)
long long mergeComp(int* &arr, int first, int mid, int last) {
    long long cnt = 0;
    int n1 = mid - first + 1;
    int n2 = last - mid;
    vector<int> L(n1);
    vector<int> R(n2);
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
        cnt++;
        if (L[i] < R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
    while (i < n1) {
        arr[k++] = L[i++];
    }
    return cnt;
}

long long _mergeSortComp(int* &arr, int first, int last) {
    long long cnt = 0;
    if (first < last) {
        int mid = first + (last - first) / 2;
        cnt += _mergeSortComp(arr, first, mid);
        cnt += _mergeSortComp(arr, mid + 1, last);
        cnt += mergeComp(arr, first, mid, last);
    }
    return cnt;
}

long long mergeSortComp(int* &arr, int n) {
    return _mergeSortComp(arr, 0, n - 1);
}

// Quick Sort
// Time Complexity: O(n log n) (average case)
int partitionComp(int* &arr, int l, int r, long long &cnt) {
    int pivot = arr[(l + r) / 2];
    while (l <= r) {
        while (arr[l] < pivot) {
            l++;
            cnt++;
        }
        while (arr[r] > pivot) {
            r--;
            cnt++;
        }
        if (l <= r) {
            swap(arr[l], arr[r]);
            l++;
            r--;
        }
    }
    return l;
}

long long _quickSortComp(int* &arr, int l, int r) {
    long long cnt = 0;
    if (l < r) {
        int pi = partitionComp(arr, l, r, cnt);
        cnt += _quickSortComp(arr, l, pi - 1);
        cnt += _quickSortComp(arr, pi, r);
    }
    return cnt;
}

long long quickSortComp(int* &arr, int n) {
    return _quickSortComp(arr, 0, n - 1);
}

// Counting Sort
// Time Complexity: O(n + k), where k is the range of elements (max - min + 1)
long long countingSortComp(int* &arr, int n) {
    long long cnt = 0;
    int maxVal = arr[0];
    int minVal = arr[0];
    for (int i = 1; i < n; i++) {
        cnt++;
        maxVal = max(maxVal, arr[i]);
        minVal = min(minVal, arr[i]);
    }

    int range = maxVal - minVal + 1;
    vector<int> count(range, 0);
    vector<int> output(n, 0);

    // Count the occurrences of each element
    for (int i = 0; i < n; i++) {
        cnt++;
        count[arr[i] - minVal]++;
    }

    // Update count[i] to be the actual position of this element in the output
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }

    // Copy the output array to the original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    return cnt;
}

// Radix Sort
// Time Complexity: O(d * (n + k)), where d is the number of digits and k is the radix
long long radixSortComp(int* &arr, int n) {
    long long cnt = 0;
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        cnt++;
        maxVal = max(maxVal, arr[i]);
    }

    // Perform counting sort for every digit
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        cnt += countingSortComp(arr, n, exp);
    }
    return cnt;
}

// Flash Sort
// Time Complexity: O(n^2) (average case)
long long flashSortComp(int* &arr, int n) {
    long long cnt = 0;
    int m = int(0.45 * n); // number of partitions
    vector<int> L(m);
    int minVal = arr[0], maxIndex = 0;
    for (int i = 0; i < n; i++) {
        cnt++;
        minVal = min(minVal, arr[i]);
        if (arr[maxIndex] < arr[i]) {
            maxIndex = i;
        }
    }
    if (arr[maxIndex] == minVal) {
        return cnt;
    }

    double c = (double)(m - 1) / (arr[maxIndex] - minVal);
    // Count the elements in each partition
    for (int i = 0; i < n; i++) {
        int cls = int(c * (arr[i] - minVal));
        L[cls]++;
    }

    // Compute the starting position for each partition
    for (int i = 1; i < m; i++) {
        L[i] += L[i - 1];
    }

    // Swap elements to their correct positions
    swap(arr[maxIndex], arr[0]);
    int nmove = 0;
    int j = 0;
    int k = m - 1;
    int t = 0;
    int flash;
    while (nmove < n - 1) {
        while (j > L[k] - 1) {
            j++;
            k = int(c * (arr[j] - minVal));
        }
        flash = arr[j];
        if (k < 0) {
            break;
        }
        while (j != L[k]) {
            k = int(c * (flash - minVal));
            int hold = arr[t = --L[k]];
            arr[t] = flash;
            flash = hold;
            nmove++;
        }
    }
    cnt += insertionSortComp(arr, n);
    return cnt;
}
