#include <iostream>
#include <string>
#include <list>
using namespace std;

template <typename T, int sz>
class Stack
{
public:
    Stack() : size(0) {}
    void push(const T &d)
    {
        if (size == sz)
        {
            cout << "Stack overflow\n";
            return;
        }
        data[size++] = d;
    }
    void pop()
    {
        if (size == 0)
        {
            cout << "empty stack\n";
            return;
        }
        size--;
    }
    T top()
    {
        if (size == 0)
        {
            throw out_of_range("Empty stack!");
        }
        return data[size - 1];
    }
    bool empty()
    {
        return size == 0;
    }

private:
    int size;
    T data[sz];
};

template <typename T>
class StackList
{
public:
    void push(const T d)
    {
        data.push_front(d);
    }
    void pop()
    {
        if (data.empty())
        {
            cout << "Empty stack!";
            return;
        }
        data.pop_front();
    }
    T top()
    {
        if (data.empty())
        {
            throw out_of_range("Empty stack!");
        }
        return data.front();
    }
    bool empty()
    {
        return data.empty();
    }

private:
    list<T> data;
};

// template <typename T>
// class StackInherit : public list<T>
// {
// public:
//     StackInherit() {}
//     void push(const T data)
//     {
//         push_front(data);
//     }

//     void pop()
//     {
//         if (empty())
//         {
//             cout << "Empty Stack!!";
//             return;
//         }
//         pop_front();
//     }

//     T top()
//     {
//         if (empty())
//         {
//             throw out_of_range("empty stack!!");
//         }
//         return front();
//     }
// };

int main()
{
    StackList<string> s;
    s.push("a");
    s.push("b");
    s.push("c");
    s.push("d");
    s.push("e");
    s.push("f");
    while (!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
    return 0;
}