#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

int findNumberOfLIS(vector<int> &nums)
{
    unordered_map<int, int> lisCount;
    vector<int> dp(nums.size(), 1);
    vector<int> dpLen(nums.size(), 1);
    int max_len = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        int j = i - 1;
        int count = dpLen[i];
        while (j >= 0)
        {
            if (nums[j] < nums[i])
            {
                if (dp[i] == 1 + dp[j])
                {
                    count += dpLen[j];
                }
                else if (dp[i] < 1 + dp[j])
                {
                    dp[i] = 1 + dp[j];
                    count = dpLen[j];
                }
            }
            dpLen[i] = count;
            j--;
        }

        max_len = max(max_len, dp[i]);
        if (lisCount.find(max_len) == lisCount.end())
        {
            lisCount[max_len] = count;
        }
        else if (dp[i] == max_len)
            lisCount[max_len] += count;
    }
    return lisCount[max_len];
}

int main()
{
    vector<int> arr{1, 2, 4, 3, 5, 4, 7, 2};
    cout << "Max number " << findNumberOfLIS(arr) << endl;

    return 0;
}