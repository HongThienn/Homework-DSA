#include <iostream>
#include <cassert>

using namespace std;

struct NODE
{
	int key;
	NODE* p_next;
};

struct List 
{
	NODE* p_head;
	NODE* p_tail;
};

// --- Define function prototypes ---
NODE* createNode(int data);
List* createList(NODE* p_node);
bool addHead(List*& L, int data);
bool addTail(List*& L, int data);
bool removeHead(List*& L);
void removeTail(List*& L);
void removeAll(List*& L);
void removeBefore(List*& L, int val);
void removeAfter(List*& L, int val);
bool addPos(List*& L, int data, int pos);
void removePos(List*& L, int data, int pos);
bool addBefore(List*& L, int data, int val);
bool addAfter(List*& L, int data, int val);
void printList(List* L);
int countElements(List* L);
List* reverseList(List* L);
void removeDuplicate(List*& L);
bool removeElement(List*& L, int key);

// function to create a list from an array
List* createListFromArray(int arr[], int n)
{
	List* newList = new List();
	newList->p_head = NULL;
	newList->p_tail = NULL;
	for (int i = 0; i < n; ++i)
	{
		addTail(newList, arr[i]);
	}
	return newList;
}

// function to compare two lists
bool areListsEqual(List* list1, List* list2)
{
	NODE* current1 = list1 ? list1->p_head : NULL;
	NODE* current2 = list2 ? list2->p_head : NULL;
	while (current1 && current2)
	{
		if (current1->key != current2->key)
		{
			return false;
		}
		current1 = current1->p_next;
		current2 = current2->p_next;
	}
	return (current1 == NULL && current2 == NULL);
}

// function to free the memory of a list
void freeList(List* L)
{
	NODE* current = L->p_head;
	while (current)
	{
		NODE* next = current->p_next;
		delete current;
		current = next;
	}
	delete L;
}

NODE* createNode(int data)
{
	NODE* newNode = new NODE();
	newNode->key = data;
	newNode->p_next = NULL;
	return newNode;
}

List* createList(NODE* p_node)
{
	List* newList = new List;
	newList->p_head = p_node;
	newList->p_tail = p_node;
	return newList;
}

bool addHead(List*& L, int data)
{
	NODE* newNode = createNode(data);
	if (newNode == NULL)
		return false;
	// xử lý danh sách rỗng
	if (L->p_head == NULL)
	{
		L->p_head = L->p_tail = newNode;
	}
	// xử lý danh sách không rỗng
	else
	{
		newNode->p_next = L->p_head;
		L->p_head = newNode;
	}
	return true;
}

bool addTail(List*& L, int data)
{
	NODE* newNode = createNode(data);
	if (newNode == NULL)
		return false;
	// Xử lý danh sách rỗng
	if (L->p_head == NULL)
	{
		L->p_head = L->p_tail = newNode;
	}
	// Xử lý danh sách không rỗng
	else
	{
		L->p_tail->p_next=newNode;
		L->p_tail = newNode;
	}
	return true;
}

bool removeHead(List*& L)
{
	if (L->p_head == NULL)
		return false;
	if (L->p_head == L->p_tail)
		L->p_head = L->p_tail = NULL;
	else
	{
		NODE* temp = L->p_head;
		L->p_head = L->p_head->p_next;
		delete temp;
	}
	return true;
}

void removeTail(List*& L)
{
	if (L->p_head == NULL)
		return;
	if (L->p_head == L->p_tail)
		L->p_head = L->p_tail = NULL;
	else
	{
		NODE* head1;
		head1 = L->p_head;
		while (head1->p_next->p_next != NULL)
		{
			head1 = head1->p_next;
		}
		delete L->p_tail;
		head1->p_next = NULL;
		L->p_tail = head1;
	}
	return;
}

void removeAll(List*& L)
{
	if (L->p_head == NULL)
		return;
	while (L->p_head != NULL)
	{
		removeHead(L);
	}
	return;
}

void removeBefore(List*& L, int val)
{
	// Xử lý trường hợp danh sách rỗng
	if (L->p_head == NULL)
		return;
	// Xử lý trường hợp có 1 Node và Node có giá trị val
	else if (L->p_head->key == val || L->p_head->p_next == NULL)
		return;
	// xử lý xóa Node đầu khi Node 2 mang giá trị val
    else if (L->p_head->p_next->key == val)
    {
        removeHead(L);
        return;
    }
	// Xử lý trường hợp còn lại
	else
	{
        NODE* head1 = L->p_head;
		while (head1->p_next!=NULL && head1->p_next->p_next != NULL)
		{
            if (head1->p_next->p_next->key == val)
            {
                NODE* temp = head1->p_next;
                head1->p_next = head1->p_next->p_next;
                delete temp;
                return;
            }
            head1 = head1->p_next;
		}
	}
}

void removeAfter(List*& L, int val) 
{
	if (L == NULL || L->p_head == NULL || L->p_head == L->p_tail) 
	{
		return;
	}
	NODE* head1 = L->p_head;
	// Duyệt để tìm node có giá trị val
	while (head1 != NULL && head1->p_next != NULL) 
	{
		if (head1->key == val) 
		{
			// Tìm thấy node có giá trị val
			NODE* nodeToDelete = head1->p_next;
			head1->p_next = nodeToDelete->p_next;
			// Cập nhật p_tail 
			if (nodeToDelete == L->p_tail) 
			{
				L->p_tail = head1;
			}
			delete nodeToDelete;
			return;
		}
		head1 = head1->p_next;
	}
}

bool addPos(List*& L, int data, int pos)
{
	if (pos < 0)
		return false;
	// Nếu pos == 0 thì thêm vào đầu
	if (pos == 0)
	{
		addHead(L, data);
		return true;
	}
    NODE* newNode = createNode(data);
	NODE* head1 = L->p_head;
	for (int i = 0; head1 && i < pos - 1; ++i) 
	{
		head1 = head1->p_next;
	}
	if (head1 == NULL)
		return false;
	// Thêm vào giữa hoặc cuối danh sách
	newNode->p_next = head1->p_next;
	head1->p_next = newNode;
	// Cập nhật p_tail nếu thêm vào cuối
	if (!newNode->p_next) 
	{
		L->p_tail = newNode;
	}
	return true;
}

void removePos(List*& L, int data, int pos)
{
	if ((L->p_head == NULL && L->p_tail == NULL) || pos < 0)
		return;
	if (pos == 0)
	{
		removeHead(L);
		return;
	}
	NODE* head1 = L->p_head;
	for (int i = 0; head1 && i < pos - 1; ++i)
	{
		head1 = head1->p_next;
	}
	if (head1 == NULL)
		return;
	// Xóa vào giữa hoặc cuối danh sách
	if (head1 == NULL || head1->p_next == NULL)
		return;
	NODE* temp = head1->p_next; // node cần xóa
	head1->p_next = temp->p_next;
	// Cập nhật p_tail nếu xóa vào cuối
	if (temp == L->p_tail)
	{
		L->p_tail = head1;
	}
	delete temp;
	return;
}

bool addBefore(List*& L, int data, int val)
{
	if (L->p_head == NULL)
		return false;
	else if (L->p_head->key == val)
	{
		addHead(L, data);
		return true;
	}
	NODE* pre = L->p_head;
	NODE* p = pre->p_next;
	while (p != NULL && p->key != val)
	{
		pre = p;
		p = p->p_next;
	}
	if (p == NULL)
		return false;
	NODE* newNode = createNode(data);
	pre->p_next = newNode;
	newNode->p_next = p;
	return true;
}

bool addAfter(List*& L, int data, int val)
{
	if (L->p_head == NULL)
		return false;
	NODE* head1 = L->p_head;
	// Duyệt để tìm node có giá trị val
	while (head1 != NULL)
	{
		if (head1->key == val)
		{
			// Tìm thấy node có giá trị val
			NODE* newNode = createNode(data);
			newNode->p_next = head1->p_next;
			head1->p_next = newNode;
			// Cập nhật p_tail 
			if (head1 == L->p_tail)
			{
				L->p_tail = newNode;
			}
			return true;
		}
		head1 = head1->p_next;
	}
}

void printList(List* L)
{
	if (L->p_head == NULL)
	{
		cout << "DS rong" << endl;
		return;
	}
	NODE* p = L->p_head;
	while (p != NULL)
	{
		cout << p->key << " ";
		p = p->p_next;
	}
	cout << endl;
}

int countElements(List* L)
{
	int count = 0;
	if (L->p_head == NULL)
	{
		return count;
	}
	NODE* p = L->p_head;
	while (p != NULL)
	{
		p = p->p_next;
		count++;
	}
	return count;
}

List* reverseList(List* L)
{
    List* temp = new List();
    temp->p_head = temp->p_tail = NULL;
    if (L == NULL || L->p_head == NULL)
        return temp;
    NODE* current = L->p_head;
    while (current != NULL)
    {
        NODE* newNode = createNode(current->key);  
        if (temp->p_head == NULL)
        {
            temp->p_head = temp->p_tail = newNode;
        }
        else
        {
            newNode->p_next = temp->p_head;
            temp->p_head = newNode;
        }
        current = current->p_next;
    }
    return temp;
}


void removeDuplicate(List*& L)
{
	if (L->p_head == NULL || L->p_head->p_next == NULL)
		return;
	NODE* p1 = L->p_head;
	while (p1 != NULL)
	{
		NODE* prev2 = p1;
		NODE* p2 = p1->p_next;
		while (p2 != NULL)
		{
			if (p2->key == p1->key)
			{
				prev2->p_next = p2->p_next;
				// Nếu xóa node cuối, cập nhật p_tail
				if (p2 == L->p_tail)
					L->p_tail = prev2;
				delete p2;
				p2 = prev2->p_next; 
			}
			else
			{
				prev2 = p2;
				p2 = p2->p_next;
			}
		}
		p1 = p1->p_next;
	}
}

bool removeElement(List*& L, int val)
{
	if (L->p_head == NULL) 
		return false;
	// Nếu node đầu là node cần xóa
	if (L->p_head->key == val)
	{
		removeHead(L);
		return true;
	}
	NODE* prev = L->p_head;
	NODE* curr = L->p_head->p_next;
	while (curr != NULL)
	{
		if (curr->key == val)
		{
			prev->p_next = curr->p_next;
			if (curr == L->p_tail)
				L->p_tail = prev;
			delete curr;
			return true;
		}
		prev = curr;
		curr = curr->p_next;
	}
	return false; 
}


