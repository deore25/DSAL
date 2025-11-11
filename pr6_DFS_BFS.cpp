#include <iostream>
#include <stack>   
#include <queue>   
using namespace std;

const int MAX = 10;        
int graph[MAX][MAX];       
bool visited[MAX];        
int n;                    


void resetVisited() {
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }
}


void printAdjacencyMatrix() {
    cout << "\nAdjacency Matrix:\n  ";
    
    for (int i = 0; i < n; i++)
        cout << i << " ";
    cout << "\n";

    
    for (int i = 0; i < n; i++) {
        
        cout << i << ": ";
        
        for (int j = 0; j < n; j++) {
            
            cout << graph[i][j] << " ";
        }
        cout << "\n";
    }
}


void DFS_UsingStack(int start) {
    stack<int> s;     
    s.push(start);    
    visited[start] = true; 

    
    while (!s.empty()) {
        int curr = s.top(); 
        s.pop();            
        cout << curr << " "; 

      
        for (int i = n - 1; i >= 0; i--) {
            
            if (graph[curr][i] == 1 && !visited[i]) {
                visited[i] = true; 
                s.push(i);        
            }
        }
    }
}


void BFS(int start) {
    queue<int> q;     
    visited[start] = true; 
    q.push(start);    

    while (!q.empty()) {
        int curr = q.front(); 
        q.pop();            
        cout << curr << " ";

        
        for (int i = 0; i < n; i++) {
            
            if (graph[curr][i] == 1 && !visited[i]) {
                visited[i] = true; 
                q.push(i);      
            }
        }
    }
}

int main() {
    int edges;
    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> edges;

    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    
    cout << "Enter edges (format: u v):\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;   
        graph[v][u] = 1;   
    }

    
    printAdjacencyMatrix();

   
    resetVisited(); 
    cout << "\nDFS Traversal (using stack) starting from node 0: ";
    DFS_UsingStack(0);

   
    resetVisited(); 
    cout << "\nBFS Traversal (using queue) starting from node 0: ";
    BFS(0);

    cout << endl;
    return 0;
}