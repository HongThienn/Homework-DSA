#include <iostream>
using namespace std;

void generateBinaryStrings(int n, string str)
{
	if (str.length() == n) // Khi đủ n phần tử
		cout << str << endl;
	generateBinaryStrings(n, str + "0"); // Thêm phần tử 0 vào chuỗi
	generateBinaryStrings(n, str + "1"); // Thêm phần tử 1 vào chuỗi
}

int main()
{
	int n;
	cout << "Nhap n = ";
	cin >> n;	
	generateBinaryStrings(n, "");
	return 0;
}