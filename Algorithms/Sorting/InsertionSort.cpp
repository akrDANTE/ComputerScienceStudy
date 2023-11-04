#include <iostream>
#include <vector>
using namespace std;

inline void printVec(vector<int> &arr)
{
    for (int i : arr)
        cout << i << ' ';
}

void swap(int &a, int &b)
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

void insertionSort(vector<int> &nums)
{
    /*
        Basic idea is take every index and put it into it's correct spot in each iteration.
        Compare with previous elements and if ordered properly, send it to it's place, pushing
        it backwards.
        Shoot integers backwards into their place.
        Good for cases when array is mostly sorted.
        Worst case time complexity: O(n^2)
        Space complexity : O(1)
    */
    for (int i = 0; i < nums.size(); i++)
    {
        int j = i;
        while (j > 0 && nums[j] < nums[j - 1])
        {
            swap(nums[j - 1], nums[j]);
            j--;
        }
    }
}

int main()
{
    vector<int> arr{5, 4, 3, 2, 1};
    insertionSort(arr);
    printVec(arr);
    cout << endl;
    return 0;
}