#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int eraseOverlapIntervals(vector<vector<int>> &intervals)
{
    auto less = [&](vector<int> &a, vector<int> &b)
    {
        if (a[1] < b[1])
            return true;
        else if (a[1] == b[1])
        {
            return a[0] < b[0];
        }
        return false;
    };

    sort(intervals.begin(), intervals.end(), less);

    int ans = 0;
    for (int i = 0; i < intervals.size(); i++)
    {
        cout << "[" << intervals[i][0] << ", " << intervals[i][1] << "]"
             << " ";
        if (i > 0 && intervals[i][0] < intervals[i - 1][1])
            ans++;
    }
    return 0;
}

int main()
{
    vector<vector<int>> intervals = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
    int ans = eraseOverlapIntervals(intervals);
    cout << ans << endl;
    string s = to_string(-250);
    cout << s << endl;
    return 0;
}