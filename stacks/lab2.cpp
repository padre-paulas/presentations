#include <iostream>
#include <string>

struct Student {
    std::string surname;
    double averageGrade;
};

struct Node {
    Student data; 
    Node* next;   
 
    Node(Student s) : data(s), next(nullptr) {}
};

class Stack {
private:
    Node* topNode; 

public:
    Stack() : topNode(nullptr) {}
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    void push(const Student& student) {
        Node* newNode = new Node(student); 
        newNode->next = topNode;        
        topNode = newNode;                
        std::cout << "\nДодано: " << student.surname 
        << " (Бал: " << student.averageGrade << ")\n";
    }

    void pop() {
        if (isEmpty()) {
            std::cout << "Стек порожній! Видалення неможливе.\n";
            return;
        }
        Node* temp = topNode;        
        topNode = topNode->next;     
        delete temp;                 
    }

    void display() const {
        if (isEmpty()) {
            std::cout << "Стек порожній!\n";
            return;
        }
        
        std::cout << "\n--- Вміст стеку (від вершини до дна) ---\n";
        Node* current = topNode;
        while (current != nullptr) {
            std::cout << "Прізвище: " 
                << current->data.surname 
                << " | Середній бал: " 
                << current->data.averageGrade << "\n";
            current = current->next;
        }
        std::cout << "----------------------------------------\n\n";
    }
};

int main() {
    Stack studentStack;

    studentStack.push({"Коваленко", 4.5});
    studentStack.push({"Шевченко", 5.0});
    studentStack.push({"Бойко", 3.8});

    studentStack.display();

    std::cout << "--- Додаємо нового студента ---\n";
    studentStack.push({"Мельник", 4.9});

    studentStack.display();

    return 0; 
}

