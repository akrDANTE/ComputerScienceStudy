#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *removeNthFromEnd(ListNode *head, int n)
{
    ListNode *slow = head;
    ListNode *fast = head;

    int length = -1;
    int count = 0;

    while (fast && fast->next)
    {
        fast = fast->next->next;
        count++;
    }
    length = !fast ? 2 * count : 2 * count + 1;
    int index = length - n;
    if (index == 0)
    {
        return head->next;
    }
    count = 0;
    while (count < index - 1)
    {
        slow = slow->next;
        count++;
    }
    if (slow && slow->next)
        slow->next = slow->next->next;
    return head;
}

int main()
{
    ListNode head(1), n2(2), n3(3), n4(4), n5(5);
    head.next = &n2;
    removeNthFromEnd(&head, 1);
    return 0;
}