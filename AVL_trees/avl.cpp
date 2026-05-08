#include <iostream>
using namespace std;

struct Node {
  char data;
  Node *left;
  Node *right;
  int height;

  Node(char value) {
    data = value;
    left = right = nullptr;
    height = 1;
  }
};

int getHeight(Node *node) {
  return node ? node->height : 0;
}

int getBalance(Node *node) {
  return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void updateHeight(Node *node) {
  node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

Node *rightRotate(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  updateHeight(y);
  updateHeight(x);

  return x;
}

Node *leftRotate(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  updateHeight(x);
  updateHeight(y);

  return y;
}

Node *insert(Node *node, char key) {
  if (!node)
    return new Node(key);

  if (key < node->data)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);

  updateHeight(node);
  int balance = getBalance(node);

  if (balance > 1 && key < node->left->data)
    return rightRotate(node);

  if (balance < -1 && key > node->right->data)
    return leftRotate(node);

  if (balance > 1 && key > node->left->data) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && key < node->right->data) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

bool isDigit(char c) {
  return (c >= '0' && c <= '9');
}

void calculateDigits(Node *root, int &sum, int &count) {
  if (!root)
    return;

  if (isDigit(root->data)) {
    sum += (root->data - '0');
    count++;
  }

  calculateDigits(root->left, sum, count);
  calculateDigits(root->right, sum, count);
}

double findAverageDigits(Node *root) {
  int sum = 0, count = 0;

  calculateDigits(root, sum, count);

  if (count == 0)
    throw "Немає цифр у дереві!";

  return (double)sum / count;
}

void printTree(Node *root, int space = 0, int levelSpace = 5) {
  if (!root)
    return;
  printTree(root->right, space + levelSpace, levelSpace);
  for (int i = 0; i < space; i++)
    cout << " ";
  cout << root->data << "\n";
  printTree(root->left, space + levelSpace, levelSpace);
}

int main() {
  Node *root = nullptr;

  char arr[] = {'A', '3', 'B', '7', 'C', '1', 'D'};
  int n = sizeof(arr) / sizeof(arr[0]);

  for (int i = 0; i < n; i++) {
    root = insert(root, arr[i]);
  }

  cout << "Element Tree: \n";
  printTree(root);

  double avg = findAverageDigits(root);
  cout << "\nArithmetic mean of digits: " << avg << endl;
  return 0;
}

