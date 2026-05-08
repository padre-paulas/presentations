#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class Stack {
private:
    Node* top;

public:
    Stack() {
        top = nullptr;
    }

    void push(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    Node* getTop() const {
        return top;
    }
};

bool areStacksEqual(Stack& s1, Stack& s2) {
    Node* temp1 = s1.getTop();
    Node* temp2 = s2.getTop();

    while (temp1 && temp2) {
        if (temp1->data != temp2->data) {
            return false;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return (temp1 == nullptr && temp2 == nullptr);
}
int main() {
    Stack s1, s2;

    s1.push(10);
    s1.push(20);
    s1.push(30);

    s2.push(10);
    s2.push(20);
    s2.push(302);

    if (areStacksEqual(s1, s2))
        cout << "\nStacks are equal\n\n";
    else
        cout << "\nStacks are NOT equal\n\n";

    return 0;
}

