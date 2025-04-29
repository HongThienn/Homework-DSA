#pragma once
#include<iostream>
using namespace std;

int findMin(int* a, int low, int n)
{
    int min = low;
    for (int i = low + 1; i < n; i++)
    {
        if (a[i] < a[min])
        {
            min = i;
        }
    }
    return min;
}

void swap(int* a, int i, int j)
{
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void selectionSort(int* a, int low, int n)
{
    for (int i = low; i < n; i++)
    {
        int min = findMin(a, i, n);
        swap(a, i, min);
    }
}
