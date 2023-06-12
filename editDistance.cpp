#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
int EditDistance(string x, string y) {
    int m = x.length();
    int n = y.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    vector<vector<char>> ops(m + 1, vector<char>(n + 1, ' '));
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i;
        ops[i][0] = 'D';
    }
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j;
        ops[0][j] = 'I';
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (x[i - 1] == y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
                ops[i][j] = ' ';
            } else {
                int del = dp[i - 1][j] + 1;
                int ins = dp[i][j - 1] + 1;
                int sub = dp[i - 1][j - 1] + 1;

                if (del <= ins && del <= sub) {
                    dp[i][j] = del;
                    ops[i][j] = 'D';
                } else if (ins <= del && ins <= sub) {
                    dp[i][j] = ins;
                    ops[i][j] = 'I';
                } else {
                    dp[i][j] = sub;
                    ops[i][j] = 'S';
                }
            }
        }
    }
    int i = m, j = n;
    vector<string> operations;
    while (i > 0 || j > 0) {
        if (ops[i][j] == ' ') {
            --i;
            --j;
        } else if (ops[i][j] == 'D') {
            operations.push_back("Delete " + string(1, x[i - 1]));
            --i;
        } else if (ops[i][j] == 'I') {
            operations.push_back("Insert " + string(1, y[j - 1]));
            --j;
        } else if (ops[i][j] == 'S') {
            operations.push_back("Substitute " + string(1, x[i - 1]) + " with " + string(1, y[j - 1]));
            --i;
            --j;
        }
    }
    reverse(operations.begin(), operations.end());
    for (const auto& op : operations) {
        cout << op << endl;
    }

    return dp[m][n];
}

int main() {
    string x, y;
    cout << "Enter the first word: ";
    cin >> x;
    cout << "Enter the second word: ";
    cin >> y;
    cout << EditDistance(x,y);
    return 0;
}