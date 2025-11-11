#include <iostream>
using namespace std;

#define MAX 100 

float p[MAX];        
float cost[MAX][MAX]; 
float sum[MAX][MAX];  
int n;             


void optimalBST() {
 
    for (int i = 0; i < n; i++) {
        cost[i][i] = p[i]; 
        sum[i][i] = p[i];  
    }

    
    for (int length = 2; length <= n; length++) {
        
        for (int i = 0; i <= n - length; i++) {
            
            int j = i + length - 1;
            
            cost[i][j] = 999999;
            
            sum[i][j] = sum[i][j - 1] + p[j];

            
            for (int r = i; r <= j; r++) {
                
                float left = (r > i) ? cost[i][r - 1] : 0;
                
                float right = (r < j) ? cost[r + 1][j] : 0;
                
                float total = left + right + sum[i][j];

                
                if (total < cost[i][j])
                    cost[i][j] = total;
            }
        }
    }

    
    cout << "\nMinimum expected search cost: " << cost[0][n - 1] << endl;
}

int main() {
    cout << "Enter number of keys: ";
    cin >> n;

    cout << "Enter probabilities p[0] to p[" << n - 1 << "]:\n";
   
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

   
    optimalBST();

    return 0;
}