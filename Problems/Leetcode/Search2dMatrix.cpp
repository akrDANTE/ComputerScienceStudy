#include <vector>
#include <iostream>

using namespace std;

inline pair<int, int> oneDTotwoD(int m, int n, int ind)
{
    // 3 * 4 - 1 = 11 / 4 = 2(row), 11%4 = 3(column)
    return {ind / n, ind % n};
}
bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    int m = matrix.size();
    int n = matrix[0].size();
    int start = 0;
    int end = m * n - 1;
    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        auto ind = oneDTotwoD(m, n, mid);
        if (matrix[ind.first][ind.second] == target)
            return true;
        else if (matrix[ind.first][ind.second] > target)
            end = mid - 1;
        else
            start = mid + 1;
    }
    return false;
}

int main()
{
    vector<vector<int>> mat = {{1, 1}};
    int target = 2;
    searchMatrix(mat, target);
    return 0;
}