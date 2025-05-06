// general tree for book consist of chapter
#include <iostream>
#include <string>
using namespace std;

struct node {
    string label;
    int ch_count;
    struct node* child[10];

    node() : ch_count(0) {
        for (int i = 0; i < 10; i++) {
            child[i] = nullptr;
        }
    }
};

class GT {
public:
    node* root;

    

    GT() {
        root = nullptr;
    }

    void create() {
        root = new node;
        cout << "Name of BOOK: ";
        cin >> root->label;

        cout << "Number of chapters: ";
        cin >> root->ch_count;

        for (int i = 0; i < root->ch_count; i++) {
            root->child[i] = new node;
            cout << "  Name of Chapter: ";
            cin >> root->child[i]->label;

            cout << "  Number of sections in chapter: ";
            cin >> root->child[i]->ch_count;

            for (int j = 0; j < root->child[i]->ch_count; j++) {
                root->child[i]->child[j] = new node;
                cout << "    Name of Section: ";
                cin >> root->child[i]->child[j]->label;

                cout << "    Number of subsections in section: ";
                cin >> root->child[i]->child[j]->ch_count;

                for (int k = 0; k < root->child[i]->child[j]->ch_count; k++) {
                    root->child[i]->child[j]->child[k] = new node;
                    cout << "      Name of Subsection: ";
                    cin >> root->child[i]->child[j]->child[k]->label;
                }
            }
        }
    }

    void display(node* r) {
        if (r == nullptr) return;

        cout << "\nName of Book: " << r->label << endl;
        cout << "Number of Chapters: " << r->ch_count << endl;

        for (int i = 0; i < r->ch_count; i++) {
            cout << "\n  Chapter: " << r->child[i]->label;
            cout << "\n  Number of Sections: " << r->child[i]->ch_count << endl;

            for (int j = 0; j < r->child[i]->ch_count; j++) {
                cout << "    Section: " << r->child[i]->child[j]->label;
                cout << "\n    Number of Subsections: " << r->child[i]->child[j]->ch_count << endl;

                for (int k = 0; k < r->child[i]->child[j]->ch_count; k++) {
                    cout << "      Subsection: " << r->child[i]->child[j]->child[k]->label << endl;
                }
            }
        }
    }
};

int main() {
    GT obj;

    while (true) {
        cout << "\n\nMENU\n";
        cout << "1. CREATE\n";
        cout << "2. DISPLAY\n";
        cout << "3. EXIT\n";

        int ch;
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
        case 1:
            obj.create();
            break;
        case 2:
            obj.display(obj.root);
            break;
        case 3:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
