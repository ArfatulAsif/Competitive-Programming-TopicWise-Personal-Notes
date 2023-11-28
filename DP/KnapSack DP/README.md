
---

# Knapsack DP Common Approach

In a knapsack DP problem, you are given two things: 

1. Weight/Cost
2. Value/Profit

The goal is to maximize the `Value` with minimum or optimum `weight/cost`.

## Approaches:

- Most problems can be solved using linear DP approach, taking only one state.
- Sometimes, DFS (backtracking) or bitmasking can be used, especially when n<20 and variables are >10000000 can't be used as array index .
- For problems with easy state relations, use bottom-up DP[iterative]. For harder relations, use top-down DP[recursive].

## Step 1: Define DP States

- **Linear DP:**
    - `dp[i]` = Maximum value gained with 0 to at most `i-th` weight [bottom-up]
    - `dp[i]` = Maximum value gained with at most `i to 0-th` weight [top-down]

- **Multiple States:**
    - `dp[i][j]` = Maximum value taken with at most `j` weight from `i-th` index to `0-th` index [top-down]
    - `dp[i][j][k]` = Number of ways to make `(profit >= minProfit)` from `i to n` elements with `j profit` and `k people` [top-down]

For problems with multiple states, top-down approach is preferred.

## Common Top-Down Approach

```cpp
// Top down approach
int dp[1000][1000];
int f(int W, int wt[], int val[], int index) {
    if (index < 0)
        return 0;
    if (dp[index][W] != -1)
        return dp[index][W];

    if (wt[index] > W) {
        dp[index][W] = f(W, wt, val, index - 1);
        return dp[index][W];
    } else {
        dp[index][W] = max(val[index] + f(W - wt[index], wt, val, index - 1), f(W, wt, val, index - 1));
        return dp[index][W];
    }
}

int main() {
    int profit[] = {60, 100, 120};
    int weight[] = {10, 20, 30};
    int W = 50;

    cout << f(W, weight, profit, n);
}
```

## Common Bottom-Up Approach

```cpp
// dp[w] = maximum value till w weight
for (int i = 0; i < n; ++i) {
    for (int w = W; w >= 0; --w) {
        if (w - wt[i] >= 0) {
            dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
        }
    }
}
```

## Problem List

[LeetCode Knapsack DP Problem List](https://leetcode.com/list/50vif4uc/)

## My LeetCode List

[My Personal LeetCode Problem List](https://leetcode.com/list/?selectedList=pmuqba96)
