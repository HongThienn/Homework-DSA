#include <iostream>
using namespace std;

int sentineLinearSearch(int a[], int n, int k)
{
	int last = a[n - 1];
	a[n - 1] = k;

	int i = 0;
	while (a[i] != k)
	{
		i++;
	}
	a[n - 1] = last;
	if (i < n - 1 || a[n - 1] == k)
		return i;
	return -1;
}

int main()
{
	int n; cout << "Nhap so luong phan tu trong mang: "; cin >> n;
	int* a = new int[n];
	cout << "Nhap chi so cho cac phan tu co trong mang:" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	int k; cout << "Nhap chi so can tim lan dau tien xuat hien: "; cin >> k;
	int resultLinearSearch = sentineLinearSearch(a, n, k);
	cout << resultLinearSearch;
	return 0;
}