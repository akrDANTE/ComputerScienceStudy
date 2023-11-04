#include <iostream>
#include <vector>

using namespace std;

vector<int> spiralOrder(vector<vector<int>> &matrix)
{
    int top_left = 0;
    int top_right = matrix[0].size();
    int bottom_left = 0;
    int bottom_right = matrix.size();
    int total_elements = 0;
    int rows = matrix.size();
    int cols = top_right;
    vector<int> ans;
    while (total_elements < rows * cols)
    {
        for (int i = top_left; i < top_right; i++)
        {
            ans.push_back(matrix[top_left][i]);
            total_elements++;
        }
        top_left++;
        top_right--;

        for (int i = top_left; i < bottom_right; i++)
        {
            ans.push_back(matrix[i][top_right]);
            total_elements++;
        }
        top_right--;
        bottom_right--;

        for (int i = top_right; i >= bottom_left; i--)
        {
            ans.push_back(matrix[bottom_right][i]);
            total_elements++;
        }
        bottom_left--;
        bottom_right--;

        for (int i = bottom_left; i >= top_left; i++)
        {
            ans.push_back(matrix[i][bottom_left]);
            total_elements++;
        }
        bottom_left--;
    }
    return ans;
}

int main()
{
    vector<vector<int>> v{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    spiralOrder(v);
    return 0;
}