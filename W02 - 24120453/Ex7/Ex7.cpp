#include <iostream>
using namespace std;

void sortArray(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
			}
		}

	}
}

void triplet(int a[], int n)
{
	sortArray(a, n);
	for (int i = 0; i < n - 2; i++)
	{
		int left = i + 1;
	    int right = n - 1;
		if (i>0 && a[i] == a[i - 1]) continue;
		while (left < right)
		{	
			int sum = a[i] + a[left] + a[right];
			if (sum == 0)
			{
				cout << a[i] << " " << a[left] << " " << a[right] << endl;

				// Bỏ qua bộ ba trùng lặp
				while (left < right && a[left] == a[left + 1]) left++;
				while (left < right && a[right] == a[right - 1]) right--;

				left++;
				right--;
				continue;
			}
			if (sum < 0) left++;
			else right--;
		}
	}
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
	cout << "Nhung bo ba thoa man: " << endl;
	triplet(a, n);
	delete[] a;
	return 0;
}
