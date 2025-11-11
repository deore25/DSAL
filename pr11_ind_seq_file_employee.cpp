#include <iostream> 
#include <fstream>  
#include <vector>   
#include <algorithm> 
#include <iomanip>   
using namespace std;


struct Employee {
    int id;          
    string name;    
    string designation; 
    double salary;   
};


struct IndexEntry {
    int id;   
    long pos; 
};


vector<IndexEntry> loadIndex() {
    vector<IndexEntry> index;        
    ifstream idxFile("index.txt"); 
    IndexEntry entry;              
    
    while (idxFile >> entry.id >> entry.pos) {
        index.push_back(entry); 
    }
    idxFile.close(); 
    return index;   
}


void saveIndex(const vector<IndexEntry>& index) {
    ofstream idxFile("index.txt"); 
   
    for (auto& entry : index) {
        idxFile << entry.id << " " << entry.pos << "\n"; 
    }
    idxFile.close(); 
}


void addEmployee() {
    ofstream dataFile("data.txt", ios::app); 
    fstream temp("data.txt", ios::in);      
    vector<IndexEntry> index = loadIndex(); 

    Employee emp;
    cout << "************Enter Employee Information************\n ";
    cout << "Enter Employee ID: ";
    cin >> emp.id;

    cout << "Enter Employee Name: ";
    cin >> emp.name;

    cout << "Enter Employee Designation: ";
    cin >> emp.designation;

    cout << "Enter Employee Salary: ";
    cin >> emp.salary;
 

    
    for (auto& entry : index) {
        if (entry.id == emp.id) {
            cout << "Employee already exists.\n";
            return; 
        }
    }

    long pos = dataFile.tellp(); 
    dataFile << emp.id << " " << emp.name << " " << emp.designation << " " << emp.salary << "\n"; 

    index.push_back({emp.id, pos}); 
    sort(index.begin(), index.end(), [](IndexEntry a, IndexEntry b) { return a.id < b.id; }); 

    saveIndex(index); 
    cout << "Employee added.\n";
    dataFile.close(); 
}


void displayEmployee() {
    int searchId; 
    cout << "Enter Employee ID to display: ";
    cin >> searchId; 

    vector<IndexEntry> index = loadIndex();
    
    auto it = find_if(index.begin(), index.end(), [searchId](IndexEntry e) { return e.id == searchId; });

   
    if (it == index.end()) {
        cout << "Employee not found.\n";
        return; 
    }

    ifstream dataFile("data.txt"); 
    dataFile.seekg(it->pos);      

    Employee emp; 
    dataFile >> emp.id >> emp.name >> emp.designation >> emp.salary; 

    cout << "Employee Details:\n";
    cout << "ID: " << emp.id << "\nName: " << emp.name << "\nDesignation: " << emp.designation << "\nSalary: " << emp.salary << "\n";
    dataFile.close(); 
}


void deleteEmployee() {
    int delId; 
    cout << "Enter Employee ID to delete: ";
    cin >> delId; 

    vector<IndexEntry> index = loadIndex(); 
   
    auto it = find_if(index.begin(), index.end(), [delId](IndexEntry e) { return e.id == delId; });

  
    if (it == index.end()) {
        cout << "Employee not found.\n";
        return; 
    }

    ifstream dataFile("data.txt");    
    ofstream tempFile("temp.txt");    
    Employee emp;                     
    long pos;                         
   
    while (dataFile >> emp.id >> emp.name >> emp.designation >> emp.salary) {
       
        if (emp.id != delId) {
            tempFile << emp.id << " " << emp.name << " " << emp.designation << " " << emp.salary << "\n";
        }
    }

    dataFile.close(); 
    tempFile.close(); 

    remove("data.txt");    
    rename("temp.txt", "data.txt"); 

    
    ofstream newIndex("index.txt"); 
    ifstream newData("data.txt"); 
    index.clear();               
    pos = 0;                        
    
    while (newData >> emp.id >> emp.name >> emp.designation >> emp.salary) {
        index.push_back({emp.id, pos}); 
        pos = newData.tellg();        
    }
    newData.close();  
    saveIndex(index);  
    cout << "Employee deleted.\n";
}


void menu() {
    int choice; 
    do {
        cout << "\n1. Add Employee\n2. Delete Employee\n3. Display Employee\n4. Exit\nChoice: ";
        cin >> choice; 

       
        switch (choice) {
            case 1: addEmployee(); break;    
            case 2: deleteEmployee(); break; 
            case 3: displayEmployee(); break; 
            case 4: cout << "Exiting...\n"; break; 
            default: cout << "Invalid choice\n"; 
        }
    } while (choice != 4); 
}

int main() {
    menu(); 
    return 0; 
}