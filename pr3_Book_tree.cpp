#include <iostream>
#include <vector>
#include <string> 
using namespace std;


class Node {
public:
    string name;        
    vector<Node*> children;
    
    Node(string n) {
        name = n;
    }

    
    void addChild(Node* child) {
        children.push_back(child);
    }

    
    void print(int level = 0) {
        
        for (int i = 0; i < level; i++) cout << "  ";   
        
        cout << name << endl;
        
        for (Node* child : children)
            
            child->print(level + 1);
    }
};

int main() {
   
    Node* book = new Node("Book");
     
    

    int numChapters;
    cout << "Enter number of chapters: ";
    cin >> numChapters;

    
    for (int i = 0; i < numChapters; i++) {
        string chName;
        cout << "Enter name of chapter " << i + 1 << ": ";
        cin.ignore(); 
        getline(cin, chName); 
        Node* chapter = new Node(chName); 

        int numSections;
        cout << "Enter number of sections in " << chName << ": ";
        cin >> numSections;

       
        for (int j = 0; j < numSections; j++) {
            string secName;
            cout << "Enter name of section " << j + 1 << ": ";
            cin.ignore(); 
            getline(cin, secName); 
            Node* section = new Node(secName); 

            int numSubsections;
            cout << "Enter number of subsections in " << secName << ": ";
            cin >> numSubsections;

            
            for (int k = 0; k < numSubsections; k++) {
                string subsecName;
                cout << "Enter name of subsection " << k + 1 << ": ";
                cin.ignore(); 
                getline(cin, subsecName); 
                Node* subsection = new Node(subsecName); 
                section->addChild(subsection); 
            }

            chapter->addChild(section); 
        }

        book->addChild(chapter); 
    }

    cout << "\nBook Structure:\n";
    book->print(); 

    cout << "\nTime Complexity: O(n) where n is number of nodes\n";
    cout << "Space Complexity: O(h) for recursion stack, h = height of tree\n";
    return 0;
}