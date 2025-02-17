#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void leastCostMethod(vector<vector<int>>& cost, vector<int>& supply, vector<int>& demand, int m, int n) {
    vector<vector<int>> allocation(m, vector<int>(n, 0));  

    vector<vector<int>> originalCost = cost;  

    while (true) {
        // Find the minimum cost element that is still eligible (supply > 0 and demand > 0)
        int minCost = INT_MAX;
        int minRow = -1, minCol = -1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (cost[i][j] < minCost && supply[i] > 0 && demand[j] > 0) {
                    minCost = cost[i][j];
                    minRow = i;
                    minCol = j;
                }
            }
        }

        // If we cannot find any valid minimum cost (i.e., all supplies or demands are exhausted), break the loop
        if (minRow == -1 || minCol == -1) {
            break;
        }

        // Allocate as much as possible to this cell
        int allocated = min(supply[minRow], demand[minCol]);
        allocation[minRow][minCol] = allocated;

        // Update supply and demand
        supply[minRow] -= allocated;
        demand[minCol] -= allocated;

        // If a supply or demand is exhausted, set the cost of that row or column to INT_MAX to prevent further allocation
        if (supply[minRow] == 0) {
            for (int j = 0; j < n; j++) {
                cost[minRow][j] = INT_MAX;
            }
        }

        if (demand[minCol] == 0) {
            for (int i = 0; i < m; i++) {
                cost[i][minCol] = INT_MAX;
            }
        }
    }

    // Output the allocation matrix
    cout << "Initial allocation using Least Cost Method:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << allocation[i][j] << "\t";
        }
        cout << endl;
    }

    // Calculate the total transportation cost
    int totalCost = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            totalCost += allocation[i][j] * originalCost[i][j];
        }
    }

    cout << "Total transportation cost: " << totalCost << endl;
}

int main() {
    vector<vector<int>> cost = {
        {2, 3, 4},
        {5, 2, 3},
        {3, 1, 2}
    };
    vector<int> supply = {30, 40, 50};
    vector<int> demand = {20, 50, 50};

    int m = 3, n = 3; 

    leastCostMethod(cost, supply, demand, m, n);

    return 0;
}
