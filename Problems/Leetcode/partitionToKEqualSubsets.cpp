#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

bool canPartitionKSubsets(vector<int> &nums, int k)
{
    int total_subsets = 1 << nums.size();
    int total_sum = accumulate(nums.begin(), nums.end(), 0);
    if (static_cast<double>(total_sum / k) != static_cast<double>(total_sum) / static_cast<double>(k))
    {
        return false;
    }
    int target = total_sum / k;
    int target_count = 0;
    vector<int> subsets;
    for (int i = 0; i < total_subsets; i++)
    {
        int curr_sum = 0;
        int ind = 0;
        for (int j = i; j > 0; j >>= 1)
        {
            if (j & 1)
            {
                curr_sum += nums[ind];
            }
            ind++;
            if (curr_sum > target)
                break;
        }
        if (curr_sum == target)
        {
            target_count++;
            bool flag = true;
            for (int s : subsets)
            {
                if (s & i)
                    flag = false;
            }
            if (flag)
                subsets.push_back(i);
            // cout << "curr_sum is : " << curr_sum << endl;
        }
    }
    int subset_acc = 0;
    for (int i : subsets)
    {
        cout << i << endl;
        subset_acc |= i;
    }
    if (subset_acc == total_subsets - 1)
        return true;
    return false;
}

int main()
{
    vector<int> v{1, 1, 1, 1, 2, 2, 2, 2};
    canPartitionKSubsets(v, 4);
    return 0;
}