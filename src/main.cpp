#include "include/DataGenerator.h"
#include "include/Sorting.h"
#include "include/CompSorting.h"
#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include <chrono>
#include <fstream>
#include <cassert>
#include <functional>
#include <ctime>
#include <vector>

using namespace std;

// Function to check if the input argument is a file name
bool isFile(string arg) {
    for (char ch : arg)
        if (ch == '.')
            return true;
    return false;
}

// Input arguments
string algorithm, algorithm1, algorithm2;
string inputFile;
string outputParam;
int inputSize;
string inputOrder;

// Parse the command-line arguments
int parseArgs(int argc, char** argv) {
    if (argc == 1) {
        cout << "\nNo extra command found!";
        return 0;
    }
    if (!strcmp(argv[1], "-exp")) // experiment option
        return 0;

    assert(!strcmp(argv[1], "-a") || !strcmp(argv[1], "-c"));
    if (!strcmp(argv[1], "-a")) {
        assert(argc == 5 || argc == 6);
        if (argc == 5) {
            if (isFile(argv[3])) {
                // [Execution file] -a [Algorithm] [Given input] [Output parameter(s)]
                algorithm = argv[2];
                inputFile = argv[3];
                outputParam = argv[4];
                return 1;
            }
            else {
                // [Execution file] -a [Algorithm] [Input size] [Output parameter(s)]
                algorithm = argv[2];
                inputSize = stoi(argv[3]); // convert string to int
                outputParam = argv[4];
                return 3;
            }
        }
        if (argc == 6) {
            // [Execution file] -a [Algorithm] [Input size] [Input order] [Output parameter(s)]
            algorithm = argv[2];
            inputSize = stoi(argv[3]); // convert string to int
            inputOrder = argv[4];
            outputParam = argv[5];
            return 2;
        }
    }
    else {
        assert(argc == 5 || argc == 6);
        if (argc == 5) {
            algorithm1 = argv[2];
            algorithm2 = argv[3];
            inputFile = argv[4];
            return 4;
        }
        else {
            algorithm1 = argv[2];
            algorithm2 = argv[3];
            inputSize = stoi(argv[4]); // convert string to int
            inputOrder = argv[5];
            return 5;
        }
    }
    return 0;
}

// Maps to store sorting algorithms and their comparison functions
map<string, function<void(int*&, int)>> sortAlgorithms;
map<string, function<long long(int*&, int)>> sortAlgorithmsWithComparison;
map<string, int> inputOrderMap;
map<string, string> dataTypeName;

// Initialize the sorting algorithms and input order map
void init() {
    sortAlgorithms["selection-sort"] = selectionSort;
    sortAlgorithms["insertion-sort"] = insertionSort;
    sortAlgorithms["bubble-sort"] = bubbleSort;
    sortAlgorithms["shaker-sort"] = shakerSort;
    sortAlgorithms["shell-sort"] = shellSort;
    sortAlgorithms["heap-sort"] = heapSort;
    sortAlgorithms["merge-sort"] = mergeSort;
    sortAlgorithms["quick-sort"] = quickSort;
    sortAlgorithms["counting-sort"] = countingSort;
    sortAlgorithms["radix-sort"] = radixSort;
    sortAlgorithms["flash-sort"] = flashSort;

    sortAlgorithmsWithComparison["selection-sort"] = selectionSortComp;
    sortAlgorithmsWithComparison["insertion-sort"] = insertionSortComp;
    sortAlgorithmsWithComparison["bubble-sort"] = bubbleSortComp;
    sortAlgorithmsWithComparison["shaker-sort"] = shakerSortComp;
    sortAlgorithmsWithComparison["shell-sort"] = shellSortComp;
    sortAlgorithmsWithComparison["heap-sort"] = heapSortComp;
    sortAlgorithmsWithComparison["merge-sort"] = mergeSortComp;
    sortAlgorithmsWithComparison["quick-sort"] = quickSortComp;
    sortAlgorithmsWithComparison["counting-sort"] = countingSortComp;
    sortAlgorithmsWithComparison["radix-sort"] = radixSortComp;
    sortAlgorithmsWithComparison["flash-sort"] = flashSortComp;

    inputOrderMap["-rand"] = 0;
    inputOrderMap["-sorted"] = 1;
    inputOrderMap["-rev"] = 2;
    inputOrderMap["-nsorted"] = 3;

    dataTypeName["-rand"] = "Randomize";
    dataTypeName["-sorted"] = "Sorted";
    dataTypeName["-nsorted"] = "Nearly Sorted";
    dataTypeName["-rev"] = "Reversed";
}

// Read data from the input file
void readFile(int*& data, int& n) {
    ifstream inp(inputFile.c_str(), ios::in);
    inp >> n;
    data = new int[n];
    for (int i = 0; i < n; i++)
        inp >> data[i];
    inp.close();
}

// Compute the running time of a sorting algorithm
double computeTime(function<void(int*&, int)> func, int* data, int n) {
    clock_t begin = clock();
    func(data, n);
    clock_t end = clock();
    double timeUsed = double(end - begin) / CLOCKS_PER_SEC * 1000;
    return timeUsed;
}

// Compute the number of comparisons made by a sorting algorithm
long long computeComparison(function<long long(int*&, int)> func, int* data, int n) {
    return func(data, n);
}

// COMMAND 1: [Execution file] -a [Algorithm] [Given input] [Output parameter(s)]
// Perform sorting algorithm analysis with input data from a file
void analyzeAlgorithmMode() {
    int* data;
    int dataSize;
    readFile(data, dataSize);

    cout << "ALGORITHM MODE" << '\n';
    cout << "Algorithm: " << algorithm << '\n';
    cout << "Input file: " << inputFile << '\n';
    cout << "Input size: " << dataSize << '\n';


    if (outputParam == "-time") {
        cout << "Running time: " << computeTime(sortAlgorithms[algorithm], data, dataSize) << "ms" << '\n';
    }
    else if (outputParam == "-comp") {
        cout << "Comparisons: " << computeComparison(sortAlgorithmsWithComparison[algorithm], data, dataSize) << '\n';
    }
    else {
        double timeUsed = computeTime(sortAlgorithms[algorithm], data, dataSize);
        long long comparisons = computeComparison(sortAlgorithmsWithComparison[algorithm], data, dataSize);
        cout << "Running time: " << timeUsed << "ms" << '\n';
        cout << "Comparisons: " << comparisons << '\n';
    }

    ofstream out("output.txt", ios::out);
    out << dataSize << '\n';
    for (int i = 0; i < dataSize; i++) {
        out << data[i];
        if (i < dataSize - 1)
            out << " ";
    }
    out.close();

    delete[] data;
}

// Perform sorting algorithm analysis with generated input data
void analyzeAlgorithmWithInputSizeAndOrderMode() {
    int dataSize = inputSize;
    int* data = new int[dataSize];

    int genType = inputOrderMap[inputOrder];
    GenerateData(data, dataSize, genType);

    std::ofstream inp("input.txt", std::ios::out);
    inp << dataSize << '\n';
    for (int i = 0; i < dataSize; i++) {
        inp << data[i];
        if (i < dataSize - 1)
            inp << " ";
    }
    inp.close();

    std::cout << "ALGORITHM MODE" << '\n';
    std::cout << "Algorithm: " << algorithm << '\n';
    std::cout << "Input size: " << dataSize << '\n';
    inputOrder.erase(0, 1); // remove '-'
    std::cout << "Input order: " << inputOrder << '\n';
    cout << "-----------------------------" << '\n';

    if (outputParam == "-time") {
        auto startTime = std::chrono::high_resolution_clock::now();
        sortAlgorithms[algorithm](data, dataSize);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        std::cout << "Running time: " << elapsedTime << "ms" << '\n';
    }
    else if (outputParam == "-comp") {
        std::cout << "Comparisons: " << sortAlgorithmsWithComparison[algorithm](data, dataSize) << '\n';
    }
    else {
        auto startTime = std::chrono::high_resolution_clock::now();
        sortAlgorithms[algorithm](data, dataSize);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        std::cout << "Running time: " << elapsedTime << "ms" << '\n';
        std::cout << "Comparisons: " << sortAlgorithmsWithComparison[algorithm](data, dataSize) << '\n';
    }

    std::ofstream out("output.txt", std::ios::out);
    out << dataSize << '\n';
    for (int i = 0; i < dataSize; i++) {
        out << data[i];
        if (i < dataSize - 1)
            out << " ";
    }
    out.close();
    delete[] data;
}

// Perform sorting algorithm analysis with various input orders and sizes
void analyzeAlgorithmWithVariousInputOrders() {
    int dataSize = inputSize;
    
    cout << "ALGORITHM MODE" << '\n';
    cout << "Algorithm: " << algorithm << '\n';
    cout << "Input size: " << dataSize << '\n';

    int idx = 1;
    for (auto gen : inputOrderMap) {
        int* data = new int[dataSize];
        GenerateData(data, dataSize, gen.second);

        ofstream inp("input_" + to_string(idx) + ".txt", ios::out);
        idx++;
        inp << dataSize << '\n';
        for (int i = 0; i < dataSize; i++) {
            inp << data[i];
            if (i < dataSize - 1)
                inp << " ";
        }
        inp.close();

        string inputOrderStr = gen.first;
        inputOrderStr.erase(0, 1);
        cout << "\nInput order: " << inputOrderStr << '\n';
        cout << "-----------------------------" << '\n';

        if (outputParam == "-time") {
            cout << "Running time: " << computeTime(sortAlgorithms[algorithm], data, dataSize) << "ms" << '\n';
        }
        else if (outputParam == "-comp") {
            cout << "Comparisons: " << computeComparison(sortAlgorithmsWithComparison[algorithm], data, dataSize) << '\n';
        }
        else {
            double timeUsed = computeTime(sortAlgorithms[algorithm], data, dataSize);
            long long comparisons = computeComparison(sortAlgorithmsWithComparison[algorithm], data, dataSize);
            cout << "Running time: " << timeUsed << "ms" << '\n';
            cout << "Comparisons: " << comparisons << '\n';
        }

        delete[] data;
    }
}

// Perform sorting algorithm comparison on the same input data
void compareAlgorithmsOnSameInput() {
    int* data;
    int dataSize;
    readFile(data, dataSize);

    cout << "COMPARE MODE" << '\n';
    cout << "Algorithm: " << algorithm1 << " | " << algorithm2 << '\n';
    cout << "Input file: " << inputFile << '\n';
    cout << "Input size: " << dataSize << '\n';
    cout << "-----------------------------" << '\n';

    double timeAlgorithm1 = computeTime(sortAlgorithms[algorithm1], data, dataSize);
    double timeAlgorithm2 = computeTime(sortAlgorithms[algorithm2], data, dataSize);

    long long comparisonsAlgorithm1 = computeComparison(sortAlgorithmsWithComparison[algorithm1], data, dataSize);
    long long comparisonsAlgorithm2 = computeComparison(sortAlgorithmsWithComparison[algorithm2], data, dataSize);

    cout << "Running time: " << timeAlgorithm1 << "ms | " << timeAlgorithm2 << "ms" << '\n';
    cout << "Comparisons: " << comparisonsAlgorithm1 << " | " << comparisonsAlgorithm2 << '\n';
    
    delete[] data;
}

// Perform sorting algorithm comparison on generated input data
void compareAlgorithmsOnGeneratedInput() {
    int dataSize = inputSize;
    int* data = new int[dataSize];

    int genType = inputOrderMap[inputOrder];
    GenerateData(data, dataSize, genType);

    ofstream inp("input.txt", ios::out);
    inp << dataSize << '\n';
    for (int i = 0; i < dataSize; i++) {
        inp << data[i];
        if (i < dataSize - 1)
            inp << " ";
    }
    inp.close();

    cout << "COMPARE MODE" << '\n';
    cout << "Algorithm: " << algorithm1 << " | " << algorithm2 << '\n';
    cout << "Input size: " << dataSize << '\n';
    inputOrder.erase(0, 1); // remove '-'
    cout << "Input order: " << inputOrder << '\n';
    cout << "-----------------------------" << '\n';

    double timeAlgorithm1 = computeTime(sortAlgorithms[algorithm1], data, dataSize);
    double timeAlgorithm2 = computeTime(sortAlgorithms[algorithm2], data, dataSize);

    long long comparisonsAlgorithm1 = computeComparison(sortAlgorithmsWithComparison[algorithm1], data, dataSize);
    long long comparisonsAlgorithm2 = computeComparison(sortAlgorithmsWithComparison[algorithm2], data, dataSize);

    cout << "Running time: " << timeAlgorithm1 << "ms | " << timeAlgorithm2 << "ms" << '\n';
    cout << "Comparisons: " << comparisonsAlgorithm1 << " | " << comparisonsAlgorithm2 << '\n';
    delete[] data;
}

// Perform the experiment option to analyze sorting algorithms with various input sizes and orders
void experimentOption() {
    cout << "\nEXPERIMENT OPTION" << '\n';
    int dataSizes[] = { 10000, 30000, 50000, 100000, 300000, 500000 };
    int dataSizeLen = sizeof(dataSizes) / sizeof(dataSizes[0]);

    for (auto gen : inputOrderMap) {
        string inputOrderStr = gen.first;
        inputOrderStr.erase(0, 1);
        cout << "\nInput order: " << inputOrderStr << '\n';
        cout << "=============================" << '\n';

        vector<double> timeList[dataSizeLen];
        vector<long long> compList[dataSizeLen];

        for (int dataSizeIdx = 0; dataSizeIdx < dataSizeLen; dataSizeIdx++) {
            int dataSize = dataSizes[dataSizeIdx];
            int* data = new int[dataSize];
            GenerateData(data, dataSize, gen.second);

            cout << "Input size: " << dataSize << '\n';
            cout << "-----------------------------" << '\n';

            for (auto algo : sortAlgorithms) {
                function<void(int*&, int)> sortFunction = algo.second;
                function<long long(int*&, int)> sortCompFunction = sortAlgorithmsWithComparison[algo.first];

                double elapsedTime = computeTime(sortFunction, data, dataSize);
                long long comparisons = computeComparison(sortCompFunction, data, dataSize);
                cout << algo.first << '\t' << ": " << elapsedTime << "ms" << "\t | "
                    << comparisons << " comparisons" << '\n';

                timeList[dataSizeIdx].push_back(elapsedTime);
                compList[dataSizeIdx].push_back(comparisons);
            }

            cout << "-----------------------------" << '\n';
            delete[] data;
        }

        cout << "=============================" << '\n';

        ofstream result("data/result_" + inputOrderStr + ".csv", ios::out);
        vector<string> sortNames;
        for (auto algo : sortAlgorithms)
            sortNames.push_back(algo.first);

        // Initialize header
        string header = "Sort,";
        for (int dataSizeIdx = 0; dataSizeIdx < dataSizeLen; dataSizeIdx++) {
            header += "time_" + to_string(dataSizes[dataSizeIdx]) + ", ";
            header += "comp_" + to_string(dataSizes[dataSizeIdx]) + ", ";
        }
        header += '\n';
        result << header;

        // Create content
        for (int i = 0; i < sortNames.size(); i++) {
            string line;
            line += sortNames[i] + ", ";
            for (int dataSizeIdx = 0; dataSizeIdx < dataSizeLen; dataSizeIdx++) {
                line += to_string(timeList[dataSizeIdx][i]) + ", ";
                line += to_string(compList[dataSizeIdx][i]) + ", ";
            }
            line += '\n';
            result << line;
        }
        result.close();
    }
}

int main(int argc, char** argv) {
    init();
    int commandType = parseArgs(argc, argv);
    switch (commandType) {
    case 1:
        analyzeAlgorithmMode();
        break;
    case 2:
        analyzeAlgorithmWithInputSizeAndOrderMode();
        break;
    case 3:
        analyzeAlgorithmWithVariousInputOrders();
        break;
    case 4:
        compareAlgorithmsOnSameInput();
        break;
    case 5:
        compareAlgorithmsOnGeneratedInput();
        break;
    case 0:
        experimentOption();
        break;
    default:
        break;
    }
}
