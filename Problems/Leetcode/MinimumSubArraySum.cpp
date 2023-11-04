#include "DanteLib.h"

using namespace std;

int minSubArrayLen(int target, vector<int> &nums)
{
    int window_start = 0;
    int window_len = INT_MAX;
    int window_sum = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (window_sum < target)
        {
            window_sum += nums[i];
        }
        else if (window_sum >= target)
        {
            window_len = min(window_len, i - window_start - 1);
            while (window_start <= i && target - window_sum >= nums[window_start])
            {
                window_sum -= nums[window_start];
                window_start++;
            }
        }
    }
    return window_len == INT_MAX ? 0 : window_len;
}

int main()
{
    vector<int> v{2, 3, 1, 2, 4, 3};
    cout << minSubArrayLen(7, v);
    return 0;
}