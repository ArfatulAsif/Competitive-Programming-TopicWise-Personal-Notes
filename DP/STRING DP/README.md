
# String Dynamic Programming (DP)

[![String DP Badge](https://img.shields.io/badge/String-Dynamic%20Programming-orange?style=for-the-badge&logo=appveyor&logoColor=black)](https://shields.io/)


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

Certainly! Here’s the categorized list of dynamic programming problems with explanations for what the DP states represent:

## **1. Palindromic Substrings and Partitions**

**a. Palindrome Partitioning** [132. Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii/description/?envType=problem-list-v2&envId=m7rkfnz1)
   - **Problem:** Given a string s, partition s such that every substring of the partition is a palindrome. Return the minimum cuts needed for a palindrome partitioning of s.
   - **DP States:**
     - `dp[l][r]`: A 2D boolean table where `dp[l][r]` is true if the substring `s[l...r]` is a palindrome.
     - `DP[i]`: A 1D array where `DP[i]` represents the minimum number of cuts needed for the substring `s[0...i]`.
   - **C++ Code:**

     ```cpp
     class Solution {
     public:
         int minCut(string s) {
             int n = s.size();
             bool dp[n+1][n+1];
             memset(dp, false, sizeof(dp));

             for(int i=0;i<n;i++) dp[i][i] = true;
             for(int l = 1; l < n; l++) {
                 for(int i = 0; i < n-l; i++) {
                     int j = i+l;
                     dp[i][j] = (s[i] == s[j] && (l == 1 || dp[i+1][j-1]));
                 }
             }

             int DP[n];
             fill(DP, DP+n, 3000);
             DP[0] = 0;

             for(int i=1;i<n;i++) {
                 for(int j=0;j<=i;j++) {
                     if(dp[j][i]) {
                         DP[i] = (j == 0) ? 0 : min(DP[i], DP[j-1] + 1);
                     }
                 }
             }

             return DP[n-1];
         }
     };
     ```

**b. All Possible Partition Type. [Split the main string into K-parts]** [1278. Palindrome Partitioning III](https://leetcode.com/problems/palindrome-partitioning-iii/description/?envType=problem-list-v2&envId=m7rkfnz1)
You are given a string `s` containing lowercase letters and an integer `k`. Your task is to:

1. Change some characters of `s` to other lowercase English letters.
2. Divide `s` into `k` non-empty disjoint substrings such that each substring is a palindrome.

Return the minimal number of characters that you need to change to achieve this division.

**Solution:**

**DP States:**
- `dp[i][k]`: Minimum number of changes required to divide the substring `s[0:i]` into `k` palindromic substrings.

**Steps and Loops:**

1. **Initialization:**
   - Initialize `dp[i][j]` to a large value (`1e9`) for all `i` and `j` to represent infinity, indicating uncomputed states.

2. **Base Case:**
   - If `k == 1`, compute the minimum changes needed to make the entire substring `s[0:i]` a palindrome using the function `f(s, 0, i)`.

3. **Compute `dp[i][1]`:**
   - For each position `i`, compute the minimum changes needed to make the substring `s[0:i]` a palindrome. This is done using the function `f(s, 0, i)`.

4. **Compute `dp[i][K]`:**
   - For `K` from 2 to `k`, where `K` represents the number of partitions:
     - **Iterate over possible end positions `i`** for the current partition.
     - **For each end position `i`, iterate over possible start positions `j`** for the previous partition, updating `dp[i][K]` as:
       ```cpp
       dp[i][K] = min(dp[i][K], dp[j-1][K-1] + f(s, j, i));
       ```
     - Here, `dp[j-1][K-1]` represents the minimum changes needed to partition `s[0:j-1]` into `K-1` palindromes, and `f(s, j, i)` computes the changes needed to make `s[j:i]` a palindrome.

**Code:**

```cpp
class Solution {
public:
    int f(string &s, int i, int j) {
        int cnt = 0;
        for (; i < j; i++, j--) {
            cnt += (s[i] != s[j]);
        }
        return cnt;
    }

    int palindromePartition(string s, int k) {
        int n = s.size();
        int dp[n][k+1]; // dp[i][k] = minimum character changes for s[0:i] with k palindromic substrings.

        // Initialization
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k+1; j++) {
                dp[i][j] = 1e9;
            }
        }

        // Base Case
        if (k == 1) {
            return f(s, 0, n-1);
        }

        // Compute dp[i][1]
        for (int i = 0; i < n; i++) {
            dp[i][1] = f(s, 0, i);
        }

        // Compute dp[i][K]
        for (int K = 2; K <= k; K++) { // Number of partitions
            for (int i = K-1; i < n; i++) { // Ending of each partition
                for (int j = K-1; j <= i; j++) { // Starting of each partition and previous partition K-1 th
                    dp[i][K] = min(dp[i][K], dp[j-1][K-1] + f(s, j, i));
                }
            }
        }

        return dp[n-1][k];
    }
};
```

## **2. Word Formation and Segmentation**

**a. Word Break II** [140. Word Break II](https://leetcode.com/problems/word-break-ii/description/?envType=problem-list-v2&envId=m7rkfnz1)
   - **Problem:** Given a string s and a dictionary of strings wordDict, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences in any order.
Note that the same word in the dictionary may be reused multiple times in the segmentation.
Example 1:
Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
Output: ["cats and dog","cat sand dog"]
   - **DP States:**
     - `dp[i]`: A 1D array where `dp[i]` holds a list of valid sentences that can be formed using the substring `s[0...i]`.
   - **C++ Code:**

     ```cpp
     class Solution {
     public:
         vector<string> wordBreak(string s, vector<string>& wordDict) {
             unordered_map<string, bool> mp(wordDict.begin(), wordDict.end());
             vector<string> dp[s.size()]; // dp[i] = sentences for s[0...i]

             for(int i = 0; i < s.size(); i++) {
                 for(int j = 0; j <= i; j++) {
                     string word = s.substr(j, i-j+1);
                     if(mp[word]) {
                         if(j == 0) {
                             dp[i].push_back(word);
                         } else {
                             for(const string& prev : dp[j-1]) {
                                 dp[i].push_back(prev + " " + word);
                             }
                         }
                     }
                 }
             }

             return dp[s.size()-1];
         }
     };
     ```

**b. Concatenated Words**[472. Concatenated Words](https://leetcode.com/problems/concatenated-words/description/?envType=problem-list-v2&envId=m7rkfnz1)
   - **Problem:** Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.
A concatenated word is defined as a string that is comprised entirely of at least two shorter words (not necessarily distinct) in the given array.
Example 1:
Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]

   - **C++ Code:**

     ```cpp
      class Solution {
      public:
          vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
              unordered_map<string, bool> mp;
      
              // Populate the map with all words
              for (auto x : words) {
                  mp[x] = true;
              }
      
              // Lambda function to check if a word can be formed by concatenating other words
              auto fun = [&](const string& target) {
                  int n = target.size();
                  vector<int> dp(n, 0); // dp[i] = how many words were used to make using total 0 to i-th character
      
                  for (int i = 0; i < n; ++i) {
                      for (int j = 0; j <= i; ++j) {
                          string word = target.substr(j, i - j + 1);
      
                          if (j == 0 && mp[word]) {
                              dp[i] = max(dp[i], 1);
                          } else if (mp[word] && dp[j - 1]) {
                              dp[i] = max(dp[i], dp[j - 1] + 1);
                          }
                      }
                  }
      
                  return (dp[n - 1] > 1);
              };
      
              vector<string> ans;
      
              // Check each word and collect those that can be formed by concatenation
              for (auto x : words) {
                  if (fun(x)) {
                      ans.push_back(x);
                  }
              }
      
              // Sort the result
              sort(ans.begin(), ans.end());
      
              return ans;
          }
      };
      ```
     
