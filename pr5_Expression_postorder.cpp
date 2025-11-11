#include <iostream>
#include <stack>
#include <string>
using namespace std;


class Node {
public:
    char data;
    Node* left, *right;
    Node(char val) : data(val), left(NULL), right(NULL) {}
};


Node* constructTree(string prefix) {
    stack<Node*> stk;
    
    
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char c = prefix[i];
       
        if (isalnum(c)) {
            Node* node = new Node(c);
            stk.push(node);
        }
        else {
            
            Node* node = new Node(c);
            node->left = stk.top(); stk.pop();
            node->right = stk.top(); stk.pop();
            stk.push(node); 
        }
    }
    
    return stk.top();
}


void postorderTraversal(Node* root) {
    if (!root) return;
    
    stack<Node*> stk, out;
    stk.push(root);
    
    
    while (!stk.empty()) {
        Node* node = stk.top();
        stk.pop();
        out.push(node);
        
        if (node->left) stk.push(node->left);
        if (node->right) stk.push(node->right);
    }
    
    
    while (!out.empty()) {
        cout << out.top()->data << " ";
        out.pop();
    }
    cout << endl;
}


void deleteTree(Node* root) {
    if (!root) return;
    
    deleteTree(root->left);
    deleteTree(root->right);
    
    
    delete root;
}

int main() {
    string prefix = "+--a*bc/def";
    
   
    Node* root = constructTree(prefix);
    
    
    cout << "Postorder traversal: ";
    postorderTraversal(root);
    
    
    deleteTree(root);
    
    cout << "Tree deleted successfully!" << endl;
    return 0;
}
