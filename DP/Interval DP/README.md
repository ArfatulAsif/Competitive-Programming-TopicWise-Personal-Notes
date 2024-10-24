# Interval DP

[![Interval DP Badge](https://img.shields.io/badge/interval-Dynamic%20Programming-orange?style=for-the-badge&logo=appveyor&logoColor=black)](https://shields.io/)


## Introduction
Interval DP is a dynamic programming technique commonly used to solve problems where the solution depends on finding the optimal solution for contiguous intervals of a sequence. The core idea is to break down a problem into smaller intervals and solve for the best possible outcome using overlapping subproblems. The technique is well-suited for problems where the solution for a larger interval depends on the optimal solutions of its subintervals.

## Problem Statement
Given a set of numbers, find the optimal solution for a problem by considering the current number and the best solutions from both the left and right intervals of the current number. The goal is to find the optimal answer by evaluating all possible subintervals of the original sequence.

## Approach
The strategy for Interval DP involves:
1. **Defining the DP state**: Each state represents the optimal solution for a specific interval of the array.
2. **Recursion for intervals**: For each interval from `i` to `j`, find an optimal value by dividing the interval into two parts using a partition point `k` and combining the best solutions from both parts.
3. **Transition formula**:

   $$
   dp[i][j] = \max(dp[i][j], dp[i][k] + result[k] + dp[k+1][j])
   $$
   
   Here, `dp[i][j]` represents the best solution for the interval from `i` to `j`, and `result[k]` represents the contribution of element `k` to the final solution.

# Common Approach

## Top-Down (Recursive with Memoization)
In the top-down approach, we recursively solve for the optimal solution by dividing the interval into two parts and memoizing the results to avoid recalculating solutions for overlapping subproblems.

```cpp
int topDown(vector<int>& nums, int i, int j, vector<vector<int>>& memo) {
    if (i > j) return 0;  // Base case
    if (memo[i][j] != -1) return memo[i][j];
    
    int result = 0;
    for (int k = i; k <= j; ++k) {
        result = max(result, topDown(nums, i, k-1, memo) + result[k] + topDown(nums, k+1, j, memo));
    }
    return memo[i][j] = result;
}
```

## Bottom-Up (Iterative)
In the bottom-up approach, we build the solution iteratively starting from smaller subintervals and combining them to solve for larger intervals. The DP table is filled step-by-step, ensuring that smaller subproblems are solved before larger ones.

```cpp
int bottomUp(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int l = 1; l < n; ++l) {
        for (int i = 0; i < n - l; ++i) {
            int j = i + l;
            for (int k = i; k < j; ++k) {
                dp[i][j] = max(dp[i][j], dp[i][k] + result[k] + dp[k+1][j]);
            }
        }
    }
    return dp[0][n-1];
}
```

Here’s the updated explanation, explicitly defining the DP state for each problem and adding clarity to what `dp[i][j][turn]` represents.

---

## Problem Type 1: **Turn-Based Game with Array Ends**

In this type of problem, two players alternately remove elements from either end of an array, and the game's outcome depends on both players' ability to play optimally. The challenge often involves finding the optimal strategy for one or both players, where one tries to maximize their score, and the other attempts to minimize the opponent’s advantage.

### Characteristics of Turn-Based Game Problems:
- **Two Players**: Often referred to as Alice and Bob.
- **Array of Stones/Values**: Players pick from either the start or end of the array.
- **Objective**: One player aims to maximize their score, while the other minimizes the difference in scores.
- **Optimal Play**: Dynamic programming is required to simulate all possible decisions for both players who play optimally.

---

### Example 1: **1690. Stone Game VII** 

- **Problem**: Alice and Bob alternately remove stones from the array’s ends. They score points based on the sum of the remaining stones. Alice wants to maximize the difference in score, while Bob tries to minimize it.
- **DP Definition**: `dp[i][j][turn]` represents the **optimal difference** in score between Alice and Bob when they play on the subarray from index `i` to `j`, with the `turn` indicating whose turn it is (0 for Alice, 1 for Bob).
- **Solution Approach**: Use dynamic programming with states `dp[i][j][turn]`, where `i` and `j` denote the current interval of stones, and `turn` determines whose turn it is to play.

```cpp
class Solution {
public:
    vector<int> pref;
    int dp[1001][1001][2]; // dp[i][j][turn] = optimal difference using elements from i to j, with each player's turn (0 for Alice, 1 for Bob)

    // Helper function to get the sum of stones in the range [i, j]
    int sum(int i, int j) {
        return i == 0 ? pref[j] : pref[j] - pref[i-1];
    }

    // DP function to solve the problem
    int f(int i, int j, int turn) {
        if (i == j) return 0; // Base case: no difference in score if only one stone left
        int &ret = dp[i][j][turn];
        if (ret != -1) return ret; // Memoization

        if (turn == 0) { // Alice's turn
            ret = max(sum(i+1, j) + f(i+1, j, 1), sum(i, j-1) + f(i, j-1, 1));
        } else { // Bob's turn
            ret = min(-sum(i+1, j) + f(i+1, j, 0), -sum(i, j-1) + f(i, j-1, 0));
        }
        return ret;
    }

    int stoneGameVII(vector<int>& stones) {
        int n = stones.size();
        pref = stones;
        for (int i = 1; i < n; i++) {
            pref[i] += pref[i-1];
        }
        memset(dp, -1, sizeof(dp));
        return f(0, n-1, 0); // Start with the full range, Alice's turn (0)
    }
};
```

---

### Example 2: **877. Stone Game**

- **Problem**: Alice and Bob play optimally, removing piles of stones from either end of an array. Alice aims to maximize her score, and Bob tries to do the same. The task is to determine if Alice will always win.
- **DP Definition**: `dp[i][j][turn]` represents the **optimal score difference** between Alice and Bob for the subarray from index `i` to `j`, where `turn` is 0 if it’s Alice's turn and 1 if it’s Bob's turn.
- **Solution Approach**: Use dynamic programming to calculate the optimal difference for each possible interval.

```cpp
class Solution {
public:
    int dp[501][501][2]; // dp[i][j][turn] = optimal difference between Alice and Bob using piles from index i to j, with each player's turn (0 for Alice, 1 for Bob)
    vector<int> v;

    // DP function to calculate the optimal score difference
    int f(int i, int j, int turn) {
        if (i == j) {
            return turn == 0 ? v[i] : -v[i]; // Base case: only one pile left
        }
        int &ret = dp[i][j][turn];
        if (ret != -1) return ret; // Memoization

        if (turn == 0) { // Alice's turn
            ret = max(v[i] + f(i+1, j, 1), v[j] + f(i, j-1, 1));
        } else { // Bob's turn
            ret = min(-v[i] + f(i+1, j, 0), -v[j] + f(i, j-1, 0));
        }
        return ret;
    }

    bool stoneGame(vector<int>& piles) {
        v = piles;
        memset(dp, -1, sizeof(dp));
        return f(0, piles.size()-1, 0) >= 0; // Alice wins if her score difference is >= 0
    }
};
```

---

### Example 3: **486. Predict the Winner**

- **Problem**: Two players take turns picking numbers from either end of an array, trying to maximize their scores. The task is to predict if Player 1 can win assuming both play optimally.
- **DP Definition**: `dp[i][j][turn]` represents the **optimal score difference** between Player 1 and Player 2 when playing on the subarray from index `i` to `j`, with `turn` indicating whose turn it is (0 for Player 1, 1 for Player 2).
- **Solution Approach**: Use dynamic programming to calculate the score difference and determine if Player 1 wins.

```cpp
class Solution {
public:
    int dp[21][21][2]; // dp[i][j][turn] = optimal score difference between Player 1 and Player 2 for subarray i to j, with turn indicating whose turn it is
    vector<int> v;

    // DP function to calculate the score difference
    int f(int i, int j, int turn) {
        if (i == j) {
            return turn == 0 ? v[i] : -v[i]; // Base case: only one element left
        }
        int &ret = dp[i][j][turn];
        if (ret != -1) return ret; // Memoization

        if (turn == 0) { // Player 1's turn
            ret = max(v[i] + f(i+1, j, 1), v[j] + f(i, j-1, 1));
        } else { // Player 2's turn
            ret = min(-v[i] + f(i+1, j, 0), -v[j] + f(i, j-1, 0));
        }
        return ret;
    }

    bool predictTheWinner(vector<int>& nums) {
        v = nums;
        memset(dp, -1, sizeof(dp));
        return f(0, nums.size()-1, 0) >= 0; // Player 1 wins if their score difference is >= 0
    }
};
```

---
