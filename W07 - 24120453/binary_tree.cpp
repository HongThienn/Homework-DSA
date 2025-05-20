#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct NODE 
{
	int key;
	NODE* p_left;
	NODE* p_right;
};

NODE* createNode(int data)
{
	NODE* newNode = new NODE;
	newNode->key = data;
	newNode->p_left = NULL;
	newNode->p_right = NULL;
}

vector<int> NLR(NODE* pRoot)
{
	vector<int> result; // biến lưu kết quả
	if (pRoot == NULL)
		return result;
	// Node
	result.push_back(pRoot->key); 
	// Left
	vector<int> left = NLR(pRoot->p_left);
	result.insert(result.end(), left.begin(), left.end()); // nối vector left vào cuối result ( thêm kết quả duyệt bên trái vào kq chính)
	vector<int> right = NLR(pRoot->p_right);
	// Right
	result.insert(result.end(), right.begin(), right.end()); // nối vector right vào cuối result ( thêm kết quả duyệt bên phải vào kq chính)
	return result;
}

vector<int> LNR(NODE* pRoot)
{
	vector<int> result;
	if (pRoot == NULL)
		return result;
	// left
	vector<int> left = NLR(pRoot->p_left);
	result.insert(result.end(), left.begin(), left.end());
	// node
	result.push_back(pRoot->key);
	// right
	vector<int> right = NLR(pRoot->p_right);
	result.insert(result.end(), right.begin(), right.end());
	return result;
}

vector<int> LRN(NODE* pRoot)
{
	vector<int> result;
	if (pRoot == NULL)
		return result;
	// left
	vector<int> left = NLR(pRoot->p_left);
	result.insert(result.end(), left.begin(), left.end());
	// right
	vector<int> right = NLR(pRoot->p_right);
	result.insert(result.end(), right.begin(), right.end());
	// node
	result.push_back(pRoot->key);
	return result;
}

vector<vector<int>> LevelOrder(NODE* pRoot)
{
	vector<vector<int>> result;
	queue < NODE*> q;
	q.push(pRoot);
	while (!q.empty())
	{
		vector<int> level;
		for (int i = 0; i < q.size(); i++)
		{
			NODE* cur = q.front();
			level.push_back(cur->key);
			q.pop();
			if (pRoot->p_left != NULL)
				q.push(pRoot->p_left);
			if (pRoot->p_right != NULL)
				q.push(pRoot->p_right);
		}
		result.push_back(level);
	}
	return result;
}

int countNode(NODE* pRoot)
{
	if (pRoot == NULL)
		return 0;
	int left = countNode(pRoot->p_left);
	int right = countNode(pRoot->p_right);
	return 1 + left + right;
}

int sumNode(NODE* pRoot)
{
	if (pRoot == nullptr)
		return 0;
	int leftSum = sumNode(pRoot->p_left);
	int rightSum = sumNode(pRoot->p_right);
	return pRoot->key + leftSum + rightSum;
}

int getHeight(NODE* pRoot)
{
	if (pRoot == NULL)
		return -1;
	int left = getHeight(pRoot->p_left);
	int right = getHeight(pRoot->p_right);
	return 1 + max(left, right);
}

int heightNode(NODE* pRoot, int value)
{
	if (pRoot == NULL)
		return -1;
	if (pRoot->key == value)
		return getHeight(pRoot);
	if (heightNode(pRoot->p_left, value) != -1)
		return heightNode(pRoot->p_left, value);
	else
		return heightNode(pRoot->p_right, value);
}

int Level(NODE* pRoot, NODE* p)
{
	if (pRoot == NULL)
		return -1;
	if (pRoot == p)
		return 0;
	if (Level(pRoot->p_left, p) != -1)
		return Level(pRoot->p_left, p) + 1;
	if (Level(pRoot->p_right, p) != -1)
		return Level(pRoot->p_right, p) + 1;
}

int countLeaf(NODE* pRoot) 
{
	if (pRoot == NULL) 
	{
		return 0; 
	}
	if (pRoot->p_left == NULL && pRoot->p_right == NULL) 
	{
		return 1; 
	}
	return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}