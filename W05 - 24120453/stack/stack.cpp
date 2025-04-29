#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct NODE
{
	int key;
	NODE* p_next;
};

struct Stack
{
	NODE* top;
};

Stack* initializeStack()
{
	Stack* s = new Stack;
	s->top = NULL;
	return s;
}

void push(Stack*& s, int data)
{
	NODE* newNode = new NODE;
	if (newNode == NULL)
	{
		cout << "node creation failed";
	}
	else
	{
		newNode->key = data;
		newNode->p_next = s->top;
		s->top = newNode;
	}
}

int pop(Stack*& s)
{
	if (s == NULL)
	{
		cout << "Stack NULL" << endl;
		return -1;
	}
	else
	{
		NODE* temp = s->top;
		int data = temp->key;
		s->top = s->top->p_next;
		delete temp;
		return data;
	}
}

int size(Stack* s)
{
	if (s == NULL)
	{
		cout << "Stack NULL" << endl;
		return 0;
	}
	else
	{
		int dem = 0;
		NODE* temp = s->top;
		while (temp != NULL)
		{
			dem++;
			temp = temp->p_next;
		}
		return dem;
	}
}

bool isEmpty(Stack* s)
{
	if (s == NULL || s->top == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void printStack(Stack* s, ofstream& outFile)
{
	if (isEmpty(s))
	{
		outFile << "EMPTY" << endl;
		return;
	}

	int count = size(s);
	int* arr = new int[count];
	NODE* current = s->top;
	for (int i = 0; i < count; i++)
	{
		arr[i] = current->key;
		current = current->p_next;
	}

	for (int i = 0; i < count; i++)
	{
		outFile << arr[i];
		if (i < count - 1)
			outFile << " ";
	}
	outFile << endl;
	delete[] arr;
}

void freeStack(Stack*& s)
{
	while (s && s->top != NULL)
	{
		pop(s);
	}
	delete s;
	s = NULL;
}

int main()
{
	ifstream inFile("input.txt");
	if (!inFile.is_open())
	{
		cout << "Khong mo duoc file input.txt" << endl;
		return 1;
	}

	ofstream outFile("output.txt");
	if (!outFile.is_open())
	{
		cout << "Khong mo duoc file output.txt" << endl;
		return 1;
	}

	Stack* s = NULL;
	string line;
	while (getline(inFile, line))
	{
		stringstream ss(line);
		string cmd;
		ss >> cmd;

		if (cmd == "init")
		{
			if (s != NULL)
				freeStack(s);
			s = initializeStack();
		}
		else if (cmd == "push")
		{
			int value;
			ss >> value;
			push(s, value);
		}
		else if (cmd == "pop")
		{
			pop(s);
		}
		else if (cmd == "size")
		{
			outFile << size(s) << endl;
		}
		else if (cmd == "isEmpty")
		{
			outFile << (isEmpty(s) ? "EMPTY" : "NOT EMPTY") << endl;
		}
		printStack(s, outFile);
	}

	freeStack(s);
	inFile.close();
	outFile.close();

	return 0;
}
