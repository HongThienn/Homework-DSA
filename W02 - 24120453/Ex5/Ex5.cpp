#include <iostream>
using namespace std;

int minSubArrayLen(int target, int nums[], int n) 
{
    int left = 0, sum = 0, minLength = 1000000; 

    for (int right = 0; right < n; right++) 
    {
        sum += nums[right]; // Mở rộng khoảng
        while (sum >= target)  // Thu hẹp khoảng khi sum >= target
        {
            minLength = min(minLength, right - left + 1);
            sum -= nums[left]; // Loại bỏ phần tử bên trái khoảng
            left++;
        }
    }

    return (minLength == 1000000) ? 0 : minLength; // Nếu không tìm thấy, trả về 0
}

int main() 
{
    int n; cout << "Nhap so phan tu cua mang: "; cin >> n;
    int* nums = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    int target; cout << "Nhap target: "; cin >> target;
    cout << minSubArrayLen(target, nums, n) << endl; 
    return 0;
}
