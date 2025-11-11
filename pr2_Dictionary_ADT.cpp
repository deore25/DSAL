#include<iostream>
#include<string>
using namespace std;


const int TABLE_SIZE = 10;


struct Entry {
    string key;  
    string value; 
    Entry* next;  
};  


class Dictionary {
    Entry* table[TABLE_SIZE]; 

    
    int hashFunction(string key) {
        int sum = 0;
        
        for (char ch : key) {
            
            sum += ch;
        }
        
        return sum % TABLE_SIZE;
    }   

public:
   
    Dictionary() {
        
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

   
    void insert(string key, string value) {
       
        int index = hashFunction(key);
        
        Entry* head = table[index];

        
        while (head) {
            
            if (head->key == key) {
                cout << "Key already exists. Updating value.\n";
                
                head->value = value;
                return; 
            }
           
            head = head->next;
        }

       
        Entry* newEntry = new Entry{key, value, table[index]};
        
        table[index] = newEntry;
    }

    
    void find(string key) {
        
        int index = hashFunction(key);
        
        Entry* head = table[index];

        
        while (head) {
           
            if (head->key == key) {
                
                cout << "Found: " << key << " => " << head->value << endl;
                return; 
            }
            
            head = head->next;
        }
       
        cout << "Key not found.\n";
    }

    
    void remove(string key) {
        
        int index = hashFunction(key);

        Entry* head = table[index];
        
        Entry* prev = nullptr;

        
        while (head) {
            
            if (head->key == key) {
                
                if (prev) {
                    
                    prev->next = head->next;
                } else {
                    
                    table[index] = head->next;
                }
                
                delete head;
                cout << "Entry deleted.\n";
                return; 
            }
            
            prev = head;
            
            head = head->next;
        }
        
        cout << "Key not found to delete.\n";
    }

    
    void display() {
        
        for (int i = 0; i < TABLE_SIZE; i++) {
            
            cout << "[" << i << "]: ";
            
            Entry* head = table[i];
           
            while (head) {
                
                cout << "(" << head->key << " => " << head->value << ") -> ";
                
                head = head->next;
            }
            
            cout << "NULL\n";
        }
    }
};

int main() {
    
    Dictionary dict;
    int choice;
    string key, value;

    
    do {
        cout << "\nDictionary Menu:\n";
        cout << "1. Insert\n2. Find\n3. Delete\n4. Display\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        
        switch (choice) {
            case 1: 
                cout << "Enter key: ";
                cin >> key;
                cout << "Enter value: ";
                cin >> value;
                dict.insert(key, value);
                break;

            case 2: 
                cout << "Enter key to search: ";
                cin >> key;
                dict.find(key);
                break;

            case 3: 
                cout << "Enter key to delete: ";
                cin >> key;
                dict.remove(key);
                break;

            case 4: 
                dict.display();
                break;

            case 5: 
                cout << "Exiting...\n";
                break;

            default: 
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5); 

    return 0;
}
