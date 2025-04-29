#include<iostream>
#include<vector>

using namespace std;

void merge(int a[], int l, int m, int r)
{
	vector<int> x(a + l, a + m + 1); // mảng từ trái tới giữa
	vector<int> y(a + m + 1, a + r + 1); // mảng từ giữa tới phải
	int i = 0, j = 0;
	while (i < x.size() && j < y.size())
	{
		if (x[i] <= y[j])
		{
			a[l] = x[i]; ++l; i++; // i tối đa là 6
		}
		else
		{
			a[l] = y[j]; ++l; j++; // tối đa là 5
		}
	}
	while (i < x.size()) // nó vẫn còn phần tử chưa được duyệt
	{
		a[l] = x[i]; ++l; ++i;
	}
	while (j < y.size())
	{
		a[l] = y[j]; ++l; ++j;
	}
}


void mergeSort(int a[], int l, int r)
{
	if (l >= r)
		return;
	int m = (l + r) / 2;
	mergeSort(a, l, m);
	mergeSort(a, m + 1, r); // hoàn thành xong việc tách
	merge(a, l, m, r); // gộp lại và sắp xếp
}

int main() {
	int a[] = { 38, 27, 43, 3, 9, 82, 10 };
	int n = sizeof(a) / sizeof(a[0]);

	cout << "Mang truoc khi sap xep: ";
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;

	mergeSort(a, 0, n - 1);

	cout << "Mang sau khi sap xep: ";
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;

	return 0;
}
