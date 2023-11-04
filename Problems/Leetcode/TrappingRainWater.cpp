#include <iostream>
#include <vector>
using namespace std;

int trap(vector<int> &height)
{
    int left = 0, right = height.size() - 1;
    int ans = 0;
    int max_left = 0;
    int max_right = 0;

    while (left <= right)
    {
        if (height[left] <= height[right])
        {
            if (height[left] >= max_left)
                max_left = height[left];
            else
                ans += max_left - height[left];
            left++;
        }
        else
        {
            if (height[right] >= max_right)
                max_right = height[right];
            else
                ans += max_right - height[right];
            right--;
        }
    }
    return ans;
}

int main()
{
    vector<int> v{4, 9, 4, 5, 3, 2};
    cout << trap(v) << endl;
    return 0;
}