#include <iostream>
#include <algorithm>
using namespace std;

int medianOfThree(int* a, int l, int r) {
    int mid = l + (r - l) / 2;
    if (a[l] > a[mid]) swap(a[l], a[mid]);
    if (a[l] > a[r]) swap(a[l], a[r]);
    if (a[mid] > a[r]) swap(a[mid], a[r]);
    return mid;
}

int partition(int* a, int l, int r) {
    int pivotIdx = medianOfThree(a, l, r);
    swap(a[pivotIdx], a[r]);
    int pivot = a[r];
    int i = l - 1;

    for (int j = l; j < r; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[r]);
    return i + 1;
}

void quickSort(int* a, int l, int r) {
    while (l < r) {
        int p = partition(a, l, r);
        if (p - l < r - p) {
            quickSort(a, l, p - 1);
            l = p + 1;
        }
        else {
            quickSort(a, p + 1, r);
            r = p - 1;
        }
    }
}
