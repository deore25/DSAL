
//Given Sequence k=k1<k2....<kn, Binary Search Tree



#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Function to find the optimal binary search tree and its minimum cost
pair<int, vector<vector<int>>> optimalBST(const vector<int>& keys, const vector<double>& prob, int n) {
    // dp[i][j] will hold the minimum cost of constructing the BST for keys i to j
    vector<vector<double>> dp(n + 1, vector<double>(n + 1, 0));

    // root[i][j] will store the root index for the optimal BST for keys i to j
    vector<vector<int>> root(n + 1, vector<int>(n + 1, 0));

    // Loop over the length of the subproblems
    for (int length = 1; length <= n; length++) {
        for (int i = 1; i <= n - length + 1; i++) {
            int j = i + length - 1;
            dp[i][j] = INT_MAX;
            double sum = 0;

            // Calculate the sum of probabilities for keys i to j
            for (int k = i; k <= j; k++) {
                sum += prob[k - 1]; // prob array is 0-indexed
            }

            // Try every key as the root
            for (int r = i; r <= j; r++) {
                double cost = (r > i ? dp[i][r - 1] : 0) + (r < j ? dp[r + 1][j] : 0) + sum;

                // If this cost is less than the current cost, update dp[i][j]
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    root[i][j] = r; // Store the root of the optimal BST for keys i to j
                }
            }
        }
    }

    return {dp[1][n], root}; // Return the minimum cost and the root table
}

// Function to print the structure of the optimal BST
void printBST(const vector<vector<int>>& root, int i, int j) {
    if (i > j) return;
    
    int r = root[i][j]; // The root of the BST for the range i to j
    cout << "Root: " << r << " (key: " << r << ")\n";
    printBST(root, i, r - 1); // Left subtree
    printBST(root, r + 1, j); // Right subtree
}

int main() {
    // Input
    int n;
    cout << "Enter number of keys: ";
    cin >> n;
    
    vector<int> keys(n);
    vector<double> prob(n);
    
    cout << "Enter keys: ";
    for (int i = 0; i < n; i++) {
        cin >> keys[i];
    }
    
    cout << "Enter search probabilities: ";
    for (int i = 0; i < n; i++) {
        cin >> prob[i];
    }

    // Get the minimum cost and the root table
    auto result = optimalBST(keys, prob, n);
    double minCost = result.first;
    vector<vector<int>> root = result.second;

    cout << "Minimum search cost: " << minCost << endl;

    // Print the structure of the optimal BST
    cout << "Structure of the optimal BST:\n";
    printBST(root, 1, n);

    return 0;
}
