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

    ~Stack() {
        clear();
    }

    void push(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            cout << "ERROR: Stack is empty. Cannot delete element.\n";
            return;
        }

        Node* temp = top;
        cout << "Deleted element: " << temp->data << endl;
        top = top->next;
        delete temp;
    }
   
    void print() {
        if (isEmpty()) {
            cout << "Stack is empty.\n\n";
            return;
        }

        Node* current = top;
        cout << "Stack elements:\n";

        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;

        cout << "Top address: " << top << endl;
    }

    void clear() {
        while (!isEmpty()) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

int main() {
    Stack s;

    int N;
    cout << "\nEnter number of elements: ";
    cin >> N;

    if (N <= 0) {
        cout << "ERROR: Invalid number of elements.\n";
        return 0;
    }

    cout << "Enter numbers:\n";

    for (int i = 0; i < N; i++) {
        int value;
        cin >> value;
        s.push(value);
    }

    cout << "\nInitial stack:\n";
    s.print();

    cout << "\nDeleting one element...\n";
    s.pop();

    cout << "\nStack after deletion:\n";
    s.print();

    cout << "\nClearing stack...\n";
    s.clear();

    cout << "\nStack after clearing:\n";
    s.print();

    return 0;
}

