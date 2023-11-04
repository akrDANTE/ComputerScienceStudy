#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int shortestCellPath(const vector<vector<int>> &grid, int sr, int sc, int tr, int tc)
{
    // your code goes here
    queue<pair<int, int>> q;
    q.push({sr, sc});
    int distance = 0;
    int visited[10][10];
    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[0].size(); j++)
            visited[i][j] = 0;
    int xd[] = {-1, 0, 1, 0};
    int yd[] = {0, 1, 0, -1};
    auto valid = [&](int x, int y)
    {
        if (x < 0 || y < 0 || x > grid.size() || y > grid[0].size())
            return false;
        if (visited[x][y])
            return false;
        if (grid[x][y] == 0)
            return false;
        return true;
    };
    while (!q.empty())
    {
        int len = q.size();
        for (int i = 0; i < len; i++)
        {
            pair<int, int> curr = q.front();
            q.pop();
            visited[curr.first][curr.second] = 1;
            if (curr.first == tr && curr.second == tc)
                return distance;
            for (int dir = 0; dir < 4; dir++)
            {
                int nextx = curr.first + xd[dir];
                int nexty = curr.second + yd[dir];
                if (valid(nextx, nexty))
                    q.push({nextx, nexty});
            }
        }
        distance++;
    }
    return -1;
}

int main()
{
    vector<vector<int>> grid = {{1, 1, 1, 1},
                                {0, 0, 0, 1},
                                {1, 1, 1, 1}};
    cout << shortestCellPath(grid, 0, 0, 2, 0) << endl;
    return 0;
}