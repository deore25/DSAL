
//Student Information using sequential file

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Student {
    int rollNumber;
    string name;
    string division;
    string address;

    // Function to display student information
    void displayStudent() {
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Division: " << division << endl;
        cout << "Address: " << address << endl;
    }
};

// Function to add a new student record
void addStudent(const string& filename) {
    ofstream outFile(filename, ios::app); // Open file in append mode
    if (!outFile) {
        cerr << "Unable to open file for writing." << endl;
        return;
    }

    Student student;
    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cin.ignore(); // to ignore the leftover newline character
    cout << "Enter Name: ";
    getline(cin, student.name);
    cout << "Enter Division: ";
    getline(cin, student.division);
    cout << "Enter Address: ";
    getline(cin, student.address);

    // Write the student record to the file
    outFile << student.rollNumber << endl;
    outFile << student.name << endl;
    outFile << student.division << endl;
    outFile << student.address << endl;

    outFile.close();
    cout << "Student added successfully!" << endl;
}

// Function to delete a student record by roll number
void deleteStudent(const string& filename) {
    int rollNumber;
    cout << "Enter the roll number of the student to delete: ";
    cin >> rollNumber;

    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Unable to open file for reading." << endl;
        return;
    }

    vector<Student> students;
    Student student;

    // Read all students from file
    while (inFile >> student.rollNumber) {
        inFile.ignore(); // Ignore the newline character
        getline(inFile, student.name);
        getline(inFile, student.division);
        getline(inFile, student.address);

        if (student.rollNumber != rollNumber) {
            students.push_back(student);
        }
    }

    inFile.close();

    if (students.size() == 0) {
        cout << "Student with roll number " << rollNumber << " not found." << endl;
        return;
    }

    // Re-write the file with the remaining students
    ofstream outFile(filename);
    for (const auto& s : students) {
        outFile << s.rollNumber << endl;
        outFile << s.name << endl;
        outFile << s.division << endl;
        outFile << s.address << endl;
    }

    outFile.close();
    cout << "Student deleted successfully!" << endl;
}

// Function to display a student record by roll number
void displayStudent(const string& filename) {
    int rollNumber;
    cout << "Enter the roll number of the student to display: ";
    cin >> rollNumber;

    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Unable to open file for reading." << endl;
        return;
    }

    bool found = false;
    Student student;

    // Read all students from file and search for the student with the given roll number
    while (inFile >> student.rollNumber) {
        inFile.ignore(); // Ignore the newline character
        getline(inFile, student.name);
        getline(inFile, student.division);
        getline(inFile, student.address);

        if (student.rollNumber == rollNumber) {
            student.displayStudent();
            found = true;
            break;
        }
    }

    inFile.close();

    if (!found) {
        cout << "Student with roll number " << rollNumber << " not found." << endl;
    }
}

int main() {
    string filename = "students.txt"; // File to store student records
    int choice;

    do {
        cout << "\n--- Student Information System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Display Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(filename);
                break;
            case 2:
                deleteStudent(filename);
                break;
            case 3:
                displayStudent(filename);
                break;
            case 4:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
