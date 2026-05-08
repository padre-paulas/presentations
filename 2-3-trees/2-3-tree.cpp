#include <iostream>
#include <string>
using namespace std;

struct Node {
    int keys[2];
    int keyCount;
    Node* ch[3];
    Node(int k = 0) : keyCount(1) {
        keys[0] = k; keys[1] = 0;
        ch[0] = ch[1] = ch[2] = nullptr;
    }
};

bool isLeaf(Node* n) { return n->ch[0] == nullptr; }

Node* root = nullptr;

// Returns: if overflow happened, stores promoted key in `up` and returns new right sibling
// Otherwise returns nullptr
Node* ins(Node* n, int key, int& up) {
    if (isLeaf(n)) {
        if (n->keyCount == 1) {
            if (key < n->keys[0]) { n->keys[1] = n->keys[0]; n->keys[0] = key; }
            else n->keys[1] = key;
            n->keyCount = 2;
            return nullptr;
        }
        // 3-node leaf: split
        int a, b, c;
        if      (key < n->keys[0]) { a=key; b=n->keys[0]; c=n->keys[1]; }
        else if (key < n->keys[1]) { a=n->keys[0]; b=key; c=n->keys[1]; }
        else                       { a=n->keys[0]; b=n->keys[1]; c=key; }
        n->keys[0] = a; n->keys[1] = 0; n->keyCount = 1;
        Node* r = new Node(c);
        up = b;
        return r;
    }

    int childUp;
    Node* newChild;

    if (key < n->keys[0]) {
        newChild = ins(n->ch[0], key, childUp);
        if (!newChild) return nullptr;
        // overflow from ch[0]
        if (n->keyCount == 1) {
            // absorb: shift right
            n->keys[1] = n->keys[0]; n->keys[0] = childUp; n->keyCount = 2;
            n->ch[2] = n->ch[1];
            n->ch[1] = newChild;
            return nullptr;
        }
        // n is 3-node, must split
        // keys: [n->keys[0], n->keys[1]], new key childUp < n->keys[0]
        // children: ch[0], ch[1], ch[2]; plus newChild (right of childUp)
        // sorted keys: childUp, n->keys[0], n->keys[1]
        // children:  n->ch[0],  newChild,  n->ch[1],  n->ch[2]
        up = n->keys[0];
        Node* r = new Node(n->keys[1]);
        r->ch[0] = n->ch[1]; r->ch[1] = n->ch[2];
        n->keys[0] = childUp; n->keys[1] = 0; n->keyCount = 1;
        n->ch[1] = newChild; n->ch[2] = nullptr;
        return r;
    } else if (n->keyCount == 1 || key < n->keys[1]) {
        newChild = ins(n->ch[1], key, childUp);
        if (!newChild) return nullptr;
        if (n->keyCount == 1) {
            n->keys[1] = childUp; n->keyCount = 2;
            n->ch[2] = newChild;
            return nullptr;
        }
        // overflow from ch[1], childUp is between keys[0] and keys[1]
        // keys: n->keys[0], childUp, n->keys[1]
        // children: ch[0], n->ch[1], newChild, ch[2]
        up = childUp;
        Node* r = new Node(n->keys[1]);
        r->ch[0] = newChild; r->ch[1] = n->ch[2];
        n->keys[1] = 0; n->keyCount = 1;
        n->ch[2] = nullptr;
        return r;
    } else {
        newChild = ins(n->ch[2], key, childUp);
        if (!newChild) return nullptr;
        // overflow from ch[2]
        // keys: n->keys[0], n->keys[1], childUp
        // children: ch[0], ch[1], n->ch[2], newChild
        up = n->keys[1];
        Node* r = new Node(childUp);
        r->ch[0] = n->ch[2]; r->ch[1] = newChild;
        n->keys[1] = 0; n->keyCount = 1;
        n->ch[2] = nullptr;
        return r;
    }
}

void insert(int key) {
    if (!root) { root = new Node(key); return; }
    int up;
    Node* r = ins(root, key, up);
    if (r) {
        Node* newRoot = new Node(up);
        newRoot->ch[0] = root;
        newRoot->ch[1] = r;
        root = newRoot;
    }
}

void print(Node* n, string prefix, bool last) {
    if (!n) return;
    cout << prefix << (last ? "└── " : "├── ");
    if (n->keyCount == 2) cout << "[" << n->keys[0] << ", " << n->keys[1] << "]\n";
    else                  cout << "[" << n->keys[0] << "]\n";
    string np = prefix + (last ? "    " : "│   ");
    int cnt = 0;
    for (int i = 0; i < 3; i++) if (n->ch[i]) cnt++;
    int seen = 0;
    for (int i = 0; i < 3; i++)
        if (n->ch[i]) print(n->ch[i], np, ++seen == cnt);
}

int main() {
    int elems[] = {13, 19, 20, 34, 29, 100, 130, 8, 15, 4, 6, 9};
    for (int x : elems) insert(x);
    cout << "2-3 Tree:\n";
    print(root, "", true);
    return 0;
}