// The North-West Corner Method is a technique used in transportation problems to find an initial basic feasible solution (IBFS).

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void northWestCornerMethod(vector<vector<int>> &cost, vector<int> &supply, vector<int> &demand) {
    int rows = supply.size();
    int cols = demand.size();
    vector<vector<int>> allocation(rows, vector<int>(cols, 0));
    int minCost = 0;

    int i = 0, j = 0;
    while (i < rows && j < cols) {
        int alloc = min(supply[i], demand[j]);
        allocation[i][j] = alloc;
        minCost += alloc * cost[i][j];
        supply[i] -= alloc;
        demand[j] -= alloc;

        if (supply[i] == 0) i++; 
        if (demand[j] == 0) j++; 
    }

    // Print the allocation matrix
    cout << "\nAllocation Table:\n";
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            cout << setw(5) << allocation[r][c] << " ";
        }
        cout << endl;
    }
    
    // Print the minimum cost
    cout << "\nMinimum Cost: " << minCost << endl;
}

int main() {
    vector<vector<int>> cost = {
        {2, 3, 4},
        {5, 2, 3},
        {3, 1, 2}
    };
    vector<int> supply = {30, 40, 50};
    vector<int> demand = {20, 50, 50};

    northWestCornerMethod(cost, supply, demand);
    return 0;
}
