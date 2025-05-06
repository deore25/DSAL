
//Dictionary using height balance tree
#include <iostream>
#include <string>
using namespace std;

struct Node {
    string keyword, meaning;
    int height;
    Node* left;
    Node* right;

    Node(string k, string m) {
        keyword = k;
        meaning = m;
        height = 1;
        left = right = nullptr;
    }
};

// Get height of the node
int height(Node* n) {
    return n ? n->height : 0;
}

// Update height
int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

// Right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

// Left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}

// Insert keyword and meaning into AVL tree
Node* insert(Node* root, string keyword, string meaning) {
    if (!root) return new Node(keyword, meaning);

    if (keyword < root->keyword)
        root->left = insert(root->left, keyword, meaning);
    else if (keyword > root->keyword)
        root->right = insert(root->right, keyword, meaning);
    else {
        cout << "Keyword already exists.\n";
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // LL
    if (balance > 1 && keyword < root->left->keyword)
        return rightRotate(root);

    // RR
    if (balance < -1 && keyword > root->right->keyword)
        return leftRotate(root);

    // LR
    if (balance > 1 && keyword > root->left->keyword) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL
    if (balance < -1 && keyword < root->right->keyword) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Find minimum value node
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

// Delete a keyword from the tree
Node* deleteNode(Node* root, string keyword) {
    if (!root)
        return root;

    if (keyword < root->keyword)
        root->left = deleteNode(root->left, keyword);
    else if (keyword > root->keyword)
        root->right = deleteNode(root->right, keyword);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->keyword = temp->keyword;
        root->meaning = temp->meaning;
        root->right = deleteNode(root->right, temp->keyword);
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

// Search and return number of comparisons
bool search(Node* root, string keyword, int& comparisons) {
    while (root) {
        comparisons++;
        if (keyword == root->keyword) {
            cout << "Keyword found! Meaning: " << root->meaning << "\n";
            return true;
        }
        root = (keyword < root->keyword) ? root->left : root->right;
    }
    cout << "Keyword not found.\n";
    return false;
}

// Update meaning of a keyword
bool update(Node* root, string keyword, string newMeaning) {
    while (root) {
        if (keyword == root->keyword) {
            root->meaning = newMeaning;
            return true;
        }
        root = (keyword < root->keyword) ? root->left : root->right;
    }
    return false;
}

// Inorder (ascending)
void displayAscending(Node* root) {
    if (root) {
        displayAscending(root->left);
        cout << root->keyword << " : " << root->meaning << "\n";
        displayAscending(root->right);
    }
}

// Reverse Inorder (descending)
void displayDescending(Node* root) {
    if (root) {
        displayDescending(root->right);
        cout << root->keyword << " : " << root->meaning << "\n";
        displayDescending(root->left);
    }
}

int main() {
    Node* root = nullptr;
    int choice;
    string keyword, meaning;

    do {
        cout << "\nDictionary Menu:\n";
        cout << "1. Add Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Update Meaning\n";
        cout << "4. Display Ascending\n";
        cout << "5. Display Descending\n";
        cout << "6. Search Keyword (Show Comparisons)\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(); // Ignore newline character from previous input

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, keyword);
                cout << "Enter meaning: ";
                getline(cin, meaning);
                root = insert(root, keyword, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                getline(cin, keyword);
                root = deleteNode(root, keyword);
                break;
            case 3:
                cout << "Enter keyword to update: ";
                getline(cin, keyword);
                cout << "Enter new meaning: ";
                getline(cin, meaning);
                if (update(root, keyword, meaning))
                    cout << "Meaning updated.\n";
                else
                    cout << "Keyword not found.\n";
                break;
            case 4:
                cout << "\nDictionary in Ascending Order:\n";
                displayAscending(root);
                break;
            case 5:
                cout << "\nDictionary in Descending Order:\n";
                displayDescending(root);
                break;
            case 6: {
                cout << "Enter keyword to search: ";
                getline(cin, keyword);
                int comparisons = 0;
                search(root, keyword, comparisons);
                cout << "Total comparisons: " << comparisons << "\n";
                break;
            }
            case 7:
                cout << "Exiting.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 7);

    return 0;
}
