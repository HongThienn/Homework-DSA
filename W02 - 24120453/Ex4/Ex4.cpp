#include <iostream>
using namespace std;

// Hàm kiểm tra xem có thể vận chuyển tất cả các gói hàng trong days ngày với khả năng tải capacity hay không
bool canShip(int weights[], int n, int days, int capacity)
{
	int curWeights = 0;
	int countDay = 1;
	for (int i = 0; i < n; i++)
	{
		if (curWeights + weights[i] > capacity)
		{
			countDay++; // Bắt đầu 1 ngày mới khi vượt quá khả năng tải
			curWeights = weights[i]; // Đặt lại trọng lượng của gói hàng mới
			if (countDay > days)
				return false; // vượt quá số ngày được đặt ra thì không thể vận chuyển được
		}
		else
		{
			curWeights += weights[i]; // chưa vượt quá số món hàng có thể vận chuyển thì đặt thêm món hàng
		}
	}
	return true; // không vượt quá số ngày thì trả về true
}


int shipDays(int weights[], int n, int days)
{
	// Khởi tạo khả năng tải lớn nhất và nhỏ nhất
	int left = weights[0]; // khả năng tối thiểu
	int right = 0; // khả năng tối đa
	// Tìm khả năng tải tối thiểu (max(weights)) và tối đa (sum(weights))
	for (int i = 0; i < n; ++i) 
	{
		left = max(left, weights[i]); // khả năng tải tối thiểu là gói hàng có trọng lượng lớn nhất
		right += weights[i]; // khả năng tải tối đa là tổng trọng lượng các món hàng			
	}
	// Dùng binary search để tìm khả năng tải tối thiểu
	while (left < right) 
	{
		int mid = left + (right - left) / 2; // Tính khả năng tải trung bình

		if (canShip(weights, n, days, mid)) 
		{
			right = mid; // Nếu có thể vận chuyển, thử với tải nhỏ hơn
		}
		else 
		{
			left = mid + 1; // Nếu không thể vận chuyển, tăng khả năng tải
		}
	}
	return left; // Khi left == right, chính là khả năng tải tối thiểu
}

int main() 
{
	int n;
	cout << "Nhap so luong goi hang: ";
	cin >> n;
	cout << "Nhap gia tri cac gói hàng:" << endl;
	int* weights = new int[n]; // Mảng gói hàng
	for (int i = 0; i < n; i++)
	{
		cin >> weights[i];
	}
	int days; // Số ngày cần vận chuyển
	cout << "Nhap so ngay can van chuyen: ";
	cin >> days;
	cout << "Tong trong luong toi thieu " << shipDays(weights, n, days) << endl;
	return 0;
}
