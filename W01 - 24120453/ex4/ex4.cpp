#include <iostream>
using namespace std;

void towerOfHanoi(int n, char A, char B, char C)
{
	if (n == 1)
	{
		cout << "Di chuyen dia 1 tu " << A << " toi " << C << endl;
	}
	else
	{
		towerOfHanoi(n - 1, A, C, B); // Di chuyển n-1 dia tu A sang B
		cout << "Di chuyen dia " << n << " tu " << A << " toi " << C << endl; // Di chuyen dia lon nhat tu A sang C
		towerOfHanoi(n - 1, B, A, C); // Di chuyen n-1 dia tu B sang C
	}
}

int main()
{
	int n;
	cout << "Nhap n = ";
	cin >> n;
	towerOfHanoi(n, 'A', 'B', 'C');
	return 0;
}