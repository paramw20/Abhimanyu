#include<iostream>
#include<bits/stdc++.h>
#define ll long long int
using namespace std;

// Define the modulo for the problem
ll mod = 1e9 + 7;

// Define the DP table with dimensions for position, skip count, recharge count, and power
ll dp[13][13][13][1005];

// Function to solve the problem using DP
ll solve(ll pos, vector<ll>& a, ll x, ll y, ll p, ll mp) {
    // Base case: if Abhimanyu has crossed all circles, return 1
    if (pos == 11) {
        return 1;
    }

    // If the DP table has already been computed for this state, return the value
    if (dp[pos][x][y][p] != -1) {
        return dp[pos][x][y][p];
    }

    // If the enemy's power is greater than Abhimanyu's power
    if (a[pos] > p) {
        // If Abhimanyu has no more skips left
        if (x == 0) {
            // If Abhimanyu has no more recharges left or the enemy's power is greater than the maximum power
            if (y == 0 || a[pos] > mp) {
                return 0;
            }
            // Use a recharge and continue to the next circle
            return dp[pos][x][y][p] = solve(pos + 1, a, x, y - 1, mp - a[pos], mp);
        }
        else {
            // If Abhimanyu has no more recharges left or the enemy's power is greater than the maximum power
            if (y == 0 || a[pos] > mp) {
                // Use a skip and continue to the next circle
                return dp[pos][x][y][p] = solve(pos + 1, a, x - 1, y, p, mp);
            }
            // Return the maximum of using a skip or a recharge
            return dp[pos][x][y][p] = (solve(pos + 1, a, x - 1, y, p, mp) | solve(pos + 1, a, x, y - 1, mp - a[pos], mp));
        }
    }

    // If Abhimanyu's power is greater than or equal to the enemy's power
    if (x == 0) {
        // Use a recharge and continue to the next circle
        return dp[pos][x][y][p] = solve(pos + 1, a, x, y - 1, p - a[pos], mp);
    }
    // Return the maximum of using a skip or a recharge
    return dp[pos][x][y][p] = solve(pos + 1, a, x - 1, y, p, mp) | solve(pos + 1, a, x, y - 1, p - a[pos], mp);
}

// Main function to test the solve function with two test cases
int main() {
    // Test Case 1
    {
        ll x = 2, y = 2, p = 10;
        vector<ll> a = {2, 3, 5, 1, 7, 4, 6, 8, 9, 10, 11};
        // Regenerate the third and seventh enemies with half of their initial power
        a[3] += a[2] / 2;
        a[7] += a[6] / 2;
        // Initialize the DP table with -1
        memset(dp, -1, sizeof(dp));
        // Call the solve function and print the result
        ll ans = solve(0, a, x, y, p, p);
        cout << "Test Case 1: " << (ans ? "Yes" : "No") << endl;
        // This test case generates the answer as "Yes"
    }

    // Test Case 2
     {
        ll x = 2, y = 1, p = 8;
        vector<ll> a = {8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1};
        a[3] += a[2] / 2;
        a[7] += a[6] / 2;
        memset(dp, -1, sizeof(dp));
        ll ans = solve(0, a, x, y, p, p);
        cout << "Test Case 2: " << (ans ? "Yes" : "No") << endl;
         // This test case generates the answer as "No"
    }

    return 0;
}