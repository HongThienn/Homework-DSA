#include<iostream>
#include<fstream>
#include"iofile.h"
using namespace std;

void WriteArrayToFile(const string& filename, int* a, int n) {
    ofstream out(filename);
    if (!out) {
        cerr << "Không thể mở file để ghi!\n";
        return;
    }
    out << n << "\n"; 
    for (int i = 0; i < n; i++) {
        out << a[i] << " ";
    }
    out.close();
}

int* ReadArrayFromFile(const string& filename, int& n) {
    ifstream in(filename);
    if (!in) {
        cerr << "Không thể mở file input.txt!" << endl;
        return nullptr;
    }

    in >> n; 
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        in >> a[i];
    }

    in.close();
    return a;
}


