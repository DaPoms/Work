//None of this (including comments) were made by me, this was taken from geekforgeeks.org so I could study the queens problem: https://www.geeksforgeeks.org/dsa/n-queen-problem-backtracking-3/ 

#include <vector>
#include <iostream>
using namespace std;

int placeQueens(int i, vector<int> &cols, vector<int> &leftDiagonal,
                     vector<int> &rightDiagonal, vector<int> &cur) {
    int n = cols.size();

    // base case: If all queens are placed
    // then return true
    if(i == n) return 1;

    // Consider the row and try placing
    // queen in all columns one by one
    for(int j = 0; j < n; j++){

        // Check if the queen can be placed
        if(cols[j] || rightDiagonal[i + j] || 
                        leftDiagonal[i - j + n - 1]) 
            continue;
        
        // mark the cell occupied
        cols[j] = 1;
        rightDiagonal[i+j] = 1; 
        leftDiagonal[i - j + n - 1] = 1;
        cur.push_back(j+1);

        if(placeQueens(i + 1, cols, leftDiagonal, rightDiagonal, cur)) 
            return 1;

        // remove the queen from current cell
        cur.pop_back();
        cols[j] = 0;
        rightDiagonal[i+j] = 0; 
        leftDiagonal[i - j + n - 1] = 0;        
    }
    return 0;
}

// Function to find the solution
// to the N-Queens problem
vector<int> nQueen(int n) {

    // array to mark the occupied cells
    vector<int> cols(n, 0);
    vector<int> leftDiagonal(n*2, 0);
    vector<int> rightDiagonal(n*2, 0);
    vector<int> cur;

    // If the solution exists
    if(placeQueens(0, cols, leftDiagonal, rightDiagonal, cur))
        return cur;
        
    else return {-1};
}

int main() {
    int n = 4;
    vector<int> ans = nQueen(n);
    for(auto i: ans){
        cout << i << " ";
    }
    return 0;
}
