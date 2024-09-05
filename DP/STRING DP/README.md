
# String Dynamic Programming (DP)

## Introduction

String DP problems involve solving optimization problems related to string manipulation. These problems often require you to consider substrings, partitions, or subsequences of a given string, and can be approached efficiently using dynamic programming techniques. The general approach usually involves defining a **Bottom up** DP table where each cell represents a subproblem related to substrings or subsequences.

## General Approach

For problems involving two strings `s1` and `s2`:
- **2D DP Table**: Use a DP table `dp[i][j]` where `i` indexes `s1` and `j` indexes `s2`.
- **State Transition**: Typically involves checking characters from `s1` and `s2` and updating the DP table based on matches or operations.

### Example Code
```cpp
// i - indexing string s1
// j - indexing string s2
for (int i = 1; i <= n; ++i) {
   for (int j = 1; j <= m; ++j) {
       if (s1[i-1] == s2[j-1]) {
           dp[i][j] = /* code */;
       } else {
           dp[i][j] = /* code */;
       }
   }
}
```

For problems involving a single string `s`:
- **2D DP Table**: Use a DP table `dp[i][j]` where `i` and `j` represent the start and end of the substring.
- **State Transition**: Update the DP table based on whether substrings are palindromes or meet other criteria.

### Example Code
```cpp
for (int l = 1; l < n; ++l) {
   for (int i = 0; i < n-l; ++i) {
       int j = i + l;
       if (s[i] == s[j]) {
           dp[i][j] = /* code */;
       } else {
           dp[i][j] = /* code */;
       }
   }
}
```
