
*This note was created by Arfatul Islam Asif.*
*If there are any errors please notify me. I am extremely open to suggestions*

---
# Dynamic Programming Approach

[![Dynamic Programming](https://img.shields.io/badge/Dynamic%20Programming-Approach-yellow.svg?style=for-the-badge&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAIAAAD8GO2jAAAA5UlEQVR42mP4/wj4T2wFAwAx/CFP/z//GVhEE7DKGlFZeIJQ2YUBCfGIAzVxGCx5RMIUg7CPb7gCI0D1+gx+6o8fwQOSrDo7gHoWfQMtZguAR4BHJzXpApKk8eAqmb6gZZ+sACOxLil6UNmhiTB1eQpRlUKMKOnFqJrAZGBi3g4WiGMg7Dyk8ZnFplwCtTcRhtAwBIpoJLQLkXYgZUsF1aACDgAjtkY1qLEBEAAAAASUVORK5CYII=)](https://en.wikipedia.org/wiki/Dynamic_programming)

In dynamic programming, we often define a state for our problem as `dp[x]`, with `dp[0]` as the base state and `dp[n]` as our destination state. The goal is to find the value of `dp[n]`.

## Top-Down Approach (Memoization)

[![Memoization](https://img.shields.io/badge/Approach-Top--Down-blue.svg?style=for-the-badge)](https://en.wikipedia.org/wiki/Memoization)

Start the transition from the top destination state, i.e., `dp[n]`, and follow the state transition relation to reach the base state.

```cpp
void f(int target)
{
    // Check if the base condition is met
    if (base condition)
    {
        return;
    }

    // Check if the value for dp[target] is already calculated
    if (dp[target] != -1)
    {
        return dp[target];
    }

    // Initialize the result with some base value
    int res = something;

    // Iterate through possible moves
    for (int i = 0; i < Moves.size(); i++)
    {
        // Recursive call to calculate f(target - Moves[i])
        res = res + f(target - Moves[i]);
    }

    // Store the result in dp[target] to avoid redundant calculations
    dp[target] = res;

    // Return the calculated value for dp[target]
    return dp[target];
}
```

In this template, the crucial recursive call `f(target - Moves[i])` state values is not available initially. The recursive call reaches the base state and then returns with the `f(target - Moves[i])` state's values. It's essential to understand that the Top-Down DP starts from the target state and establishes a relation `f(current state) = ans + f(previous state)`, then makes recursive calls to calculate `f(previous state)` and returns with `f(previous state)` value, which is then added to the answer.

**Execution Flow: Target State ⟶⟶⟶⟶ Initial State ⟶ Returns with Recursive Calls**

## Bottom-Up Approach (Tabulation)

[![Tabulation](https://img.shields.io/badge/Approach-Bottom--Up-green.svg?style=for-the-badge)](https://en.wikipedia.org/wiki/Bottom-up_programming)

Start the transition from the bottom base state, i.e., `dp[0]`, and follow the state transition relation to reach the destination state `dp[n]`.

```cpp
for (int i = 0; i < n; i++)
{
    for (int j = 0; j < Moves.size(); j++)
    {
        // Check if the current state is reachable using Moves[j]
        if (i > Moves[j])
        {
            // Accumulate values to calculate dp[i]
            dp[i] += dp[i - Moves[j]];
        }
    }
}
```

Before calculating `dp[i]`, we already have `dp[i - Moves[j]]` calculated, which optimizes the computation.

**Execution Flow: Initial State ⟶⟶⟶⟶ Target State**

---

# *Solving DP problems Step - 01* :
[![One and Only Step](https://img.shields.io/badge/Solving_DP_Problems-Step__01-blue.svg?style=for-the-badge)]

Read the problem carefully and declare the DP states . *For a very good habit , declare the dp states by commenting at the right of `dp[n]`  array* .

*For examples*:
```cpp
//coin dp
int dp[n+1]; // dp[i] means total number way to make i money
```

```cpp
//digit dp
int dp[22][4][2]; //dp[next N digits][non_zero_left][tight]
```

```cpp
//lis dp
int dp[n+1][2]; // dp[i][0] means from 0 to i LIS with positive (current - previous) ; dp[i][1] means from 0 to i LIS with negetive (current-previous)
```
*So on....*





