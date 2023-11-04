#include "DanteLib.h"
using namespace std;

vector<int> findDisappearedNumbers(vector<int> &nums)
{
    vector<int> ans;
    // negative marking
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[abs(nums[i]) - 1] > 0)
            nums[abs(nums[i]) - 1] *= -1;
    }
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] > 0)
            ans.push_back(i + 1);
    }
    return ans;
}

int main()
{
    vector<int> v{4, 3, 2, 7, 8, 2, 3, 1};
    auto ans = findDisappearedNumbers(v);
    return 0;
}