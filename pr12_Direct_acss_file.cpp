#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;

const char FILE_NAME[] = "direct_access.txt";  

struct Record {
    char name[30];

    Record() {
        strcpy(name, "");
    }
};

void insertRecord() {
    Record rec;
    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(rec.name, 30);

   
    fstream file(FILE_NAME, ios::in | ios::out | ios::app);

    if (!file) {
       
        file.open(FILE_NAME, ios::out);
        file.close();
        file.open(FILE_NAME, ios::in | ios::out | ios::app);
    }

    
    file << rec.name << endl;
    file.close();

    cout << "Record inserted successfully.\n";
}

void deleteRecord() {
    int position;
    cout << "Enter record position to delete (starting from 1): ";
    cin >> position;

    
    fstream file(FILE_NAME, ios::in | ios::out);
    if (!file) {
        cout << "File not found.\n";
        return;
    }

    vector<string> records;
    string line;

    
    while (getline(file, line)) {
        records.push_back(line);
    }
    file.close();

   
    if (position < 1 || position > records.size()) {
        cout << "Invalid position.\n";
        return;
    }

    
    records.erase(records.begin() + (position - 1));
    cout << "Record deleted successfully.\n";

   
    file.open(FILE_NAME, ios::out | ios::trunc);
    for (const auto& record : records) {
        file << record << endl;
    }
    file.close();
}

void displayRecords() {
    ifstream file(FILE_NAME);
    if (!file) {
        cout << "File not found.\n";
        return;
    }

    string line;
    int index = 1;
    cout << "\n--- Records ---\n";
    while (getline(file, line)) {
        cout << index << ". " << line << endl;
        index++;
    }
    file.close();
}

int main() {
    int choice;

    do {
        cout << "\n--- Direct Access File Menu ---\n";
        cout << "1. Insert Record\n";
        cout << "2. Delete Record\n";
        cout << "3. Display Records\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: insertRecord(); break;
            case 2: deleteRecord(); break;
            case 3: displayRecords(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}
