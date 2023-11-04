#include <vector>
#include <iostream>
using namespace std;
#define vvc vector<vector<char>>

void resetArr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = 0;
}
bool isValid(vvc &board)
{
    // check rows
    int count[10] = {0};
    for (auto &row : board)
    {
        for (auto &c : row)
        {
            if (c == '.')
                return false;
            count[c - '0']++;
            if (count[c - '0'] > 1)
                return false;
        }
        for (int i = 1; i < 10; i++)
        {
            if (count[i] != 1)
                return false;
        }
        resetArr(count, 10);
    }
    // check columns
    for (int c = 0; c < 9; c++)
    {
        for (int r = 0; r < 9; r++)
        {
            if (board[r][c] == '.')
                return false;
            count[board[r][c] - '0']++;
            if (count[board[r][c] - '0'] > 1)
                return false;
        }
        for (int i = 1; i < 10; i++)
        {
            if (count[i] != 1)
                return false;
        }
        resetArr(count, 10);
    }
    // check grids
    for (int r = 0; r < 9; r += 3)
    {
        for (int c = 0; c < 9; c += 3)
        {
            int gridw = r + 3;
            int gridh = c + 3;
            for (int i = r; i < gridw; i++)
            {
                for (int j = c; j < gridh; j++)
                {
                    if (board[i][j] == '.')
                        return false;
                    count[board[i][j] - '0']++;
                    if (count[board[i][j] - '0'] > 1)
                        return false;
                }
            }
            for (int i = 1; i < 10; i++)
            {
                if (count[i] != 1)
                    return false;
            }
            resetArr(count, 10);
        }
    }

    return true;
}

void getCandidates(vvc &board, vector<char> &candidates, int i, int j)
{
    // check row
    int count[10] = {0};
    for (int c = 0; c < 9; c++)
    {
        if (board[i][c] != '.')
            count[board[i][c] - '0']++;
    }
    // check col
    for (int r = 0; r < 9; r++)
    {
        if (board[r][j] != '.')
            count[board[r][j] - '0']++;
    }
    // check grid
    int gridx = 0;
    int gridy = 0;
    if (i >= 0 && i < 3)
        gridx = 0;
    if (i >= 3 && i < 6)
        gridx = 3;
    if (i >= 6 && i < 9)
        gridx = 6;
    if (j >= 0 && j < 3)
        gridy = 0;
    if (j >= 3 && j < 6)
        gridy = 3;
    if (j >= 6 && j < 9)
        gridy = 6;
    for (int in = gridx; in < gridx + 3; in++)
    {
        for (int jn = gridy; jn < gridy + 3; jn++)
        {
            if (board[in][jn] != '.')
            {
                count[board[in][jn] - '0']++;
            }
        }
    }
    for (int i = 1; i < 10; i++)
    {
        if (count[i] == 0)
            candidates.push_back(i + '0');
    }
}

bool backtrack(vector<vector<char>> &board)
{
    if (isValid(board))
        return true;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == '.')
            {
                vector<char> candidates;
                getCandidates(board, candidates, i, j);
                bool childAns = false;
                for (char c : candidates)
                {
                    board[i][j] = c;
                    childAns = backtrack(board);
                    if (childAns)
                        return true;
                }
                board[i][j] = '.';
                return false;
            }
        }
    }
    return false;
}
void solveSudoku(vector<vector<char>> &board)
{
    backtrack(board);
}

int main()
{
    vector<vector<char>> board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                  {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                  {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                  {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                  {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                  {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                  {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                  {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                  {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    backtrack(board);
    for (auto &row : board)
    {
        for (auto &c : row)
            cout << c << ' ';
        cout << endl;
    }
    return 0;
}