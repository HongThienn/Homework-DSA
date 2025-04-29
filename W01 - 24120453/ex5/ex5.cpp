#include <iostream>
using namespace std;

bool isSorted(int a[], int n)
{
	if (n == 1 || n == 0)
		return true;
	if (a[n - 2] > a[n - 1])
		return false;
	return isSorted(a, n - 1);
}

int main()
{
	int n;
	cout << "Nhap so phan tu: "; cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	if (isSorted(a, n))
		cout << "Da sap xep" << endl;
	else
		cout << "Chua sap xep" << endl;
	return 0;

}