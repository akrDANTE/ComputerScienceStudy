#include "DanteLib.h"

using namespace std;

int totalFruit(vector<int> &fruits)
{
    int max_len = INT_MIN;
    int window_start = 0;
    pair<int, int> baskets{-1, -1};
    baskets.first = window_start;
    for (int i = 0; i < fruits.size(); i++)
    {
        if (baskets.second == -1)
        {
            if (fruits[i] != fruits[window_start])
                baskets.second = i;
            // continue;
        }
        if (fruits[i] != fruits[baskets.first] && fruits[i] != fruits[baskets.second])
        {
            max_len = max(max_len, i - window_start);
            window_start = baskets.second;
            baskets.first = window_start;
            baskets.second = -1;
            i = window_start;
            continue;
        }
        max_len = max(max_len, i - window_start + 1);
    }
    return max_len;
}

int main()
{
    vector<int> v{3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};
    cout << totalFruit(v);
    return 0;
}