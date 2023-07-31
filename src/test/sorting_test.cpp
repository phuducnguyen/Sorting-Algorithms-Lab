#include "../include/DataGenerator.h"
#include "../include/Sorting.h"

#include <algorithm> // sort in c++ library
#include <map>
#include <string>
#include <functional>

// uncomment to disable assert()
// #define NDEBUG
#include <cassert>

void generate(int* &a1, int* &a2, int n) {
    for (int i = 0; i < n; i++) {
        int val = rand() % (n + 1);
        a1[i] = val;
        a2[i] = val;
    }
}

bool compare(int* a1, int* a2, int n) {
    for (int i = 0; i < n; i++) {
        if(a1[i] != a2[i])
            return false;
        }    
    return true;
}

int main() {
    srand((unsigned int)time(NULL));
    std::map<std::string, std::function<void(int* &, int)>> sort_algo;
    sort_algo["selection"] = selectionSort;
    sort_algo["insertion"] = insertionSort;
    sort_algo["bubble"] = bubbleSort;
    sort_algo["shaker"] = shakerSort;
    sort_algo["shell"] = shellSort;
    sort_algo["heap"] = heapSort;
    sort_algo["merge"] = mergeSort;
    sort_algo["quick"] = quickSort;
    sort_algo["counting"] = countingSort;
    sort_algo["radix"] = radixSort;
    sort_algo["flash"] = flashSort;

    for (auto it : sort_algo) {
        std::cout << "Testing on " << it.first << " sort ... ";
        int n = 1000;
        int* a1 = new int[n];
        int* a2 = new int[n];
        generate(a1, a2, n);

        it.second(a1, n);
        std::sort(a2, a2 + n);

        assert(compare(a1, a2,n) == true);
        std::cout << "Oh yes, Passed!\n";
        
        delete[] a1;
        delete[] a2;
    }
}