// Graph using DFS and BFS

#include <iostream>
#include <stdlib.h>
using namespace std;

int cost[10][10], i, j, k, n;
int qu[10], front, rear, v, visited[10];
int stk[10], top, visited1[10];

int main()
{
    int m, ch;

    while (1)
    {
        
        cout << "\nDisplay Menu";
        cout << "\n1. Create Graph";
        cout << "\n2. Display Adjacency Matrix";
        cout << "\n3. BFS (Breadth First Search)";
        cout << "\n4. DFS (Depth First Search)";
        cout << "\n5. Exit";
        cout << "\n--------------------------------------------------";
        cout << "\nEnter choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Enter number of vertices: ";
            cin >> n;
            cout << "Enter number of edges: ";
            cin >> m;

            // Initialize matrix to 0
            for (i = 0; i < n; i++)
                for (j = 0; j < n; j++)
                    cost[i][j] = 0;

            cout << "Enter edges (start end):" << endl;
            for (k = 0; k < m; k++)
            {
                cin >> i >> j;
                cost[i][j] = 1;
                cost[j][i] = 1; // undirected graph
            }
            break;

        case 2:
            cout << "The adjacency matrix of the graph is:\n";
            for (i = 0; i < n; i++)
            {
                for (j = 0; j < n; j++)
                {
                    cout << " " << cost[i][j];
                }
                cout << endl;
            }
            break;

        case 3:
            // Corrected BFS
            cout << "Enter initial vertex: ";
            cin >> v;
            front = rear = 0;

            // Reset visited array
            for (i = 0; i < n; i++)
                visited[i] = 0;

            qu[rear++] = v;
            visited[v] = 1;

            cout << "The BFS of the Graph is:\n";

            while (front < rear)
            {
                v = qu[front++];
                cout << v << " ";

                for (i = 0; i < n; i++)
                {
                    if (cost[v][i] == 1 && visited[i] == 0)
                    {
                        qu[rear++] = i;
                        visited[i] = 1;
                    }
                }
            }
            break;

        case 4:
            // Correct DFS using stack
            cout << "Enter initial vertex: ";
            cin >> v;

            // Reset visited arrays
            for (i = 0; i < n; i++)
                visited1[i] = 0;

            top = 0;
            stk[top++] = v;

            cout << "The DFS of the Graph is:\n";

            while (top > 0)
            {
                v = stk[--top];

                if (visited1[v] == 0)
                {
                    cout << v << " ";
                    visited1[v] = 1;

                    // Push neighbors in reverse order for proper DFS
                    for (i = n - 1; i >= 0; i--)
                    {
                        if (cost[v][i] == 1 && visited1[i] == 0)
                        {
                            stk[top++] = i;
                        }
                    }
                }
            }
            break;

        case 5:
            cout << "Thank you!!" << endl;
            return 0;

        default:
            cout << "Wrong choice!! Try again." << endl;
        }
    }

    return 0;
}


// input Pattern : 
// edegs should start from left side then the right side 
//     A
//    / \
//   B   C
//  / \  / 
// D   E F   
// in this tree the assigned values are : 0-A ,1-B, 2-C,3-D, 4-E ,5-F
//  and thier edges are :
//  0 1(root left)
//  0 2(root right)
//  1 3(leftchild->leftchild)
//  1 4(leftchild->rightchild)
//  2 5 (rightchild->leftchild)
//  and initialize vertex for bfs and dfs is 0(A)
