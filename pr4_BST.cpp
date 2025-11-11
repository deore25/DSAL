#include <iostream>
using namespace std;


class Node {
public:
    int data;  
    Node* left;  
    Node* right; 

    
    Node(int value) {
        data = value;
        left = right = NULL;    
    }
};

Node* insert(Node* root, int value) {
   
    if (root == NULL)
        return new Node(value);

    
    if (value < root->data)
        root->left = insert(root->left, value);
    
    else if (value > root->data)
        root->right = insert(root->right, value);

    
    return root;
}

int height(Node* root) {
   
    if (root == NULL) return 0;
   
    int leftHeight = height(root->left);
   
    int rightHeight = height(root->right);
    
    return 1 + max(leftHeight, rightHeight);
}


int findMin(Node* root) {
    
    if (root == NULL) {
        cout << "Tree is empty.\n";
        return -1;
    }
    
    while (root->left != NULL)
        root = root->left;
    
    return root->data;
}


void mirror(Node* root) {
    
    if (root == NULL) return;
    
    swap(root->left, root->right);
   
    mirror(root->left);
    
    mirror(root->right);
}


bool search(Node* root, int key) {
    
    if (root == NULL) return false;
    
    if (key == root->data) return true;
    
    if (key < root->data)
        return search(root->left, key);
    
    else
        return search(root->right, key);
}


void inorder(Node* root) {
    
    if (root == NULL) return;
   
    inorder(root->left);
    
    cout << root->data << " ";
    
    inorder(root->right);
}

int main() {
    
    Node* root = NULL;
    int n, val;

    cout << "Enter number of nodes to insert initially: ";
    cin >> n;

    cout << "Enter values: ";
  
    for (int i = 0; i < n; i++) {
        cin >> val;
        root = insert(root, val);
    }

    int choice;
    
    do {
        cout << "\n\n--- BST Menu ---\n";
        cout << "1. Insert new node\n";
        cout << "2. Find longest path from root (height)\n";
        cout << "3. Find minimum value\n";
        cout << "4. Search a value\n";
        cout << "5. Mirror the tree\n";
        cout << "6. Display tree (Inorder)\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        
        switch (choice) {
        case 1: 
            cout << "Enter value to insert: ";
            cin >> val;
            root = insert(root, val);
            break;
        case 2: 
            cout << "Height of tree: " << height(root) << endl;
            break;
        case 3: 
            cout << "Minimum value: " << findMin(root) << endl;
            break;
        case 4: 
            cout << "Enter value to search: ";
            cin >> val;
            if (search(root, val))
                cout << val << " found in tree.\n";
            else
                cout << val << " not found.\n";
            break;
        case 5: 
            mirror(root);
            cout << "Tree mirrored.\n";
            break;
        case 6: 
            cout << "Inorder traversal: ";
            inorder(root);
            cout << endl;
            break;
        case 7: 
            cout << "Exiting...\n";
            break;
        default: 
            cout << "Invalid choice!\n";
        }
    } while (choice != 7); 

    return 0;
}