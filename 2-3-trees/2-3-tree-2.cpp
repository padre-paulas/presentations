#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int keys[2];
    int keyCount;
    Node *ch[3];
    Node(int k = 0) : keyCount(1)
    {
        keys[0] = k;
        keys[1] = 0;
        ch[0] = ch[1] = ch[2] = nullptr;
    }
};

bool isLeaf(Node *n) { return n->ch[0] == nullptr; }
Node *root = nullptr;

Node *ins(Node *n, int key, int &up)
{
    if (isLeaf(n))
    {
        if (n->keyCount == 1)
        {
            if (key < n->keys[0])
            {
                n->keys[1] = n->keys[0];
                n->keys[0] = key;
            }
            else
                n->keys[1] = key;
            n->keyCount = 2;
            return nullptr;
        }
        int a, b, c;
        if (key < n->keys[0])
        {
            a = key;
            b = n->keys[0];
            c = n->keys[1];
        }
        else if (key < n->keys[1])
        {
            a = n->keys[0];
            b = key;
            c = n->keys[1];
        }
        else
        {
            a = n->keys[0];
            b = n->keys[1];
            c = key;
        }
        n->keys[0] = a;
        n->keys[1] = 0;
        n->keyCount = 1;
        Node *r = new Node(c);
        up = b;
        return r;
    }
    int childUp;
    Node *newChild;
    if (key < n->keys[0])
    {
        newChild = ins(n->ch[0], key, childUp);
        if (!newChild)
            return nullptr;

        if (n->keyCount == 1)
        {
            n->keys[1] = n->keys[0];
            n->keys[0] = childUp;
            n->keyCount = 2;
            n->ch[2] = n->ch[1];
            n->ch[1] = newChild;
            return nullptr;
        }
        up = n->keys[0];
        Node *r = new Node(n->keys[1]);
        r->ch[0] = n->ch[1];
        r->ch[1] = n->ch[2];
        n->keys[0] = childUp;
        n->keys[1] = 0;
        n->keyCount = 1;
        n->ch[1] = newChild;
        n->ch[2] = nullptr;
        return r;
    }
    else if (n->keyCount == 1 || key < n->keys[1])
    {
        newChild = ins(n->ch[1], key, childUp);
        if (!newChild)
            return nullptr;
        if (n->keyCount == 1)
        {
            n->keys[1] = childUp;
            n->keyCount = 2;
            n->ch[2] = newChild;
            return nullptr;
        }
        up = childUp;
        Node *r = new Node(n->keys[1]);
        r->ch[0] = newChild;
        r->ch[1] = n->ch[2];
        n->keys[1] = 0;
        n->keyCount = 1;
        n->ch[2] = nullptr;
        return r;
    }
    else
    {
        newChild = ins(n->ch[2], key, childUp);
        if (!newChild)
            return nullptr;
        up = n->keys[1];
        Node *r = new Node(childUp);
        r->ch[0] = n->ch[2];
        r->ch[1] = newChild;
        n->keys[1] = 0;
        n->keyCount = 1;
        n->ch[2] = nullptr;
        return r;
    }
}

void insert(int key)
{
    if (!root)
    {
        root = new Node(key);
        return;
    }
    int up;
    Node *r = ins(root, key, up);
    if (r)
    {
        Node *nr = new Node(up);
        nr->ch[0] = root;
        nr->ch[1] = r;
        root = nr;
    }
}

bool fixUnderflow(Node *par, int ci);

bool removeFromLeaf(Node *n, int key)
{
    if (n->keyCount == 2)
    {
        if (n->keys[0] == key)
        {
            n->keys[0] = n->keys[1];
        }
        n->keys[1] = 0;
        n->keyCount = 1;
        return false;
    }
    n->keyCount = 0;
    return true;
}

bool fixUnderflow(Node *par, int ci)
{
    int total = par->keyCount + 1;

    int li = ci - 1;
    int ri = ci + 1;

    if (ri < total && par->ch[ri] && par->ch[ri]->keyCount == 2)
    {
        Node *child = par->ch[ci];
        Node *right = par->ch[ri];
        int sepIdx = ci;

        child->keys[0] = par->keys[sepIdx];
        child->keyCount = 1;
        if (!isLeaf(child))
        {
            child->ch[1] = right->ch[0];
        }
        par->keys[sepIdx] = right->keys[0];
        right->keys[0] = right->keys[1];
        right->keys[1] = 0;
        right->keyCount = 1;
        if (!isLeaf(right))
        {
            right->ch[0] = right->ch[1];
            right->ch[1] = right->ch[2];
            right->ch[2] = nullptr;
        }
        return false;
    }

    if (li >= 0 && par->ch[li] && par->ch[li]->keyCount == 2)
    {
        Node *child = par->ch[ci];
        Node *left = par->ch[li];
        int sepIdx = li;

        child->keys[1] = child->keys[0];
        child->keys[0] = par->keys[sepIdx];
        child->keyCount = 1;
        if (!isLeaf(child))
        {
            child->ch[1] = child->ch[0];
            child->ch[0] = left->ch[left->keyCount];
        }
        par->keys[sepIdx] = left->keys[left->keyCount - 1];
        left->keys[left->keyCount - 1] = 0;
        left->keyCount--;
        if (!isLeaf(left))
        {
            left->ch[left->keyCount + 1] = nullptr;
        }
        return false;
    }

    if (li >= 0 && par->ch[li])
    {
        Node *left = par->ch[li];
        Node *child = par->ch[ci];
        int sepIdx = li;

        left->keys[left->keyCount] = par->keys[sepIdx];
        if (!isLeaf(left))
        {
            left->ch[left->keyCount + 1] = child->ch[0];
        }
        left->keyCount++;

        for (int i = sepIdx; i < par->keyCount - 1; i++)
            par->keys[i] = par->keys[i + 1];
        par->keys[par->keyCount - 1] = 0;
        for (int i = ci; i < par->keyCount; i++)
            par->ch[i] = par->ch[i + 1];
        par->ch[par->keyCount] = nullptr;
        par->keyCount--;

        delete child;
        return par->keyCount == 0;
    }
    else
    {
        Node *child = par->ch[ci];
        Node *right = par->ch[ri];
        int sepIdx = ci;

        child->keys[0] = par->keys[sepIdx];
        if (!isLeaf(child))
        {
            child->ch[1] = right->ch[0];
        }
        child->keyCount = 1;

        for (int i = sepIdx; i < par->keyCount - 1; i++)
            par->keys[i] = par->keys[i + 1];
        par->keys[par->keyCount - 1] = 0;
        for (int i = ri; i < par->keyCount; i++)
            par->ch[i] = par->ch[i + 1];
        par->ch[par->keyCount] = nullptr;
        par->keyCount--;

        delete right;
        return par->keyCount == 0;
    }
}

bool del(Node *n, int key)
{
    if (isLeaf(n))
    {
        return removeFromLeaf(n, key);
    }

    for (int i = 0; i < n->keyCount; i++)
    {
        if (n->keys[i] == key)
        {
            Node *succ = n->ch[i + 1];
            while (!isLeaf(succ))
                succ = succ->ch[0];
            n->keys[i] = succ->keys[0];
            bool underflow = del(n->ch[i + 1], succ->keys[0]);
            if (underflow)
                return fixUnderflow(n, i + 1);
            return false;
        }
    }

    int ci;
    if (key < n->keys[0])
        ci = 0;
    else if (n->keyCount == 1 || key < n->keys[1])
        ci = 1;
    else
        ci = 2;

    bool underflow = del(n->ch[ci], key);
    if (underflow)
        return fixUnderflow(n, ci);
    return false;
}

void remove(int key)
{
    if (!root)
        return;
    bool underflow = del(root, key);
    if (underflow)
    {
        Node *oldRoot = root;
        root = root->ch[0] ? root->ch[0] : nullptr;
        delete oldRoot;
    }
}

void print(Node *n, string prefix, bool last)
{
    if (!n)
        return;
    cout << prefix << (last ? "└── " : "├── ");
    if (n->keyCount == 2)
        cout << "[" << n->keys[0] << ", " << n->keys[1] << "]\n";
    else
        cout << "[" << n->keys[0] << "]\n";
    string np = prefix + (last ? "    " : "│   ");
    int cnt = 0;
    for (int i = 0; i < 3; i++)
        if (n->ch[i])
            cnt++;
    int seen = 0;
    for (int i = 0; i < 3; i++)
        if (n->ch[i])
            print(n->ch[i], np, ++seen == cnt);
}

int main()
{
    int elems[] = {13, 19, 20, 34, 29, 100, 130, 8, 15, 4, 6, 9};
    for (int x : elems)
        insert(x);

    cout << "Initial tree:\n";
    print(root, "", true);

    int toDelete[] = {8, 100, 13, 34};
    for (int x : toDelete)
    {
        remove(x);
        cout << "\nAfter deleting " << x << ":\n";
        print(root, "", true);
    }

    return 0;
}