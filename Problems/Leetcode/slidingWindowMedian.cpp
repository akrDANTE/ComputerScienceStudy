#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class Heap
{
public:
    Heap(T gr) : great(gr)
    {
        data = vector<int>(1);
        data.push_back(0);
    }

    int top()
    {
        if (!empty())
            return data[1];
        else
            return -1;
    }

    int push(int el)
    {
        data.push_back(el);
        int ind = data.size() - 1;
        float_up(data.size() - 1, ind);
        return ind;
    }

    void pop()
    {
        if (empty())
            return;
        swap(data[1], data[data.size() - 1]);
        data.pop_back();
        sink_down(1);
    }

    void remove(int index)
    {
        if (empty())
            return;
        swap(data[index], data[data.size() - 1]);
        data.pop_back();
        sink_down(index);
    }

    inline bool empty()
    {
        return data.size() == 1;
    }

    inline int size()
    {
        return data.size() - 1;
    }

private:
    void sink_down(int root)
    {
        int curr = root;
        int left = left_child(root);
        int right = right_child(root);
        while (curr < data.size())
        {
            int largest = curr;
            if (left < data.size() && great(data[left], data[largest]))
                largest = left;
            if (right < data.size() && great(data[right], data[largest]))
                largest = right;
            if (largest == curr)
                return;
            swap(data[largest], data[curr]);
            curr = largest;
            left = left_child(curr);
            right = left_child(curr);
        }
    }

    void float_up(int root, int &ind)
    {
        while (root > 1)
        {
            int par = parent(root);
            if (great(data[root], data[par]))
            {
                swap(data[root], data[par]);
                root = par;
                ind = root;
            }
            else
                return;
        }
    }

    inline int left_child(int root)
    {
        return root * 2 + 1;
    }

    inline int right_child(int root)
    {
        return root * 2 + 2;
    }

    inline int parent(int root)
    {
        return root / 2;
    }

    vector<int> data;
    T great;
};

vector<double> medianSlidingWindow(vector<int> &nums, int k)
{
    vector<double> ans;
    auto large = [&](int i, int j)
    {
        return nums[i] > nums[j];
    };
    auto small = [&](int i, int j)
    {
        return nums[i] < nums[j];
    };
    Heap maxHeap(large);
    Heap minHeap(small);
    for (int i = 0; i < nums.size(); i++)
    {
        maxHeap.push(i);
        minHeap.push(i);
    }

    while (!maxHeap.empty())
    {
        cout << "Max " << nums[maxHeap.top()] << endl;
        maxHeap.pop();
        cout << "Min " << nums[minHeap.top()] << endl;
        minHeap.pop();
    }
    return ans;
}

int main()
{

    return 0;
}