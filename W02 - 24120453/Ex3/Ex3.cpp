#include <iostream>
using namespace std;

int findMin(int a[], int n)
{
	int left = 0;
	int right = n - 1;
	while (left < right)
	{
		int mid = (left+right)/2;
		if (a[mid] < a[right])
		{
			right = mid;
		}
		else
		{
			left = mid+1;
		}
	}
	return a[left];
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
	int resultLinearSearch = findMin(a, n);
	cout << "Phan tu nho nhat la: " << resultLinearSearch;
	return 0;
}