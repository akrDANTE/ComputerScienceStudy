#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    vector<int> v{1, 1, -1, -2};
    auto it = upper_bound(v.rbegin(), v.rend(), -1);
    int value = v.rbegin() - it;
    cout << value << endl;
    if (it != v.rend())
        cout << *it << endl;
    else
        cout << "end \n";

    return 0;
}