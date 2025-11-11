#include<iostream>
using namespace std;


struct Node {
    long long phone; 
    Node* next;    
};


class TelephoneBook {
    Node* table[10]; 

public:
    
    TelephoneBook() {
        
        for (int i = 0; i < 10; i++) {
            table[i] = nullptr;
        }
    }

    
    int hashFunction(long long number) {
        
        return number % 10;
    }

    
    void insert(long long number) {
        
        int index = hashFunction(number);
        
        Node* newNode = new Node{number, nullptr};

        
        if (!table[index]) {
            
            table[index] = newNode;
        } else {
            
            Node* temp = table[index];
            while (temp->next) {
                temp = temp->next;
            }
            
            temp->next = newNode;
        }
    }

    
    void display() {
        
        for (int i = 0; i < 10; i++) {
           
            cout << "a[" << i << "]:";
            
            Node* temp = table[i];
            
            while (temp) {
                                      
                cout << " ->" << temp->phone;
                
                temp = temp->next;
            }
            
            cout << endl;
        }
    }

    
    int search(long long number) {
        
        int index = hashFunction(number);
        
        Node* temp = table[index];

        
        while (temp) {
            
            if (temp->phone == number) {
                
                cout << "Element found at: a[" << index << "]\n";
                
                return index;
            }
            
            temp = temp->next;
        }
        
        return -1;
    }


    void remove(long long number) {
    
        int index = hashFunction(number);
        
        Node* temp = table[index];
        
        Node* prev = nullptr;           

        
        while (temp) {
            
            if (temp->phone == number) {
                
                if (prev) {
                
                    prev->next = temp->next;
                } else {
                    
                    table[index] = temp->next;
                }
                
                delete temp;
                
                cout << "Phone number deleted.\n";
                
                return;
            }
            
            prev = temp;
            
            temp = temp->next;
        }
        
        cout << "Phone number not found.\n";
    }
};

int main() {
    
    TelephoneBook tb;
    int choice;
    long long number;

    
    do {
        cout << "\nTelephone Book Menu:\n";
        cout << "1.Insert\n2.Display\n3.Search\n4.Delete\n5.Exit\n";
        cin >> choice;

        
        switch (choice) {
            case 1: 
                cout << "Enter phone number to insert: ";
                cin >> number;
                tb.insert(number);
                break;

            case 2:
                tb.display();
                break;

            case 3: 
                cout << "Enter phone number to search: ";
                cin >> number;
                if (tb.search(number) == -1) {
                    cout << "Phone number not found.\n";
                }
                break;

            case 4: 
                cout << "Enter phone number to delete: ";
                cin >> number;
                tb.remove(number);
                break;

            case 5: 
                break;

            default: 
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5); 

    return 0;
}