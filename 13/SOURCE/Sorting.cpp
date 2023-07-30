#include "include/Sorting.h"

void selectionSort(int* &a, int n) {
	for (int i = 0; i < n; i++) {
		int minIndex = i;
		for (int j = i + 1; j < n; j++) {
			if (a[j] < a[i]) {
				_swap(a[i], a[j]);
			}
		}
	}
}

void insertionSort(int* &a, int n) {
	for (int i = 1; i < n; i++) {
		int k = i - 1;
		int key = a[i];
		while (a[k] > key && key >= 0) {
			a[k + 1] = a[k];
			k--;
		}
		a[k + 1] = key;
	}
}

void bubbleSort(int* &a, int n) {
	for (int i = n - 1; i >= 0; i--) {
		bool isSwap = false;
		for (int j = 0; j < i; j++) {
			if (a[j] > a[j + 1]) {
				isSwap = true;
				_swap(a[j], a[j + 1]);
			}
			if (!isSwap)
				return;
		}
	}
}

void shakerSort(int* &a, int n) {
	int left = 0;
	int right = n - 1;
	int k = 0;
	for (int i = left; i <= right; i++) {
		bool isSwap = false;

		for (int j = left; j < right; j++) {
			if (a[j] > a[j + 1]) {
				isSwap = true;
				_swap(a[j], a[j + 1]);
				k = j;
			}
		}
		if (!isSwap) return;
		right = k;

		isSwap = false;
		for (int j = right; j > left; j--) {
			if (a[j] < a[j - 1]) {
				isSwap = true;
				_swap(a[j], a[j - 1]);
				k = j;
			}
		}
		if (!isSwap) return;
		left = k;
	}
}

void shellSort(int* &a, int n) {
	for (int interval = n / 2; interval > 0; interval /= 2) {
		for (int i = interval; i < n; i++) {
			int temp = a[i];
			int j = i;
			for (int j = i; j >= interval && a[j - interval] > temp; j -= interval) {
				a[j] = a[j - interval];
			} 
			a[j] = temp;
		}
	}
}

/* ---------------------------------------------------------------------- */
void heapRebuild(int* &a, int pos, int n){
	while (2 * pos + 1 < n)
	{
		int j = 2 * pos + 1;
		if (j < n - 1)
			if (a[j] < a[j + 1])
				j = j + 1;
		if (a[pos] >= a[j])
			return;
		_swap(a[pos], a[j]);
		pos = j;
	}
}
void heapConstruct(int* &a, int n){
	for (int i = (n - 1) / 2; i >= 0; i--)
		heapRebuild(a, i, n);
}

void heapSort(int* &a, int n){
	heapConstruct(a, n);
	int r = n - 1;
	while (r > 0){
		_swap(a[0], a[r]);
		heapRebuild(a, 0, r);
		r--;
	}
}
/* ---------------------------------------------------------------------- */
void merge(int* &a, int first, int mid, int last){
	int n1 = mid - first + 1;
	int n2 = last - mid;
	int *L = new int[n1];
	int *R = new int[n2];
	for (int i = 0; i < n1; i++)
		L[i] = a[first + i];
	for (int j = 0; j < n2; j++)
		R[j] = a[mid + j + 1];
	int i = 0;
	int j = 0;
	int k = first;
	while (i < n1 && j < n2)
		a[k++] = (L[i] < R[j]) ? L[i++] : R[j++];

	while (j < n2)
		a[k++] = R[j++];
	while (i < n1)
		a[k++] = L[i++];
	delete[] L;
	delete[] R;
}

void _mergeSort(int* &a, int first, int last){
	if (first < last){
		int mid = first + (last - first) / 2;
		_mergeSort(a, first, mid);
		_mergeSort(a, mid + 1, last);
		merge(a, first, mid, last);
	}
}

void mergeSort(int* &a, int n){
	_mergeSort(a, 0, n-1);
}
/* ---------------------------------------------------------------------- */
int partition(int* &a, int l, int r){
    int pivot = a[(l+r)/2]; 
    while(l <= r){
        while(a[l] < pivot)
            l++;
        while(a[r] > pivot)
            r--;
        if(l <= r){
            swap(a[l], a[r]);
            l++;
            r--;
        }
    }
    return l;
}

void _quickSort(int* &a, int l, int r){
    if (l < r){
        int pi = partition(a, l, r);
        _quickSort(a, l, pi - 1);
        _quickSort(a, pi, r);
    }
}

void quickSort(int* &a, int n){
	_quickSort(a, 0, n-1);
}
/* ---------------------------------------------------------------------- */

void countingSort(int* &a, int n, int exp){
	int* out = new int[n];
	int* count = new int[10];

	for(int i = 0; i < n; i++)
		out[i] = 0;
	for(int i = 0; i < 10; i++)
		count[i] = 0;
    
    for(int i = 0; i < n; i++)
        count[(a[i]/exp)%10]++;
    for(int i = 1; i < 10; i++)
        count[i] += count[i-1];
    
    for(int i = n - 1; i >= 0; i--){
        out[count[(a[i]/exp)%10] - 1] = a[i];
        count[(a[i]/exp)%10]--;
    }
    for(int i = 0; i < n; i++)
        a[i] = out[i];

	delete[] out, count;
}

void countingSort(int* &a, int n){
	int maxVal = 0;
	for(int i = 0; i < n; i++)
		if(a[i] > maxVal)
			maxVal = a[i];
	int* count  = new int[maxVal + 1];
	for(int i = 0; i <= maxVal; i++)
		count[i] = 0;
	for(int i = 0; i < n; i++)
		count[a[i]]++;
	
	int curId = 0;
	for(int i = 0; i <= maxVal; i++)
		while(count[i]--){
			a[curId] = i;
			curId++;
		}
	delete[] count;
}
/* ---------------------------------------------------------------------- */
void radixSort(int* &a, int n){
    int maxVal = a[0];
    for(int i = 0; i < n; i++)
        maxVal = max(maxVal, a[i]);
    for(int exp = 1; maxVal/exp > 0; exp *= 10){
        countingSort(a, n, exp);
    }
}
/* ---------------------------------------------------------------------- */
void flashSort(int* &a, int n){
    int m = int(0.45*n); // number of partitions
    vector <int> l(m);
    int minVal = a[0], maxIndex = 0;
    for(int i = 0; i < n; i++){
        minVal = min(minVal, a[i]);
        if(a[maxIndex] < a[i])
            maxIndex = i;
    }
    if(a[maxIndex] == minVal)
        return;
    
    double c = (double)(m - 1)/(a[maxIndex] - minVal);
    for(int i = 0; i < n; i++){
        int cls = int(c*(a[i] - minVal));
        l[cls]++;
    }
    for(int i = 1; i < m; i++)
        l[i] += l[i-1];

    _swap(a[maxIndex], a[0]);

    int nmove = 0;
	int j = 0;
	int k = m - 1;
	int t = 0;
	int flash;
	while (nmove < n - 1){
		while (j > l[k] - 1){
			j++;
			k = int(c*(a[j] - minVal));
		}
		flash = a[j];
		if (k < 0) break;
		while (j != l[k]){
			k = int(c*(flash - minVal));
			int hold = a[t = --l[k]];
			a[t] = flash;
			flash = hold;
			++nmove;
		}
	}
    insertionSort(a, n);
}