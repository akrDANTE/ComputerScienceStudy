#pragma once

#include <vector>
#include <utility> //pair
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <climits>

void printVect(std::vector<int> &v)
{
    for (auto i : v)
        std::cout << i << ' ';
    std::cout << std::endl;
}

void printMat(std::vector<std::vector<int>> &&mat)
{
    for (auto &row : mat)
        printVect(row);
}

auto swapx = [](int &a, int &b)
{
    if (a != b)
    {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
    }
};