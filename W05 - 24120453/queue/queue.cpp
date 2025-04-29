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

struct Queue
{
    NODE* head;
    NODE* tail;
};

Queue* initializeQueue()
{
    Queue* q = new Queue;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

void enqueue(Queue*& q, int data)
{
    NODE* newNode = new NODE;
    newNode->key = data;
    newNode->p_next = NULL;

    if (q->head == NULL)
    {
        q->head = newNode;
        q->tail = newNode;
    }
    else
    {
        q->tail->p_next = newNode;
        q->tail = newNode;
    }
}

int dequeue(Queue*& q)
{
    if (q == NULL || q->head == NULL)
    {
        cout << "Queue NULL" << endl;
        return -1;
    }
    else
    {
        NODE* temp = q->head;
        int data = temp->key;
        q->head = q->head->p_next;
        if (q->head == NULL)
        {
            q->tail = NULL;
        }
        delete temp;
        return data;
    }
}

int size(Queue* q)
{
    if (q == NULL || q->head == NULL)
    {
        return 0;
    }
    else
    {
        int dem = 0;
        NODE* cur = q->head;
        while (cur != NULL)
        {
            dem++;
            cur = cur->p_next;
        }
        return dem;
    }
}

bool isEmpty(Queue* q)
{
    if (q == NULL || q->head == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void printQueue(Queue* q, ofstream& outFile)
{
    if (isEmpty(q))
    {
        outFile << "EMPTY" << endl;
        return;
    }

    int count = size(q);
    int* arr = new int[count];
    NODE* current = q->head;

    // Sao chép các phần tử vào mảng tạm
    for (int i = 0; i < count; i++)
    {
        arr[i] = current->key;
        current = current->p_next;
    }

    // In các phần tử từ mảng
    for (int i = 0; i < count; i++)
    {
        outFile << arr[i];
        if (i < count - 1)
            outFile << " ";
    }
    outFile << endl;

    delete[] arr;
}

void freeQueue(Queue*& q)
{
    while (q && q->head != NULL)
    {
        NODE* temp = q->head;
        q->head = q->head->p_next;
        delete temp;
    }
    delete q;
    q = NULL;
}

int main()
{
    ifstream inFile("input.txt");
    if (!inFile.is_open())
    {
        cout << "Khong mo duoc file input1.txt" << endl;
        return 1;
    }

    ofstream outFile("output.txt");
    if (!outFile.is_open())
    {
        cout << "Khong mo duoc file output1.txt" << endl;
        return 1;
    }

    Queue* q = NULL;
    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "init")
        {
            if (q != NULL)
                freeQueue(q);
            q = initializeQueue();
        }
        else if (cmd == "enqueue")
        {
            int value;
            ss >> value;
            enqueue(q, value);
        }
        else if (cmd == "dequeue")
        {
            dequeue(q);
        }
        else if (cmd == "size")
        {
            outFile << size(q) << endl;
        }
        else if (cmd == "isEmpty")
        {
            outFile << (isEmpty(q) ? "EMPTY" : "NOT EMPTY") << endl;
        }
        printQueue(q, outFile);
    }

    freeQueue(q);
    inFile.close();
    outFile.close();

    return 0;
}
