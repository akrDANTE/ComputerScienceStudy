#include "DanteLib.h"
using namespace std;

int twoSumClosest(vector<int> &nums, int left, int right, int target)
{
    if (left == right)
        return nums[left];
    int min_diff = INT_MAX;
    int ans = INT_MAX;
    while (left < right)
    {
        int diff = abs(target - nums[left] - nums[right]);
        if (diff < min_diff)
        {
            min_diff = diff;
            ans = nums[left] + nums[right];
        }
        if (min_diff == 0)
            return ans;
        // while (left < right && nums[left] == nums[left + 1])
        //     left++;
        // while (right > left && nums[right] == nums[right - 1])
        //     right--;
        // if (left == right)
        //     break;
        if (nums[left] + nums[right] < target)
            left++;
        else
            right--;
    }
    return ans;
}

int threeSumClosest(vector<int> &nums, int target)
{
    sort(nums.begin(), nums.end());
    int len = nums.size();
    int min_diff = INT_MAX;
    int ans = INT_MAX;
    for (int i = 0; i < len - 2; i++)
    {
        int two_sum = twoSumClosest(nums, i + 1, len - 1, target - nums[i]);
        if (abs(target - two_sum - nums[i]) < min_diff)
        {
            ans = two_sum + nums[i];
            min_diff = abs(target - two_sum - nums[i]);
        }
        if (min_diff == 0)
            return ans;
    }
    return ans;
}

int main()
{
    vector<int> v{-1000, -5, -5, -5, -5, -5, -5, -1, -1, -1};
    cout << threeSumClosest(v, -14);
    return 0;
}