#include <iostream>
#include <climits>

using namespace std;

struct NODE 
{
	int key;
	NODE* p_left;
	NODE* p_right;
};

NODE* Search(NODE* pRoot, int x)
{
    while (pRoot != NULL && pRoot->key != x) 
    {
        if (x < pRoot->key) 
        {
            pRoot = pRoot->p_left;
        }
        else 
        {
            pRoot = pRoot->p_right;
        }
    }
    return pRoot;
}

void Insert(NODE*& pRoot, int x) 
{
    if (pRoot == nullptr) 
    {
        pRoot = new NODE;
        pRoot->key = x;
        pRoot->p_left = NULL;
        pRoot->p_right = NULL;
    }
    else if (x < pRoot->key) 
    {
        Insert(pRoot->p_left, x); 
    }
    else if (x > pRoot->key)
    {
        Insert(pRoot->p_right, x); 
    }
}

// Hàm tìm nút lớn nhất trong cây con trái
NODE* findMaxNode(NODE* root)
{
    while (root->p_right != nullptr) 
    {
        root = root->p_right;
    }
    return root;
}

void Remove(NODE*& pRoot, int x)
{
    if (pRoot == NULL)
    {
        return; 
    }
    // Tìm nút cần xóa
    if (x < pRoot->key) 
    {
        Remove(pRoot->p_left, x);
    }
    else if (x > pRoot->key)
    {
        Remove(pRoot->p_right, x);
    }
    else 
    {
        // Nút lá hoặc chỉ có 1 con
        if (pRoot->p_left == NULL) 
        {
            NODE* temp = pRoot->p_right;
            delete pRoot;
            pRoot = temp;
        }
        else if (pRoot->p_right == NULL)
        {
            NODE* temp = pRoot->p_left;
            delete pRoot;
            pRoot = temp;
        }
        // Nút có 2 con
        else 
        {    
            NODE* maxLeftNode = findMaxNode(pRoot->p_left);
            pRoot->key = maxLeftNode->key;
            Remove(pRoot->p_left, maxLeftNode->key);
        }
    }
}

NODE* createTree(int a[], int n) 
{
    NODE* pRoot = NULL;
    for (int i = 0; i < n; i++) 
    {
        Insert(pRoot, a[i]);
    }
    return pRoot;
}

void removeTree(NODE*& pRoot) 
{
    if (pRoot == NULL) 
    {
        return; 
    }
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = NULL; 
}

int Height(NODE* pRoot)
{
    if (pRoot == NULL)
    {
        return -1;
    }
    int leftHeight = Height(pRoot->p_left);
    int rightHeight = Height(pRoot->p_right);
    return 1 + max(leftHeight, rightHeight);
}

int countLess(NODE* pRoot, int x) 
{
    if (pRoot == NULL) 
    {
        return 0; 
    }
    // Nếu giá trị nút hiện tại nhỏ hơn x, đếm nút này và tiếp tục sang phải
    if (pRoot->key < x) 
    {
        return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
    }
    else 
    {
        return countLess(pRoot->p_left, x);
    }
}

int countGreater(NODE* pRoot, int x) 
{
    if (pRoot == NULL) 
    {
        return 0; 
    }
    // Nếu nút hiện tại lớn hơn x, đếm nút này và tiếp tục sang trái
    if (pRoot->key > x) 
    {
        return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
    }
    else 
    {
        return countGreater(pRoot->p_right, x);
    }
}

bool isBSTUtil(NODE* pRoot, int minVal, int maxVal) 
{
    if (pRoot == NULL)
        return true;
    if (pRoot->key <= minVal || pRoot->key >= maxVal)
        return false;
    return isBSTUtil(pRoot->p_left, minVal, pRoot->key) && isBSTUtil(pRoot->p_right, pRoot->key, maxVal);
}

bool isBST(NODE* pRoot)  
{
    return isBSTUtil(pRoot, INT_MIN, INT_MAX);
}

bool isFullTree(NODE* pRoot) 
{
    if (pRoot == NULL)
        return true;
    // Node là lá 
    if (pRoot->p_left == NULL && pRoot->p_right == NULL)
        return true;
    // Node có đủ 2 con và kiểm tra tiếp bên trái, phải
    if (pRoot->p_left != NULL && pRoot->p_right != NULL)
        return isFullTree(pRoot->p_left) && isFullTree(pRoot->p_right);
    // Node chỉ có 1 con → không phải full
    return false;
}

bool isFullBST(NODE* pRoot) 
{
    return isBST(pRoot) && isFullTree(pRoot);
}

