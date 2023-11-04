#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
/*
    Binary search: searches for the element in a sorted array in log(n) time.
    basic idea is that we are halving the search space at each iteration, that means we check whether element is in the middle, or first half or second half.

    It can also be applied in cases where a monotonic property can be observed. For example a sequence always increasing or decreasing.

    mid = (r + l) / 2 or mid = l + (r-l)/2; use second one when r+l goes out of bounds.

    Another application of binary search is peak index finding:
        Look for a value for which some property hods true in the array and also after that point it becomes false.
        Example: 1, 2, 3, 2, 1 -- increases till 3 then starts to decrease.
                 T, T, T, F, F
        For peak finding we have to find the rightmost point in the array where a[mid] > a[mid - 1]

    for finding right most and leftmost elements when duplicate elements in the array:
    //for rightmost
    start = 0;
    end = n;
    while(start < end)
    {
        mid = floor((start + end)/2);
        if (a[mid] > target)
            end = mid;
        else
            start = mid + 1;
    }
    return end - 1;

    // for leftmost
    start = 0;
    end = n;
    while(start < end)
    {
        mid = floor((start + end)/2);
        if(a[mid] < target)
            start = mid + 1;
        else
            end = mid;
    }
    return start;

    finding lower and upper bound of an element:
    int l = -1; r = n;
    while(r - l > 1)
    {
        int m = (l + r )/2;
        if (target < a[m])
            r = m;
        else
            l = m;
    }
    l contains lower_bound(last element that is not greater than target)
    r contains upper_bound(first element larger than target)
*/
int binarySearch_iterative(vector<int> &v, int target)
{
    int start = 0,
        end = v.size() - 1;
    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        if (v[mid] == target)
            return mid;
        else if (v[mid] < target)
        {
            /*
            peak finding:
            if(mid == 0 || v[mid] > v[mid - 1]) //at 0 mid is always greater than previous value
                ans = mid;
            */
            // ans = v[mid]; //to find greatest smaller than target. => lower_bound
            // lower bound is first element not less than target i.e. <= target
            start = mid + 1;
        }
        else
        {
            // ans = v[mid]; //to find smallest greater than target. => upper_bound
            end = mid - 1;
        }
    }
    return -1;
}

int binarySearch_rec(int start, int end, vector<int> &v, int target)
{
    if (start > end)
        return -1;
    int mid = start + (end - start) / 2;
    if (v[mid] == target)
        return mid;
    else if (v[mid] < target)
    {
        return binarySearch_rec(mid + 1, end, v, target);
    }
    else
    {
        return binarySearch_rec(start, mid - 1, v, target);
    }
}

void binarySearch_stl(vector<int> &v, int target)
{
    // upper bound returns iterator to first element greater than the target.
    cout << "Upper Bound : \n";
    cout << *upper_bound(v.begin(), v.end(), target) << endl;
    // lower bound returns iterator to first element less than or equal to the target.
    cout << "Lower Bound : \n";
    cout << *lower_bound(v.begin(), v.end(), target) << endl;
    // binary search returns 0 if not found, 1 if found in the array.
    cout << "binary_search(stl) : \n";
    cout << binary_search(v.begin(), v.end(), target) << endl;
}

int binarySearch_recursive(vector<int> &v, int target)
{
    return binarySearch_rec(0, v.size() - 1, v, target);
}

int main()
{
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "Binary Search Iterative: \n";
    cout << binarySearch_iterative(v, 23) << endl;
    cout << "Binary Search Recursive: \n";
    cout << binarySearch_recursive(v, 23) << endl;
    binarySearch_stl(v, 6);
    binarySearch_stl(v, 23);
    binarySearch_stl(v, -1);
    return 0;
}