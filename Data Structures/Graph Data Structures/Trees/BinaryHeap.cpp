#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

priority_queue<int, vector<int>, std::greater<int>> pq;

class BinaryHeap
{
public:
    BinaryHeap() : size(0) { data.push_back(INT_MAX); }
    BinaryHeap(int sz) : size(0), data(sz, 0) { data.push_back(INT_MAX); }
    BinaryHeap(int len, int arr[]) : size(len)
    {
        data.push_back(INT_MAX);
        for (int i = 0; i < len; i++)
        {
            insert(arr[i]);
        }
    }
    void printHeap()
    {
        for (auto i : data)
            cout << i << ' ';
        cout << endl;
    }

    int top()
    {
        if (data.size() >= 2)
            return data[1];
        return -1; // heap empty
    }

    void insert(int i)
    {
        data.push_back(i);
        float_up(data.size() - 1);
    }

    void pop()
    {
        if (data.size() < 2)
        {
            cout << "empty stack" << endl;
            return;
        }
        swap(data[1], data[data.size() - 1]);
        data.pop_back();
        sink_down(1);
    }

    void delete_key(int ind)
    {
        if (ind >= data.size())
            return;
        if (ind == data.size() - 1)
        {
            data.pop_back();
            return;
        }
        swap(data[ind], data[data.size() - 1]);
        data.pop_back();
        sink_down(ind);
    }

    bool empty()
    {
        return data.size() == 1;
    }

private:
    int size;
    vector<int> data;
    inline int left(int i) { return 2 * i; }
    inline int right(int i) { return 2 * i + 1; }
    inline int parent(int i) { return i / 2; }
    void float_up(int i)
    {
        while (i > 1) // compare(i, parent(i))
        {
            if (data[i] > data[parent(i)])
            {
                swap(data[i], data[parent(i)]);
                i = parent(i);
            }
            else
            {
                return;
            }
        }
    }
    void sink_down(int i)
    {
        while (i < data.size())
        {
            int largest = i;
            if (left(i) < data.size() && data[largest] < data[left(i)])
                largest = left(i);
            if (right(i) < data.size() && data[largest] < data[right(i)])
                largest = right(i);
            if (largest != i)
            {
                swap(data[i], data[largest]);
                i = largest;
            }
            else
                return;
        }
    }
};

int main()
{
    int arr[] = {1, 5, 9, 10, 11, 13, 12, 13, 15};
    BinaryHeap maxHeap;
    for (int i = 0; i < 9; i++)
    {
        maxHeap.insert(arr[i]);
    }
    while (!maxHeap.empty())
    {
        cout << maxHeap.top() << endl;
        maxHeap.pop();
    }
    return 0;
}