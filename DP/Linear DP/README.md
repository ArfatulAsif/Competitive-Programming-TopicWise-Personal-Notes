
---
# Linear DP Common Approach

[![Linear DP Badge](https://img.shields.io/badge/Linear-Dynamic%20Programming-yellow?style=for-the-badge&logo=appveyor&logoColor=black)](https://shields.io/)

1. Linear DP has only one state. (sometimes like dp[n][2] which is essentially linear)
2. Linear DP has an iterative nature, meaning they can be solved using bottom-up or tabulation quite easily. Since the relation can be easily derived from previous states (which can be calculated unlike top-down)... 

## Step - 1 Define dp states:
[![Define States Badge](https://img.shields.io/badge/Define%20States-Important-blue)](https://shields.io/) <br>
Strictly define what DP state means. For example:
- `dp[i]` means `from 0-th to i-th element` total calculated property. Or,
- `dp[i]` means `for i-th to n-th element` total calculated property. Or,
- `dp[i]` means `from 0-th to i-th element` maximum/minimum calculated property. Or,
- `dp[i]` means `for i-th to n-th element` maximum/minimum calculated property. Or,
  - Add variations based on specific problem requirements.
  - `dp[n+1][2]` Here `dp[i][0]` means `from 0 to i-th element` LIS with positive (current - previous) amd `dp[i][1]` means from `0 to i-th element` LIS with negetive (current-previous)

## Common Top-Down Approach
```cpp
int f(int n) {
    if (n <= 1) {
        return n;
    }

    if (dp[n] != -1) {
        return dp[n];
    }

    // Define transitions or loops if necessary.

    dp[n] = f(n - 1) + f(n - 2);

    return dp[n];
}
```
## Common Bottom-Up Approach
Most of linear DP is solved using the bottom-up approach because there is only one state, and the transition relation is not that hard to find from the bottom or start state to the final state.

```cpp
dp[1] = 1;

for (int i = 2; i <= n; ++i) {
    // Define the transition relation based on the problem.
    dp[i] = dp[i - 1] + dp[i - 2];
}

return dp[n];
```
---

# Linear DP Common Problems:
- Coin change all variant
- LIS
- Fibonacci

**To solve most of the linear dp problems we have to think like coin change dp variants.** <br>
Cause they are the best representative on how to get ans from already linearly calculated previous states. Also LIS is an amazing example for getting the ans like this
```cpp
for(int i=0;i<n;i++)
{
   for(int j=0;j<i;j++)
   {
        if(condition)
               dp[i] += dp[j];
               or,
               dp[i] = max(dp[i],dp[j]+1)   
   }
}
```


## Problem List
```
https://leetcode.com/list/50vlu3z5/
```
---
My List 
```
https://leetcode.com/list/?selectedList=pmwcfjf6
```
---

---
This Was created by Me ........ If any mistakes , please inform me

