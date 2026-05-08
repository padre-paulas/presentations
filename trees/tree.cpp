#include <iostream>
#include <string>

using namespace std;

void demo();

struct Person {
  string name;
  Person *father;
  Person *mother;

  Person(string n) : name(n), father(nullptr), mother(nullptr) {}
};

void printTree(Person *root, int space = 0, int count = 10) {
  if (root == nullptr)
    return;
  space += count;

  printTree(root->father, space);
  cout << endl;
  for (int i = count; i < space; i++)
    cout << " ";
  cout << "-> " << root->name << "\n";

  printTree(root->mother, space);
}

int main() {

  demo();

  return 0;
}

void demo() {
  string name;

  cout << "Введіть ваше ім'я: ";
  cin >> name;
  Person *person = new Person(name);

  cout << "Введіть ім'я матері: ";
  cin >> name;
  Person *mom = new Person(name);

  cout << "Введіть ім'я батька: ";
  cin >> name;
  Person *dad = new Person(name);

  cout << "Введіть ім'я діда по батькові: ";
  cin >> name;
  Person *g_dad_f = new Person(name);

  cout << "Введіть ім'я баби по батькові: ";
  cin >> name;
  Person *g_mom_f = new Person(name);

  cout << "Введіть ім'я діда по матері: ";
  cin >> name;
  Person *g_dad_m = new Person(name);

  cout << "Введіть ім'я баби по матері: ";
  cin >> name;
  Person *g_mom_m = new Person(name);

  person->mother = mom;
  person->father = dad;
  dad->father = g_dad_f;
  dad->mother = g_mom_f;
  mom->father = g_dad_m;
  mom->mother = g_mom_m;

  cout << "\n=== ВАШЕ ГЕНЕАЛОГІЧНЕ ДЕРЕВО ===\n\n";
  printTree(person);
  cout << "\n===============================\n\n";
}



