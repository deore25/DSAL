#include <iostream> 
#include <vector>   
#include <algorithm>

using namespace std; 


struct Edge {
    int u;      
    int v;      
    int weight;  
};


bool compare(Edge a, Edge b) {
    return a.weight < b.weight; 
}


int parent[100]; 


int rankArray[100]; 


int find(int x) {
    
    if (parent[x] != x) {
        
        parent[x] = find(parent[x]); 
    }
   
    return parent[x];
}


void unionSets(int a, int b) {
    
    a = find(a);
    b = find(b);

    
    if (a != b) {
        
        if (rankArray[a] < rankArray[b]) {
            
            parent[a] = b;
        } else if (rankArray[a] > rankArray[b]) {
           
            parent[b] = a;
        } else {
            
            parent[b] = a;
            
            rankArray[a]++;
        }
    }
}


int main() {
    
    cout << "\t****** Minimum Cost Phone Line Connection using Kruskal's Algorithm ******\n\n";

    int n; 
    int e;

    
    cout << "Enter number of offices: ";
    cin >> n;

    
    cout << "Enter number of connections: ";
    cin >> e;

    
    vector<Edge> edges;

    
    cout << "Enter each connection as: office1 office2 cost\n";
    
    for (int i = 0; i < e; i++) {
        Edge edge; 
        cin >> edge.u >> edge.v >> edge.weight;
        
        edges.push_back(edge);
    }

    
    sort(edges.begin(), edges.end(), compare);

    
    for (int i = 0; i < n; i++) {
        parent[i] = i;   
        rankArray[i] = 0; 
    }

    
    int totalCost = 0;

    
    cout << "\nConnections in the Minimum Spanning Tree:\n";

    
    for (Edge edge : edges) {
        
        if (find(edge.u) != find(edge.v)) {
           
            unionSets(edge.u, edge.v);
            
            totalCost += edge.weight;
            
            cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
        }
       
    }

    
    cout << "\nMinimum total cost to connect all offices: " << totalCost << endl;

   
    return 0;
}
