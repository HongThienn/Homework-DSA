#include <iostream>
using namespace std;

bool targetSum(int a[], int n, int target)
{
	int left = 0;
	int right = n - 1;
	while (left < right)
	{
		if (a[left] + a[right] > target)
			right--;
		else if (a[left] + a[right] < target)
			left++;
		return true;
	}
	return false;
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
	int target; cout << "Nhap so can kiem tra: "; cin >> target;
	if (targetSum(a, n, target) == true)
		cout << "YES";
	else
		cout << "NO";
	return 0;
}