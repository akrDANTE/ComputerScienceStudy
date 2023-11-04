#include "DanteLib.h"
using namespace std;

vector<vector<int>> construct2DArray(vector<int> &original, int m, int n)
{
    vector<vector<int>> ans;
    if (original.size() != m * n)
        return ans;
    for (int i = 0; i < m; i++)
    {
        vector<int> row;
        for (int j = 0; j < n; j++)
        {
            int ind = (i * n + j) % original.size();
            row.push_back(original[ind]);
        }
        ans.push_back(row);
    }

    return ans;
}

int main()
{
    vector<int> v{1, 3, 5, 2, 4, 6};
    printMat(construct2DArray(v, 2, 3));
    return 0;
}