//you have a business with several of ices; .. 
// You want a set of lines that connects all your of ices with a minimum total cost

#include <iostream>
#include <climits>
using namespace std;

#define MAX 100
int cost[MAX][MAX]; // Adjacency matrix
int parent[MAX], key[MAX], visited[MAX];
int n;

int minKey() {
    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++)
        if (!visited[v] && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void primMST() {
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        visited[i] = 0;
    }

    key[0] = 0;       // Start from the first office
    parent[0] = -1;   // First node is root of MST

    for (int count = 0; count < n - 1; count++) {
        int u = minKey();
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (cost[u][v] && !visited[v] && cost[u][v] < key[v]) {
                parent[v] = u;
                key[v] = cost[u][v];
            }
        }
    }

    // Display MST
    int totalCost = 0;
    cout << "\nEdges in the MST:\n";
    for (int i = 1; i < n; i++) {
        cout << "Office " << parent[i] << " - Office " << i << " with cost " << cost[i][parent[i]] << endl;
        totalCost += cost[i][parent[i]];
    }
    cout << "Total cost of laying phone lines: " << totalCost << endl;
}

int main() {
    int m, u, v, w;
    cout << "Enter number of offices: ";
    cin >> n;
    cout << "Enter number of connections (edges): ";
    cin >> m;

    // Initialize cost matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = 0;

    cout << "Enter connections (office1 office2 cost):" << endl;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        cost[u][v] = w;
        cost[v][u] = w; // Undirected graph
    }

    primMST();

    return 0;
}
