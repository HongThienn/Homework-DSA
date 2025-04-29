#include <iostream>
#include <algorithm>
using namespace std;

void count_sort(int* a, int n, int pos) {
    int* count = new int[10]();
    for (int i = 0; i < n; i++) {
        count[(a[i] / pos) % 10]++;
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    int* ans = new int[n];
    for (int i = n - 1; i >= 0; i--) {
        ans[--count[(a[i] / pos) % 10]] = a[i];
    }
    for (int i = 0; i < n; i++) {
        a[i] = ans[i];
    }
    delete[] count;
    delete[] ans;
}

void radixSort(int* a, int n) {
    if (n <= 0) return;
    int max_val = *max_element(a, a + n);
    for (int pos = 1; max_val / pos > 0; pos *= 10) {
        count_sort(a, n, pos);
    }
}
