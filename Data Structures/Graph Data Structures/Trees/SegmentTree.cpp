#include <iostream>
#include <vector>
using namespace std;

class SegTreeRec
{
public:
    SegTreeRec() : size(0) {}

    SegTreeRec(int len, int arr[]) : size(len)
    {
        data.resize(len * 4);
        lazy = vector<int>(2 * len, 0);
        buildTree(arr, 1, 0, len - 1);
    }

    int query(int l, int r)
    {
        return queryUtil(l, r, 1, 0, size - 1);
    }

    void update(int index, int value)
    {
        updateUtil(index, value, 1, 0, size - 1);
    }

    void update(int l, int r, int value)
    {
        rangeUpdateUtil(l, r, value, 1, 0, size - 1);
    }

private:
    vector<int> data;
    vector<int> lazy;
    int size;
    void buildTree(int arr[], int node, int l, int r)
    {
        if (l == r)
        {
            data[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        buildTree(arr, 2 * node, l, mid);
        buildTree(arr, 2 * node + 1, mid + 1, r);
        data[node] = data[2 * node] + data[2 * node + 1];
    }
    int queryUtil(int ql, int qr, int node, int l, int r)
    {
        if (lazy[node] != 0)
        {
            data[node] += (r - l + 1) * lazy[node];
            if (l != r)
            {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
        if (qr < l || ql > r)
            return 0;
        if (l == ql && qr == r)
        {
            return data[node];
        }
        // check left range
        int mid = (l + r) / 2;
        if (l <= ql && qr <= mid)
        {
            return queryUtil(ql, qr, 2 * node, l, mid);
        }
        if (mid < ql && qr <= r)
        {
            return queryUtil(ql, qr, 2 * node + 1, mid + 1, r);
        }
        return queryUtil(ql, mid, 2 * node, l, mid) + queryUtil(mid + 1, qr, 2 * node + 1, mid + 1, r);
    }
    void updateUtil(int index, int value, int node, int l, int r)
    {
        if (lazy[node] != 0)
        {
            data[node] += (r - l + 1) * lazy[node];
            if (l != r)
            {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
        if (l > r)
            return;
        if (l == r && l == index)
        {
            data[node] = value;
            return;
        }
        int mid = (l + r) / 2;
        if (index >= l && index <= mid)
            updateUtil(index, value, 2 * node, l, mid);
        if (index <= r && index > mid)
            updateUtil(index, value, 2 * node + 1, mid + 1, r);
        data[node] = data[2 * node] + data[2 * node + 1];
    }

    void rangeUpdateUtil(int ql, int qr, int value, int node, int l, int r)
    {
        if (lazy[node] != 0)
        {
            data[node] += (qr - ql + 1) * lazy[node];
            if (l != r)
            {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (qr < l || ql > r)
            return;

        if (ql <= l && r <= qr)
        {
            data[node] += (r - l + 1) * value;
            if (l != r)
            {
                lazy[2 * node] += value;
                lazy[2 * node + 1] += value;
            }
            return;
        }

        int mid = (r - l) / 2;

        rangeUpdateUtil(ql, qr, value, 2 * node, l, mid);
        rangeUpdateUtil(ql, qr, value, 2 * node + 1, mid + 1, r);

        data[node] = data[2 * node] + data[2 * node + 1];
    }
};

class SegTreeIter
{
public:
    SegTreeIter() : size(0), height(0), elements(0) {}
    SegTreeIter(int len, int arr[]) : elements(len)
    {
        size = 1;
        while (size < len)
            size *= 2;
        data = vector<int>(2 * size, 0);

        for (int i = 0; i < len; i++)
            data[size + i] = arr[i];

        for (int i = size - 1; i > 0; i--)
        {
            data[i] = data[2 * i] + data[2 * i + 1];
        }
    }

    void update(int index, int value)
    {
        index = size + index;
        data[index] = value;
        index /= 2;
        while (index > 0)
        {
            data[index] = data[2 * index] + data[2 * index + 1];
            index /= 2;
        }
    }

    void update(int l, int r, int value) // does not work
    {
        l += size;
        r += size;
        while (l < r)
        {
            if (l & 1)
                data[l++] += value;
            if (r & 1)
                data[--r] += value;
            l /= 2;
            r /= 2;
        }
    }

    /*
     If l, the left interval border, is odd (which is equivalent to l&1) then l is the right child of its parent.
     Then our interval includes node l but doesn't include it's parent. So we add t[l] and move to the right of l's parent by setting l = (l + 1) / 2.
     If l is even, it is the left child, and the interval includes its parent as well (unless the right border interferes), so we just move to it by setting l = l / 2.
     Similar argumentation is applied to the right border. We stop once borders meet.
     */
    int query(int l, int r) // [l, r)
    {
        l += size;
        r += size + 1;
        int sum = 0;
        while (l < r)
        {
            if (l & 1)
                sum += data[l++];
            if (r & 1)
                sum += data[--r];
            r /= 2;
            l /= 2;
        }
        return sum;
    }

    void push()
    {
        for (int i = 1; i < size; i++)
        {
            data[2 * i] += data[i];
            data[2 * i + 1] += data[i];
            data[i] = 0;
        }
    }

private:
    int size, height, elements;
    vector<int> data;
};

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    SegTreeIter st(10, arr);
    cout << st.query(0, 9) << endl;
    cout << st.query(2, 4) << endl;
    cout << st.query(1, 6) << endl;
    st.update(2, 0); // { 1, 2, 0, 4, 5, 6, 7, 8, 9, 10 }
    cout << st.query(0, 9) << endl;
    st.update(1, 4, 3); // { 1, 5, 3, 7, 8, 6, 7, 8, 9, 10 }
    cout << st.query(1, 4) << endl;
    return 0;
}