#include "DanteLib.h"

using namespace std;

vector<pair<int, int>> two_sum(vector<int> &nums, int beg, int target)
{
    vector<pair<int, int>> ret;
    int left = beg;
    int right = nums.size() - 1;

    while (left < right)
    {
        if (nums[left] + nums[right] == target)
        {
            ret.push_back({left, right});
            while (left < right && nums[left] == nums[left + 1])
                left++;
            while (left < right && nums[right] == nums[right - 1])
                right--;
            left++;
            right--;
        }
        else if (nums[left] + nums[right] < target)
        {
            left++;
        }
        else
        {
            right--;
        }
    }

    return ret;
}

vector<vector<int>> threeSum(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    for (int i = 0; i < nums.size() - 2; i++)
    {
        int target = 0 - nums[i];
        auto ret = std::move(two_sum(nums, i + 1, target));
        while (i < nums.size() - 2 && nums[i] == nums[i + 1])
            i++;
        if (ret.size() != 0)
        {
            for (auto r : ret)
                ans.push_back({nums[i], nums[r.first], nums[r.second]});
        }
    }
    return ans;
}

int main()
{
    vector<int> v{-1, 0, 1, 2, -1, -4};
    printMat(threeSum(v));
    return 0;
}