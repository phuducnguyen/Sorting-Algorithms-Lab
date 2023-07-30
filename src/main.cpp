#include "include/DataGenerator.h"
#include "include/Sorting.h"
#include "include/CompSorting.h"
#include <iostream>
#include <map>
#include <string.h>
#include <functional>
#include <assert.h>
#include <time.h>

bool checkIfFile(string arg){
    for(char ch: arg)
        if(ch == '.')
            return true;
    return false;
}

// Input arguments
string algo, algo1, algo2;
string inputFile;
string outputParam;
int inputSize;
string inputOrder;

int parseArgs(int argc, char** argv){
    if(argc == 1){
        printf("\nNo extra command found!");
        return 0;
    }
    if(!strcmp(argv[1], "-exp")) // experiment option
        return 0;
    assert(!strcmp(argv[1], "-a") || !strcmp(argv[1], "-c"));
    if(!strcmp(argv[1], "-a")){
        assert(argc == 5 || argc == 6);
        if(argc == 5){
            if(checkIfFile(argv[3])){
                // [Execution file] -a [Algorithm] [Given input] [Output parameter(s)]
                algo = argv[2];
                inputFile = argv[3];
                outputParam = argv[4];
                return 1;
            }
            else{
                // [Execution file] -a [Algorithm] [Input size] [Output parameter(s)]
                algo = argv[2];
                inputSize = stoi(argv[3]); // convert string to int
                outputParam = argv[4];
                return 3;
            }
        }
        if(argc == 6){
            // [Execution file] -a [Algorithm] [Input size] [Input order] [Output parameter(s)]
            algo = argv[2];
            inputSize = stoi(argv[3]); // convert string to int
            inputOrder = argv[4];
            outputParam = argv[5];
            return 2;
        }
    }else{
        assert(argc == 5 || argc == 6);
        if(argc == 5){
            algo1 = argv[2];
            algo2 = argv[3];
            inputFile = argv[4];
            return 4;
        }else{
            algo1 = argv[2];
            algo2 = argv[3];
            inputSize = stoi(argv[4]); // convert string to int
            inputOrder = argv[5];
            return 5;
        }
    }
    return 0;
}

std::map<std::string, std::function<void(int* &, int)>> sort_algo;
std::map<std::string, std::function<ll(int* &, int)>> sort_algo_with_cmp;
std::map<std::string, int> input_order;

void init(){
    sort_algo["selection-sort"] = selectionSort;
    sort_algo["insertion-sort"] = insertionSort;
    sort_algo["bubble-sort"] = bubbleSort;
    sort_algo["shaker-sort"] = shakerSort;
    sort_algo["shell-sort"] = shellSort;
    sort_algo["heap-sort"] = heapSort;
    sort_algo["merge-sort"] = mergeSort;
    sort_algo["quick-sort"] = quickSort;
    sort_algo["counting-sort"] = countingSort;
    sort_algo["radix-sort"] = radixSort;
    sort_algo["flash-sort"] = flashSort;

    sort_algo_with_cmp["selection-sort"] = selectionSortComp;
    sort_algo_with_cmp["insertion-sort"] = insertionSortComp;
    sort_algo_with_cmp["bubble-sort"] = bubbleSortComp;
    sort_algo_with_cmp["shaker-sort"] = shakerSortComp;
    sort_algo_with_cmp["shell-sort"] = shellSortComp;
    sort_algo_with_cmp["heap-sort"] = heapSortComp;
    sort_algo_with_cmp["merge-sort"] = mergeSortComp;
    sort_algo_with_cmp["quick-sort"] = quickSortComp;
    sort_algo_with_cmp["counting-sort"] = countingSortComp;
    sort_algo_with_cmp["radix-sort"] = radixSortComp;
    sort_algo_with_cmp["flash-sort"] = flashSortComp;

    input_order["-rand"] = 0;
    input_order["-nsorted"] = 3;
    input_order["-sorted"] = 1;
    input_order["-rev"] = 2;
}

void readFile(int* &a, int &n){
    ifstream inp(inputFile.c_str(), ios::in);
    inp >> n;
    a = new int[n];
    for(int i = 0; i < n; i++)
        inp >> a[i];
    inp.close();
}

double computeTime(std::function<void(int* &, int)> func, int *a, int n){
    double begin, timeUsed;
    begin = (double)clock();
    func(a, n);
    timeUsed = ((double)clock() - begin)/CLOCKS_PER_SEC * 1000;
    return timeUsed;
}

ll computeComparision(std::function<ll(int* &, int)> func, int *a, int n){
    return func(a, n);
}

void option1(){
    int* a;
    int n;
    
    readFile(a, n);

    std:: cout << "ALGORITHM MODE" << '\n';
    std:: cout << "Algorithm: " << algo << '\n';
    std:: cout << "Input file: " << inputFile << '\n';
    std:: cout << "Input size: " << n << '\n';

    if(outputParam == "-time"){
        std:: cout << "Running time: " << computeTime(sort_algo[algo], a, n) << "ms" << '\n';
    }else if(outputParam == "-comp"){
        std:: cout << "Comparisions: " << computeComparision(sort_algo_with_cmp[algo], a, n) << '\n';
    }else{
        std:: cout << "Running time: " << computeTime(sort_algo[algo], a, n) << "ms" << '\n';
        std:: cout << "Comparisions: " << computeComparision(sort_algo_with_cmp[algo], a, n) << '\n';
    }

    ofstream out("output.txt", ios::out);
    out << n << '\n';
    for(int i = 0; i < n; i++){
        out << a[i];
        if(i < n-1)
            out << " "; 
    }
    out.close();

    delete[] a;
    
}

void option2(){
    int n = inputSize;
    int* a = new int[n];
    
    int genType = input_order[inputOrder];
    GenerateData(a, n, genType);

    ofstream inp("input.txt", ios::out);
    inp << n << '\n';
    for(int i = 0; i < n; i++){
        inp << a[i];
        if(i < n-1)
            inp << " "; 
    }
    inp.close();

    std:: cout << "ALGORITHM MODE" << '\n';
    std:: cout << "Algorithm: " << algo << '\n';
    std:: cout << "Input size: " << n << '\n';
    inputOrder.erase(0, 1); // remove '-'
    std:: cout << "Input order: " << inputOrder << '\n';

    if(outputParam == "-time"){
        std:: cout << "Running time: " << computeTime(sort_algo[algo], a, n) << "ms" << '\n';
    }else if(outputParam == "-comp"){
        std:: cout << "Comparisions: " << computeComparision(sort_algo_with_cmp[algo], a, n) << '\n';
    }else{
        std:: cout << "Running time: " << computeTime(sort_algo[algo], a, n) << "ms" << '\n';
        std:: cout << "Comparisions: " << computeComparision(sort_algo_with_cmp[algo], a, n) << '\n';
    }

    ofstream out("output.txt", ios::out);
    out << n << '\n';
    for(int i = 0; i < n; i++){
        out << a[i];
        if(i < n-1)
            out << " "; 
    }
    out.close();
    delete[] a;
}

void option3(){
    int n = inputSize;
    
    std:: cout << "ALGORITHM MODE" << '\n';
    std:: cout << "Algorithm: " << algo << '\n';
    std:: cout << "Input size: " << n << '\n';

    int idx = 1;
    for(auto gen: input_order){
        int* a = new int[n];
        GenerateData(a, n, gen.second);

        ofstream inp("input" + to_string(idx) + ".txt", ios::out);
        idx++;
        inp << n << '\n';
        for(int i = 0; i < n; i++){
            inp << a[i];
            if(i < n-1)
                inp << " "; 
        }
        inp.close();

        string s = gen.first;
        s.erase(0, 1);
        std:: cout << "\nInput order: " << s << '\n';
        std:: cout << "-----------------------------" << '\n';

        if(outputParam == "-time"){
        std:: cout << "Running time: " << computeTime(sort_algo[algo], a, n) << "ms" << '\n';
        }else if(outputParam == "-comp"){
            std:: cout << "Comparisions: " << computeComparision(sort_algo_with_cmp[algo], a, n) << '\n';
        }else{
            std:: cout << "Running time: " << computeTime(sort_algo[algo], a, n) << "ms" << '\n';
            std:: cout << "Comparisions: " << computeComparision(sort_algo_with_cmp[algo], a, n) << '\n';
        }

        delete[] a;
    }
    
}

void option4(){
    int* a;
    int n;
    readFile(a, n);

    std:: cout << "COMPARE MODE" << '\n';
    std:: cout << "Algorithm: " << algo1 << " | " << algo2 << '\n';
    std:: cout << "Input file: " << inputFile << '\n';
    std:: cout << "Input size: " << n << '\n';

    std:: cout << "-----------------------------" << '\n';
    double timeAlgo1 = computeTime(sort_algo[algo1], a, n);
    double timeAlgo2 = computeTime(sort_algo[algo2], a, n);

    ll compAlgo1 = computeComparision(sort_algo_with_cmp[algo1], a, n);
    ll compAlgo2 = computeComparision(sort_algo_with_cmp[algo2], a, n);

    std:: cout << "Running time: " << timeAlgo1 << "ms | " << timeAlgo2 << "ms" << '\n';
    std:: cout << "Comparisions: " << compAlgo1 << " | " << compAlgo2 << '\n';
    delete[] a;
}

void option5(){
    int n = inputSize;
    int* a = new int[n];

    int genType = input_order[inputOrder];
    GenerateData(a, n, genType);

    ofstream inp("input.txt", ios::out);
    inp << n << '\n';
    for(int i = 0; i < n; i++){
        inp << a[i];
        if(i < n-1)
            inp << " "; 
    }
    inp.close();

    std:: cout << "COMPARE MODE" << '\n';
    std:: cout << "Algorithm: " << algo1 << " | " << algo2 << '\n';
    std:: cout << "Input size: " << n << '\n';
    inputOrder.erase(0, 1); // remove '-'
    std:: cout << "Input order: " << inputOrder << '\n';

    std:: cout << "-----------------------------" << '\n';
    double timeAlgo1 = computeTime(sort_algo[algo1], a, n);
    double timeAlgo2 = computeTime(sort_algo[algo2], a, n);

    ll compAlgo1 = computeComparision(sort_algo_with_cmp[algo1], a, n);
    ll compAlgo2 = computeComparision(sort_algo_with_cmp[algo2], a, n);

    std:: cout << "Running time: " << timeAlgo1 << "ms | " << timeAlgo2 << "ms" << '\n';
    std:: cout << "Comparisions: " << compAlgo1 << " | " << compAlgo2 << '\n';
    delete[] a;
}

void experiment_option(){
    cout << "EXPERIMENT OPTION" << '\n';
    int data_size[] = {10000, 30000, 50000, 100000, 300000, 500000};
    //int data_size[] = {100, 200};
    int data_len = sizeof(data_size)/sizeof(data_size[0]);

    for(auto gen: input_order){
        string s = gen.first;
        s.erase(0, 1);
        std:: cout << "\nInput order: " << s << '\n';

        std:: cout << "=============================" << '\n';

        vector <double> time_list[data_len];
        vector <ll> comp_list[data_len];

        for(int data_idx = 0; data_idx < data_len; data_idx++){
            int n = data_size[data_idx];
            int* a = new int[n];
            GenerateData(a, n, gen.second);

            std:: cout << "Input size: " << n << '\n';

            std:: cout << "-----------------------------" << '\n';

            for(auto algo: sort_algo){
                std::function<void(int* &, int)> sort_func = algo.second;
                std::function<ll(int* &, int)> sort_cmp_func = sort_algo_with_cmp[algo.first];

                double _time = computeTime(sort_func, a, n);
                ll _iter = computeComparision(sort_cmp_func, a, n);
                std:: cout << algo.first << '\t' << ": " << _time << "ms" <<  "\t | " 
                        << _iter << " iters" << '\n';

                time_list[data_idx].push_back(_time);
                comp_list[data_idx].push_back(_iter);
            }

            std:: cout << "-----------------------------" << '\n';
            delete[] a;
        }

        std:: cout << "=============================" << '\n';

        ofstream result("data/result_" + s + ".csv", ios::out);
        vector <string> sort_name;
        for(auto algo: sort_algo)
            sort_name.push_back(algo.first);
        // initialize header
        string header = "Sort,";
        for(int data_idx = 0; data_idx < data_len; data_idx++){
            header += "time_" + to_string(data_size[data_idx]) + ", ";
            header += "comp_" + to_string(data_size[data_idx]) + ", ";
        }
        header += '\n';
        result << header;
        // create content
        for(int i = 0; i < sort_name.size(); i++){
            string line;
            line += sort_name[i] + ", ";
            for(int data_idx = 0; data_idx < data_len; data_idx++){
                line += to_string(time_list[data_idx][i]) + ", ";
                line += to_string(comp_list[data_idx][i]) + ", ";
            }
            line += '\n';
            result << line;
        }
        result.close();
    }
}

int main(int argc, char** argv){
    init();
    int commandType = parseArgs(argc, argv);
    switch (commandType)
    {
    case 1:
        option1();
        break;
    case 2:
        option2();
        break;
    case 3:
        option3();
        break;
    case 4:
        option4();
        break;
    case 5:
        option5();
        break;
    case 0:
        experiment_option();
        break;
    
    default:
        break;
    }
}