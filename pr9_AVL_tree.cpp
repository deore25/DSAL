#include <iostream>
#include <cstring> 
using namespace std;


struct Node {
    string key;     
    string meaning; 
    int height;    
    Node* left;  
    Node* right;  

    
    Node(string k, string m) {
        key = k;
        meaning = m;
        height = 1; 
        left = right = NULL;
    }
};


int height(Node* node) {
    return node ? node->height : 0;
}


int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}


int max(int a, int b) {
    return (a > b) ? a : b;
}


Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    
    x->right = y;
    y->left = T2;

   
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    
    return x;
}


Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

  
    y->left = x;
    x->right = T2;

    
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    
    return y;
}


Node* insert(Node* root, string key, string meaning) {
    
    if (!root)
        return new Node(key, meaning);

    if (key < root->key)
        root->left = insert(root->left, key, meaning);
    else if (key > root->key)
        root->right = insert(root->right, key, meaning);
    else {
        
        cout << "Keyword already exists. Updating meaning.\n";
        root->meaning = meaning;
        return root;
    }

    
    root->height = 1 + max(height(root->left), height(root->right));

    
    int balance = getBalance(root);

    
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

   
    return root;
}


Node* minValueNode(Node* node) {
    Node* current = node;
    
    while (current && current->left)
        current = current->left;
    return current;
}


Node* deleteNode(Node* root, string key) {
    
    if (!root) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            
            if (!temp) {
                temp = root;
                root = NULL;
            } else 
                *root = *temp; 
            delete temp;
        } else {
            
            Node* temp = minValueNode(root->right);
           
            root->key = temp->key;
            root->meaning = temp->meaning;
          
            root->right = deleteNode(root->right, temp->key);
        }
    }

   
    if (!root) return root;

   
    root->height = 1 + max(height(root->left), height(root->right));

    
    int balance = getBalance(root);

    
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


void search(Node* root, string key, int& comparisons) {
    while (root) {
        comparisons++;
        if (key == root->key) {
            cout << "Meaning: " << root->meaning << endl;
            return;
        } else if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    cout << "Keyword not found.\n";
}


void displayAsc(Node* root) {
    if (root) {
        displayAsc(root->left);
        cout << root->key << ": " << root->meaning << endl;
        displayAsc(root->right);
    }
}


void displayDesc(Node* root) {
    if (root) {
        displayDesc(root->right);
        cout << root->key << ": " << root->meaning << endl;
        displayDesc(root->left);
    }
}

int main() {
    Node* root = NULL;
    int choice;
    string key, meaning;

    do {
        cout << "\n--- Dictionary Menu ---\n";
        cout << "1. Add keyword\n2. Delete keyword\n3. Update meaning\n4. Display Ascending\n5. Display Descending\n6. Search & Show Comparisons\n7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> key;
                cout << "Enter meaning: ";
                cin.ignore(); 
                getline(cin, meaning);
                root = insert(root, key, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                cin >> key;
                root = deleteNode(root, key);
                break;
            case 3:
                cout << "Enter keyword to update: ";
                cin >> key;
                cout << "Enter new meaning: ";
                cin.ignore();
                getline(cin, meaning);
                root = insert(root, key, meaning); 
                break;
            case 4:
                cout << "\nAscending Order:\n";
                displayAsc(root);
                break;
            case 5:
                cout << "\nDescending Order:\n";
                displayDesc(root);
                break;
            case 6: {
                cout << "Enter keyword to search: ";
                cin >> key;
                int comps = 0;
                search(root, key, comps);
                cout << "Comparisons made: " << comps << endl;
                break;
            }
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 7);

    return 0;
}