//#include<iostream>
//#include <cmath>
//#include<string>
//#include"merge-sort.h"
//#include"quick-sort.h"
//#include"radix-sort.h"
//#include"selection-sort.h"
//#include"insertion-sort.h"
//#include"heap-sort.h"
//#include"bubble-sort.h"
//#include"iofile.h"
//using namespace std;
//
//int main(int argc, char* argv[]) {
//    string algorithm;
//    string inputFile;
//    string outputFile;
//
//    for (int i = 1; i < argc; i++) {
//        string arg = argv[i];
//        if (arg == "-a" && i + 1 < argc) algorithm = argv[++i];
//        else if (arg == "-i" && i + 1 < argc) inputFile = argv[++i];
//        else if (arg == "-o" && i + 1 < argc) outputFile = argv[++i];
//    }
//
//    int n = 0;
//    int* arr = ReadArrayFromFile(inputFile, n);
//    if (!arr) return 1;
//
//    if (algorithm == "selection-sort") selectionSort(arr, 0, n);
//    else if (algorithm == "insertion-sort") insertionSort(arr, n);
//    else if (algorithm == "bubble-sort") bubbleSort(arr, n);
//    else if (algorithm == "heap-sort") heapSort(arr, n);
//    else if (algorithm == "quick-sort") quickSort(arr, 0, n - 1);
//    else if (algorithm == "merge-sort") mergeSort(arr, 0, n - 1);
//    else if (algorithm == "radix-sort") radixSort(arr, n);
//    else {
//        delete[] arr;
//        return 1;
//    }
//
//    WriteArrayToFile(outputFile, arr, n);
//    delete[] arr;
//
//    return 0;
//}