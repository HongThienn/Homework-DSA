#include <iostream>
#include <algorithm>
using namespace std;

struct NODE 
{
    int key;         
    NODE* p_left;    
    NODE* p_right;   
    int height;     
};

NODE* createNode(int data)
{
    NODE* newNode = new NODE;
    newNode->key = data;          
    newNode->p_left = NULL;    
    newNode->p_right = NULL;   
    newNode->height = 1;          
    return newNode;
}

// Hàm hỗ trợ lấy chiều cao node (xử lý trường hợp node null)
int getHeight(NODE* node) 
{
    if (node == NULL)
        return 0;
    return node->height;
}

// Hàm tính hệ số cân bằng (balance factor)
int getBalance(NODE* node) 
{
    if (node == NULL)
        return 0;
    return getHeight(node->p_left) - getHeight(node->p_right);
}

// Hàm cập nhật chiều cao node dựa trên chiều cao các con
void updateHeight(NODE* node) 
{
    if (node == NULL) 
        return;
    node->height = 1 + max(getHeight(node->p_left), getHeight(node->p_right));
}

// Hàm xoay phải (dùng cho trường hợp LL)
NODE* rightRotate(NODE* y) 
{
    NODE* x = y->p_left;
    NODE* T2 = x->p_right;
    // Thực hiện xoay
    x->p_right = y;
    y->p_left = T2;
    // Cập nhật chiều cao sau khi xoay
    updateHeight(y);
    updateHeight(x);
    return x; 
}

// Hàm xoay trái (dùng cho trường hợp RR)
NODE* leftRotate(NODE* x) 
{
    NODE* y = x->p_right;
    NODE* T2 = y->p_left;
    // Thực hiện xoay
    y->p_left = x;
    x->p_right = T2;
    // Cập nhật chiều cao sau khi xoay
    updateHeight(x);
    updateHeight(y);
    return y; 
}

// Hàm chèn node vào cây AVL
void Insert(NODE*& pRoot, int x) 
{
    // Chèn như BST bth
    if (pRoot == NULL) 
    {
        pRoot = createNode(x);
        return;
    }
    if (x < pRoot->key) {
        Insert(pRoot->p_left, x); 
    }
    else if (x > pRoot->key) {
        Insert(pRoot->p_right, x); 
    }
    else 
    {
        return; 
    }
    // Cập nhật chiều cao node cha
    updateHeight(pRoot);
    // Kiểm tra cân bằng và xử lý
    int balance = getBalance(pRoot);
    // Trường hợp LL
    if (balance > 1 && x < pRoot->p_left->key)
    {
        pRoot = rightRotate(pRoot);
        return;
    }
    // Trường hợp RR
    if (balance < -1 && x > pRoot->p_right->key) 
    {
        pRoot = leftRotate(pRoot);
        return;
    }
    // Trường hợp LR
    if (balance > 1 && x > pRoot->p_left->key) 
    {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
        return;
    }
    // Trường hợp RL
    if (balance < -1 && x < pRoot->p_right->key) 
    {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
        return;
    }
}

// Hàm tìm node có giá trị nhỏ nhất (dùng khi xóa node có 2 con)
NODE* minValueNode(NODE* node)
{
    NODE* current = node;
    while (current->p_left != NULL)
        current = current->p_left;
    return current;
}

// Hàm xóa node khỏi cây AVL
void Remove(NODE*& pRoot, int x) 
{
    // Xóa như BST thông thường
    if (pRoot == NULL) 
        return;
    if (x < pRoot->key) {
        Remove(pRoot->p_left, x); 
    }
    else if (x > pRoot->key) {
        Remove(pRoot->p_right, x); 
    }
    else 
    {
        // Node cần xóa được tìm thấy
        // Node có 0 hoặc 1 con
        if ((pRoot->p_left == NULL) || (pRoot->p_right == NULL)) 
        {
            NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
            // Trường hợp không có con
            if (temp == NULL) 
            {
                temp = pRoot;
                pRoot = NULL;
            }
            else // Trường hợp có 1 con
            { 
                *pRoot = *temp; 
            }
            delete temp;
        }
        else 
        {
            // Trường hợp có 2 con: tìm node nhỏ nhất bên phải
            NODE* temp = minValueNode(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }
    // Nếu cây rỗng sau khi xóa
    if (pRoot == NULL) 
        return;
    // Cập nhật chiều cao
    updateHeight(pRoot);
    // Kiểm tra cân bằng và xử lý
    int balance = getBalance(pRoot);
    // Các trường hợp mất cân bằng tương tự khi chèn
    if (balance > 1 && getBalance(pRoot->p_left) >= 0) 
    {
        pRoot = rightRotate(pRoot);
        return;
    }
    if (balance > 1 && getBalance(pRoot->p_left) < 0) 
    {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
        return;
    }
    if (balance < -1 && getBalance(pRoot->p_right) <= 0) 
    {
        pRoot = leftRotate(pRoot);
        return;
    }
    if (balance < -1 && getBalance(pRoot->p_right) > 0) 
    {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
        return;
    }
}

// Hàm kiểm tra cây có phải BST không
bool isBST(NODE* node, int min, int max) 
{
    if (node == NULL) 
        return true;
    if (node->key < min || node->key > max) 
        return false;
    return isBST(node->p_left, min, node->key - 1) && isBST(node->p_right, node->key + 1, max);
}

// Hàm kiểm tra cây có cân bằng không
bool isBalanced(NODE* node) 
{
    if (node == NULL)
        return true;
    int balance = getBalance(node);
    if (balance > 1 || balance < -1) 
        return false;
    return isBalanced(node->p_left) && isBalanced(node->p_right);
}

// Hàm kiểm tra cây AVL
bool isAVL(NODE* pRoot) 
{
    if (pRoot == NULL) 
        return true;
    return isBST(pRoot, INT_MIN, INT_MAX) && isBalanced(pRoot);
}