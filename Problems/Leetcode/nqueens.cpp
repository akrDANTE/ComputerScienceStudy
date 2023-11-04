#include <vector>
#include <string>
#include <iostream>

using namespace std;

bool isSafe(vector<string> &curr, int pos, int queen)
{
    // check column
    int n = curr.size();
    for (int r = 0; r < curr.size(); r++)
    {
        if (r != queen)
        {
            if (curr[r][pos] == 'Q')
                return false;
        }
    }

    // diagonal top-left to bottom-right
    for (int i = queen - 1, j = pos - 1; i >= 0 && j >= 0; i--, j--)
    {
        if (curr[i][j] == 'Q')
            return false;
    }
    for (int i = queen + 1, j = pos + 1; i < n && j < n; i++, j++)
    {
        if (curr[i][j] == 'Q')
            return false;
    }

    // diagonal top-right to bottom-left
    for (int i = queen - 1, j = pos + 1; i >= 0 && j < n; i--, j++)
    {
        if (curr[i][j] == 'Q')
            return false;
    }
    for (int i = queen + 1, j = pos - 1; i < n && j >= 0; i++, j--)
    {
        if (curr[i][j] == 'Q')
            return false;
    }
    return true;
}
void getCandidates(vector<int> &candidates, vector<string> &curr, int queen)
{
    if (queen == 0)
    {
        for (int i = 0; i < curr.size(); i++)
            candidates.push_back(i);
        return;
    }
    for (int i = 0; i < curr.size(); i++)
    {
        if (isSafe(curr, i, queen))
            candidates.push_back(i);
    }
}
void nqueens(vector<vector<string>> &ans, vector<string> &curr, int queens)
{
    if (queens == curr.size())
    {
        ans.push_back(curr);
        return;
    }
    vector<int> candidates;
    getCandidates(candidates, curr, queens);
    for (int i : candidates)
    {
        curr[queens][i] = 'Q';
        nqueens(ans, curr, queens + 1);
        curr[queens][i] = '.';
    }
}

vector<vector<string>> solveNQueens(int n)
{
    vector<vector<string>> ans;
    string empty(n, '.');
    vector<string> curr(n, empty);
    nqueens(ans, curr, 0);
    return ans;
}

int main()
{
    vector<vector<string>> ans;
    ans = solveNQueens(4);
    for (auto a : ans)
    {
        cout << "solution \n";
        for (auto s : a)
        {
            cout << s << endl;
        }
    }
    return 0;
}