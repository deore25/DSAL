// Beginning with an empty binary search tree, Construct a binary search tree by inserting



#include <iostream>
using namespace std;

struct node {
    int data;
    node* lchild;  // Pointer to left child
    node* rchild;  // Pointer to right child

    // Constructor to initialize node
    node(int val) {
        data = val;
        lchild = rchild = nullptr;
    }
};

class BST {
public:
    node* root;

    BST() {
        root = nullptr;  // Initialize tree as empty
    }

    // To be implemented later
    void insert(int val)
    {
        root=insert(root,val);//it calls recursive function for calling
    }
    
    
    node* insert(node*root ,int val)
    {
        if (root == nullptr) {
            return new node(val);  // create new node if position is empty
        }
        
        if(val < root->data){
            root->lchild=insert(root->lchild,val);
        }
        else if(val>root->data){
            root->rchild=insert(root->rchild,val);
        }
        return root;
    }
    int maxlen()
    {
        return height(root);   
    }
    int height(node* root){
        
        if (root == nullptr){
            return 0;
        }
        int L_height=height(root->lchild);
        int R_height=height(root->rchild);
        
        return 1+ max(L_height,R_height);
        
    }
    int minimum(){
        return minn(root);
    }
    int minn(node* root){
        if (root == nullptr)
        {
            cout<<" Tree is EMPTY ";
            return -1;
        }
        node* curr=root;
        while(curr->lchild != nullptr){
            curr=curr->lchild;
        }
        return curr->data;
    }
    
    void mirror(){
        return mirrorfun(root);
    }
    void mirrorfun(node* root)
    {
        if(root == nullptr)  return;
        node* temp=root->lchild;
        root->lchild = root->rchild;
        root->rchild=temp;
        
        mirrorfun(root->lchild);
        mirrorfun(root->rchild);
        
    }
    void display() {
    cout << "In-order Traversal (Array View): ";
    displayInOrder(root);
    cout << endl;
    }

    void displayInOrder(node* root) {
        if (root == nullptr) return;
        displayInOrder(root->lchild);
        cout << root->data << " ";
        displayInOrder(root->rchild);
    }

    bool search(int ele){
        node* current = root;
        
        while( current!=nullptr)
        {
           if(ele == current->data)
           {
               cout<<" Elemnt Found : "<<current->data;
               return true;
           }
           else if(ele < current->data)
           {
               current=current->lchild;
               
           }
           else 
           {
               current=current->rchild;
           }
        }
        cout<<" Element Not Found!!!"<<endl;
        return false;
    }
};

int main() {
    BST obj;
   

    while (true) {
        cout << "\n=== MENU ===\n";
        cout << "1. Insert a node\n";
        cout << "2. Insert another node\n";
        cout << "3. Find length of longest path from root\n";
        cout << "4. Find minimum value in tree\n";
        cout << "5. Mirror the tree\n";
        cout << "6. Search a value\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        int ch;
        cin >> ch;

        switch (ch) {
                case 1:
                case 2:  // Both insert cases
                    cout << "Enter the element to INSERT: ";
                    int num;
                    cin >> num;
                    obj.insert(num);
                    obj.display(); // <<==== ADD THIS
                    break;
            
                case 3:
                    cout << "Max path length from root: " << obj.maxlen() << endl;
                    break;
            
                case 4:
                    cout << "Minimum value in the tree: " << obj.minimum() << endl;
                    break;
            
                case 5:
                    obj.mirror();
                    cout << "Tree mirrored successfully." << endl;
                    obj.display(); // <<==== ADD THIS
                    break;
            
                case 6:
                    cout << "Enter the key to search: ";
                    cin >> num;
                    obj.search(num);
                    break;
            
                case 7:
                    cout << "Exiting program. Goodbye!" << endl;
                    return 0;
            
                default:
                    cout << "!!!! Invalid Choice !!!!" << endl;
        }

    }
}
