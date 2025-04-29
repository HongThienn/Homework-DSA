#pragma once
#include<string>
using namespace std;
int* ReadArrayFromFile(const string& filename, int& n);
void WriteArrayToFile(const string& filename, int* a, int n);

