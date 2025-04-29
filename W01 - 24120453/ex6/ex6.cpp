#include <iostream>
using namespace std;

// Hàm kiểm tra cột c, đường chéo chính c1 và đường chéo phụ c2
bool check(int i, int j, int N, bool c[], bool c1[], bool c2[])
{
    return c[j] && c1[i - j + N - 1] && c2[i + j];
}

void NQueen(int i, int N, bool c[], bool c1[], bool c2[], int x[], int& solutions) 
{
    if (i == N)
    {
        solutions++;
        cout << "Nghiem " << solutions << ": ";
        for (int k = 0; k < N; k++) cout << x[k] + 1 << " ";
        cout << endl;
        return;
    }

    for (int j = 0; j < N; j++)
    {
        if (check(i, j, N, c, c1, c2))
        {
            x[i] = j;
            c[j] = false;
            c1[i - j + N - 1] = false;
            c2[i + j] = false;

            NQueen(i + 1, N, c, c1, c2, x, solutions); // Gọi đệ quy

            c[j] = true;
            c1[i - j + N - 1] = true;
            c2[i + j] = true;
        }
    }
}

int main()
{
    int N;
    cout << "Nhap so luong quan hau (N): ";
    cin >> N;

    bool* c = new bool[N];
    bool* c1 = new bool[2 * N - 1];
    bool* c2 = new bool[2 * N - 1];
    int* x = new int[N];
    int solutions = 0; // Đếm số nghiệm

    // Khởi tạo tất cả phần tử của mảng là true
    for (int i = 0; i < N; i++) c[i] = true;
    for (int i = 0; i < 2 * N - 1; i++) c1[i] = c2[i] = true;

    NQueen(0, N, c, c1, c2, x, solutions); // Bắt đầu từ hàng đầu tiên

    cout << "Tong so nghiem: " << solutions << endl;

    delete[] c;
    delete[] c1;
    delete[] c2;
    delete[] x;

    return 0;
}