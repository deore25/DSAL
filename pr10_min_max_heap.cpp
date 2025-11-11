#include <iostream>
#include <queue>   
#include <vector>  
#include <string>  
using namespace std;


struct Student {
    string name;
    int marks;

   
    Student(string n, int m) {
        name = n;
        marks = m;
    }
};


struct CompareMin {
    
    bool operator()(Student a, Student b) {
        return a.marks > b.marks; 
    }
};


struct CompareMax {
    
    bool operator()(Student a, Student b) {
        return a.marks < b.marks; 
    }
};

int main() {
    
    priority_queue<Student, vector<Student>, CompareMax> maxHeap;
   
    priority_queue<Student, vector<Student>, CompareMin> minHeap;

    int choice;
    string name;
    int marks;

    do {
        cout << "\n--- Student Info Menu ---\n";
        cout << "1. Insert student\n";
        cout << "2. Show student with MAX marks\n";
        cout << "3. Show student with MIN marks\n";
        cout << "4. Delete student with MAX marks\n";
        cout << "5. Delete student with MIN marks\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: 
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter marks: ";
            cin >> marks;
            
            maxHeap.push(Student(name, marks));
            minHeap.push(Student(name, marks));
            cout << "Student added!\n";
            break;

        case 2: 
            if (!maxHeap.empty()) {
                Student top = maxHeap.top(); 
                cout << "Student with MAX marks: " << top.name << " - " << top.marks << endl;
            } else {
                cout << "No students available.\n";
            }
            break;

        case 3: 
            if (!minHeap.empty()) {
                Student top = minHeap.top();
                cout << "Student with MIN marks: " << top.name << " - " << top.marks << endl;
            } else {
                cout << "No students available.\n";
            }
            break;

        case 4: 
            if (!maxHeap.empty()) {
                Student top = maxHeap.top(); 
                maxHeap.pop();                
                cout << "Deleted student with MAX marks: " << top.name << endl;
                
            } else {
                cout << "No students to delete.\n";
            }
            break;

        case 5: 
            if (!minHeap.empty()) {
                Student top = minHeap.top(); 
                minHeap.pop();                
                cout << "Deleted student with MIN marks: " << top.name << endl;
               
            } else {
                cout << "No students to delete.\n";
            }
            break;

        case 6: 
            cout << "Exiting...\n";
            break;

        default: 
            cout << "Invalid choice!\n";
        }

    } while (choice != 6); 

    return 0;
}