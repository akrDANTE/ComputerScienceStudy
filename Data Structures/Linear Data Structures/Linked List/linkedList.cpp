#include <iostream>

using namespace std;

const int POOL_SIZE{60007};
int pool_index = 0;
class Node
{
    int data;
    Node *next;

public:
    Node() : data{0}, next{nullptr} {}
    Node(int d) : data{d}, next{nullptr} {}
    void reset()
    {
        data = 0;
        next = nullptr;
    }
    friend class SinglyLinkedList;
    friend Node *get_node(int);
};

Node memory_pool[POOL_SIZE];
Node *get_node(int i = 0)
{
    if (pool_index < POOL_SIZE)
    {
        memory_pool[pool_index].reset();
        memory_pool[pool_index].data = i;
        return &memory_pool[pool_index++];
    }
    else
    {
        return new Node();
    }
}

class SinglyLinkedList
{
    Node *head;
    int len;

public:
    /*
        use dummy node in cases where we need to change the position of the head node. In that case head will be dummy->next; dummy will be the first node.
    */
    SinglyLinkedList() : head{nullptr}, len{0} {}
    void push_front(int i)
    {
        Node *temp = get_node(i);
        if (head == nullptr)
        {
            head = temp;
        }
        else
        {
            temp->next = head;
            head = temp;
        }
        len++;
    }
    void push_back(int i)
    {
        Node *temp = get_node(i);
        if (head == nullptr)
        {
            head = temp;
            return;
        }
        Node *it = head;
        while (it->next != nullptr)
        {
            it = it->next;
        }
        it->next = temp;
        len++;
    }
    int get(int index)
    {
        if (index < 0 || index >= len)
        {
            throw out_of_range("Index out of range");
        }
        Node *it = head;
        int i = 0;
        while (it != nullptr && i < index)
        {
            it = it->next;
            i++;
        }
        if (i < index || it == nullptr)
        {
            throw out_of_range("Index Out of range");
        }
        if (head == nullptr)
        {
            throw("Empty Linked List");
        }
        return it->data;
    }
    void insert(int index, int data)
    {
        if (index < 0)
        {
            throw out_of_range("Index out of range");
        }
        Node *it = head;
        int i = 0;
        while (it->next != nullptr && i < index - 1)
        {
            it = it->next;
            i++;
        }
        Node *temp = get_node(data);
        temp->next = it->next;
        it->next = temp;
        len++;
    }
    void print_list()
    {
        Node *it = head;
        while (it != nullptr)
        {
            cout << it->data << "->";
            it = it->next;
        }
        cout << "Null\n";
    }
    void deleteAtIndex(int index)
    {
        if (index >= len || index < 0)
        {
            throw out_of_range("Index out of range!");
        }
        Node *it = head;
        int i = 0;
        while (it != nullptr && i < index - 1)
        {
            it = it->next;
            i++;
        }
        if (index == 0)
        {
            // Node* temp = head;
            head = head->next;
            // delete temp;
        }
        else
        {
            // Node* temp = it->next;
            it->next = it->next->next;
            // delete temp;
        }
        len--;
    }
    bool empty()
    {
        return len == 0;
    }
};

int main()
{
    using linkList = SinglyLinkedList;
    linkList ll;
    ll.push_front(5);
    ll.push_front(4);
    ll.push_front(3);
    ll.push_front(2);
    ll.push_front(1);
    ll.push_back(6);
    ll.push_back(7);
    ll.push_back(8);
    ll.push_back(9);
    ll.insert(5, 7);
    ll.print_list();
    for (int i = 0; i < 5; i++)
    {
        ll.deleteAtIndex(1);
    }
    ll.print_list();
    try
    {
        cout << ll.get(8) << endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
    }

    return 0;
}