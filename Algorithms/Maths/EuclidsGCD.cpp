#include <iostream>
using namespace std;

/*
Euclid's Algorithm to find GCD :
Input : a, b (integers)
Steps:
    i)   Take a as the greater of a and b.
    ii)  Divide a by b so that a = q*b + r
    iii) set a = b and b = r.
    iv)  Repeat till b becomes 0.
    v)   Value of a is GCD when b is 0
*/

void swap(int &a, int &b)
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

int EuclidGCD_iterative(int a, int b)
{
    if (a < b)
        swap(a, b);
    if (a == b)
        return a;
    while (b != 0)
    {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int EuclidGCD_recursive_main(int a, int b)
{
    if (b == 0)
        return a;
    return EuclidGCD_recursive_main(b, a % b);
}

int Euclid_recursive(int a, int b)
{
    if (a < b)
        swap(a, b);
    if (a == b)
        return a;
    return EuclidGCD_recursive_main(a, b);
}

int main()
{
    cout << EuclidGCD_iterative(35, 21) << endl;
    cout << Euclid_recursive(45, 15) << endl;

    return 0;
}