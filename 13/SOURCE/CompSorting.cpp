#include "include/CompSorting.h"

/* ---------------------------------------------------------------------- */
ll selectionSortComp(int* &a, int n){
    ll cnt = 0;
    for (int i = 0; ++cnt && i < n; i++){
		int minIndex = i;
		for (int j = i+1; ++cnt && j < n; j++)
			if (++cnt && a[j] < a[i]){
				_swap(a[i], a[j]);
			}
	}
    return cnt;
}
/* ---------------------------------------------------------------------- */
ll insertionSortComp(int* &a, int n){
    ll cnt = 0;
	for (int i = 1; ++cnt && i < n; i++){
		int k = i - 1;
		int key = a[i];
		while ((++cnt && a[k] > key) && (++cnt && k >= 0)){
			a[k + 1] = a[k];
			k--;
		}
		a[k + 1] = key;
	}
    return cnt;
}
/* ---------------------------------------------------------------------- */
ll bubbleSortComp(int* &a, int n){
    ll cnt = 0;
	for (int i = n - 1; ++cnt && i >= 0; i--){
		bool isSwap = false;
		for (int j = 0; ++cnt && j < i; j++)
			if (++cnt && a[j] > a[j + 1]){
				isSwap = true;
				_swap(a[j], a[j + 1]);
			}
		if (++cnt && !isSwap)
			return cnt;
	}
    return cnt;
}
/* ---------------------------------------------------------------------- */
ll shakerSortComp(int* &a, int n){
    ll cnt = 0;
	int left = 0;
	int right = n - 1;
	int k = 0;
	for (int i = left; ++cnt && i <= right; i++){
		bool isSwap = false;
		
		for (int j = left; ++cnt && j < right; j++)
			if (++cnt && a[j] > a[j + 1]){
				isSwap = true;
				_swap(a[j], a[j + 1]);
				k = j;
			}
		if (++cnt && !isSwap)
			return cnt;
		right = k;
		
		isSwap = false;
		for (int j = right; ++cnt && j > left; j--)
			if (++cnt && a[j] < a[j - 1]){
				isSwap = true;
				_swap(a[j], a[j - 1]);
				k = j;
			}
		if (++cnt && !isSwap)
			return cnt;
		left = k;
	}
    return cnt;
}
/* ---------------------------------------------------------------------- */
ll shellSortComp(int* &a, int n){
    ll cnt = 0;
	for (int interval = n / 2; ++cnt && interval > 0; interval /= 2){
		for (int i = interval; i < n; i++){
			int temp = a[i];
			int j = i;
			for (j = i; (++cnt && j >= interval) && (++cnt && a[j - interval] > temp); j -= interval)
				a[j] = a[j - interval];
			a[j] = temp;
		}
	}
    return cnt;
}
/* ---------------------------------------------------------------------- */
ll heapRebuildComp(int* &a, int pos, int n){
    ll cnt = 0;
	while (++cnt && 2 * pos + 1 < n)
	{
		int j = 2 * pos + 1;
		if (++cnt && j < n - 1)
			if (++cnt && a[j] < a[j + 1])
				j = j + 1;
		if (++cnt && a[pos] >= a[j])
			return cnt;
		_swap(a[pos], a[j]);
		pos = j;
	}
    return cnt;
}
ll heapConstructComp(int* &a, int n){
    ll cnt = 0;
	for (int i = (n - 1) / 2; ++cnt && i >= 0; i--)
		cnt += heapRebuildComp(a, i, n);
    return cnt;
}

ll heapSortComp(int* &a, int n){
    ll cnt = 0;
	cnt += heapConstructComp(a, n);
	int r = n - 1;
	while (++cnt && r > 0){
		_swap(a[0], a[r]);
		cnt += heapRebuildComp(a, 0, r);
		r--;
	}
    return cnt;
}
/* ---------------------------------------------------------------------- */
ll mergeComp(int* &a, int first, int mid, int last){
    ll cnt = 0;
	int n1 = mid - first + 1;
	int n2 = last - mid;
	int *L = new int[n1];
	int *R = new int[n2];
	for (int i = 0; ++cnt && i < n1; i++)
		L[i] = a[first + i];
	for (int j = 0; ++cnt && j < n2; j++)
		R[j] = a[mid + j + 1];
	int i = 0;
	int j = 0;
	int k = first;
	while ((++cnt && i < n1) && (++cnt && j < n2))
		a[k++] = (L[i] < R[j]) ? L[i++] : R[j++];

	while (++cnt && j < n2)
		a[k++] = R[j++];
	while (++cnt && i < n1)
		a[k++] = L[i++];
	delete[] L;
	delete[] R;
    return cnt;
}

ll _mergeSortComp(int* &a, int first, int last){
    ll cnt = 0;
	if (++cnt && first < last){
		int mid = first + (last - first) / 2;
		cnt += _mergeSortComp(a, first, mid);
		cnt += _mergeSortComp(a, mid + 1, last);
		cnt += mergeComp(a, first, mid, last);
	}
    return cnt;
}

ll mergeSortComp(int* &a, int n){
	return _mergeSortComp(a, 0, n-1);
}
/* ---------------------------------------------------------------------- */
int partitionComp(int* &a, int l, int r, ll &cnt){
    int pivot = a[(l+r)/2]; 
    while(++cnt && l <= r){
        while(++cnt && a[l] < pivot)
            l++;
        while(++cnt && a[r] > pivot)
            r--;
        if(++cnt && l <= r){
            swap(a[l], a[r]);
            l++;
            r--;
        }
    }
    return l;
}

ll _quickSortComp(int* &a, int l, int r){
    ll cnt = 0;
    if (++cnt && l < r){
        int pi = partitionComp(a, l, r, cnt);
        cnt += _quickSortComp(a, l, pi - 1);
        cnt += _quickSortComp(a, pi, r);
    }
    return cnt;
}

ll quickSortComp(int* &a, int n){
	return _quickSortComp(a, 0, n-1);
}
/* ---------------------------------------------------------------------- */

ll countingSortComp(int* &a, int n, int exp){
    ll cnt = 0;
	int* out = new int[n];
	int* count = new int[10];

	for(int i = 0; ++cnt && i < n; i++)
		out[i] = 0;
	for(int i = 0; ++cnt && i < 10; i++)
		count[i] = 0;
    
    for(int i = 0; ++cnt && i < n; i++)
        count[(a[i]/exp)%10]++;
    for(int i = 1; ++cnt && i < 10; i++)
        count[i] += count[i-1];
    
    for(int i = n - 1; ++cnt && i >= 0; i--){
        out[count[(a[i]/exp)%10] - 1] = a[i];
        count[(a[i]/exp)%10]--;
    }
    for(int i = 0; ++cnt && i < n; i++)
        a[i] = out[i];

	delete[] out, count;
    return cnt;
}

ll countingSortComp(int* &a, int n){
    ll cnt = 0;
	int maxVal = 0;
	for(int i = 0; ++cnt && i < n; i++)
		if(++cnt && a[i] > maxVal)
			maxVal = a[i];
	int* count  = new int[maxVal + 1];
	for(int i = 0; ++cnt && i <= maxVal; i++)
		count[i] = 0;
	for(int i = 0; ++cnt && i < n; i++)
		count[a[i]]++;
	
	int curId = 0;
	for(int i = 0; i <= maxVal; i++)
		while(++cnt && count[i]--){
			a[curId] = i;
			curId++;
		}
	delete []count;
    return cnt;
}
/* ---------------------------------------------------------------------- */
ll radixSortComp(int* &a, int n){
    ll cnt = 0;
    int maxVal = a[0];
    for(int i = 0; ++cnt && i < n; i++)
        maxVal = max(maxVal, a[i]);
    for(int exp = 1; ++cnt && maxVal/exp > 0; exp *= 10){
        cnt += countingSortComp(a, n, exp);
    }
    return cnt;
}
/* ---------------------------------------------------------------------- */
ll flashSortComp(int* &a, int n){
    ll cnt = 0;
    int m = int(0.45*n); // number of partitions
    vector <int> l(m);
    int minVal = a[0], maxIndex = 0;
    for(int i = 0; ++cnt && i < n; i++){
        minVal = min(minVal, a[i]);
        if(++cnt && a[maxIndex] < a[i])
            maxIndex = i;
    }
    if(++cnt && a[maxIndex] == minVal)
        return cnt;
    
    double c = (double)(m - 1)/(a[maxIndex] - minVal);
    for(int i = 0; ++cnt && i < n; i++){
        int cls = int(c*(a[i] - minVal));
        l[cls]++;
    }
    for(int i = 1; ++cnt && i < m; i++)
        l[i] += l[i-1];

    _swap(a[maxIndex], a[0]);

    int nmove = 0;
	int j = 0;
	int k = m - 1;
	int t = 0;
	int flash;
	while (++cnt && nmove < n - 1){
		while (++cnt && j > l[k] - 1){
			j++;
			k = int(c*(a[j] - minVal));
		}
		flash = a[j];
		if (++cnt && k < 0) break;
		while (++cnt && j != l[k]){
			k = int(c*(flash - minVal));
			int hold = a[t = --l[k]];
			a[t] = flash;
			flash = hold;
			++nmove;
		}
	}
    cnt += insertionSortComp(a, n);
    return cnt;
}