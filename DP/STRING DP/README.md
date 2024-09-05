
# String Dynamic Programming (DP)

[![String DP Badge](https://img.shields.io/badge/String-Dynamic%20Programming-orange?style=for-the-badge&logo=appveyor&logoColor=black)](https://shields.io/)


## Introduction

String DP problems involve solving optimization problems related to string manipulation. These problems often require you to consider substrings, partitions, or subsequences of a given string, and can be approached efficiently using dynamic programming techniques. The general approach usually involves defining a **Bottom up** DP table where each cell represents a subproblem related to substrings or subsequences.

## Almost all the STRING DP problems are solved using Bottom UP [Tabulation approach]

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

## 1.1 All Possible Partition Type. [Split the main string into K-parts]** [1278. Palindrome Partitioning III](https://leetcode.com/problems/palindrome-partitioning-iii/description/?envType=problem-list-v2&envId=m7rkfnz1)

**Problem:** You are given a string `s` containing lowercase letters and an integer `k`. Your task is to:

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

     Sure, here’s a detailed breakdown of each problem, including the exact problem statements:

## **3. Counting Distinct Subsequences**

1. **115. Distinct Subsequences** [115. Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/description/?envType=problem-list-v2&envId=m7rkfnz1)
   - **Problem Statement:** 
     Given two strings `s` and `t`, return the number of distinct subsequences of `s` which equals `t`. 
     
     A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
     
   - **C++ Code:**
     ```cpp
      class Solution {
      public:
          int numDistinct(string s, string t) {
              // int dp[i][j] = till i-th character of first string, how many ways we
              // can make till j-th character of second string.
      
              // dp[i][j] = (dp[i-1][j-1] * (s[i]== t[j])) + dp[i-1][j]
      
              // =
      
              // (if current i-th character of s-string is equal to the till j-th
              // character of t, then we add -----how many ways we can make till (j-1)
              // of string-t and using (i-1)-th character of string-t )
      
              // +
      
              // (how many ways we can make till (j) of string-t and using (i-1)-th
              // character of string-t
      
              int n = s.size();
              int m = t.size();
      
              unsigned int dp[n][m + 1];
      
              memset(dp, 0, sizeof(dp));
      
              dp[0][0] = (s[0] == t[0]);
      
              for (int i = 1; i < n; i++) {
      
                  dp[i][0] = dp[i - 1][0] + (s[i] == t[0]);
              }
              
              for (int j = 1; j < m; j++) { // number of character of t-string that must be considered to be equal of till i-th character of S - string.  
                  for (int i = 1; i < n; i++) {
      
                      dp[i][j] = (dp[i - 1][j - 1] * (s[i] == t[j])) + dp[i - 1][j];
                  }
              }
      
              return dp[n - 1][m - 1];
      
              // above portion can be writing like this too for simplication..
              // for (int j = 1; j < m; j++) {
              //     for (int i = 1; i < n; i++) {
              //         if (s[i] == t[j]) {
              //             dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
      
              //         } else {
              //             dp[i][j] = dp[i - 1][j];
              //         }
              //     }
              // }
      
          }
      };
     ```

2. **940. Distinct Subsequences II** [940. Distinct Subsequences II](https://leetcode.com/problems/distinct-subsequences-ii/description/?envType=problem-list-v2&envId=m7rkfnz1)
   - **this is a special problem, not a type**
   - **Problem Statement:** 
    Given a string s, return the number of distinct non-empty subsequences of s. Since the answer may be very large, return it modulo 109 + 7.

A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not.
     
   - **C++ Code:**
     ```cpp
     class Solution {
     public:
         int distinctSubseqII(string s) {
             int n = s.size();
             
             int dp[26]; // dp[a] = number of subsequences ending with character 'a'
             
             memset(dp, 0, sizeof(dp));
             
             for (int i = 0; i < n; i++) {
                 int all_prev_unique_subsequence_count_ending_at_a_to_z = 0;
                 
                 for (int j = 0; j < 26; j++) {
                     all_prev_unique_subsequence_count_ending_at_a_to_z += dp[j];
                     all_prev_unique_subsequence_count_ending_at_a_to_z %= 1000000007;
                 }
                 
                 dp[s[i] - 'a'] = (all_prev_unique_subsequence_count_ending_at_a_to_z + 1) % 1000000007;
             }
             
             int ans = 0;
             
             for (int i = 0; i < 26; i++) {
                 ans += dp[i];
                 ans %= 1000000007;
             }
             
             return ans;
         }
     };
     ```
   - **DP State:**
     - `dp[a]`: Number of distinct subsequences of the substring `s[0..i]` ending with character `a`.

## **4: Counting Ways to Form a String**

1. **1639. Number of Ways to Form a Target String Given a Dictionary** [1639. Number of Ways to Form a Target String Given a Dictionary](https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/description/?envType=problem-list-v2&envId=m7rkfnz1)
   - **Problem Statement:**
     You are given a list of strings of the same length words and a string target.

Your task is to form target using the given words under the following rules:

target should be formed from left to right.
To form the ith character (0-indexed) of target, you can choose the kth character of the jth string in words if target[i] = words[j][k].
Once you use the kth character of the jth string of words, you can no longer use the xth character of any string in words where x <= k. In other words, all characters to the left of or at index k become unusuable for every string.
Repeat the process until you form the string target.
Notice that you can use multiple characters from the same string in words provided the conditions above are met.

Return the number of ways to form target from words. Since the answer may be too large, return it modulo 109 + 7.

   - **C++ Code:**
     ```cpp
    class Solution {
   public:
       int numWays(vector<string>& words, string target) {
           int n = words[0].size();
           int m = target.size();
   
           int cnt[n+1][27];
           memset(cnt, 0, sizeof(cnt));
   
           // Count the frequency of each character at each position
           for (int i = 0; i < words.size(); i++) {
               for (int j = 0; j < n; j++) {
                   cnt[j][words[i][j] - 'a']++;
               }
           }
   
           long long int dp[m+1][n+1]; // dp[i][j] = number of ways to form till i-th character of the target string using till j-th character of all words.
           memset(dp, 0, sizeof(dp));
   
           // Initialize the DP table for the first character of the target
           dp[0][0] = cnt[0][target[0] - 'a'];
           for (int i = 1; i < n; i++) {
               dp[0][i] += dp[0][i-1] + cnt[i][target[0] - 'a'];
           }
   
           // Fill the DP table for the rest of the target characters
           for (int i = 1; i < m; i++) {
               for (int j = i; j < n; j++) {
                   dp[i][j] += (dp[i-1][j-1] * cnt[j][target[i] - 'a']) + dp[i][j-1]; 
                   
                   // (dp[i-1][j-1] * cnt[j][target[i] - 'a']) = number of ways till (i-1)-th character was made using till (j-1) character * using current j-th place character (new count)
                   //                                                                                                                         count of a specific character at j-th place can be more than one, so multiply     
                   // dp[i][j-1] = number of ways till i-th character was made using till (j-1) character
   
                   dp[i][j] %= 1000000007;
               }
           }
   
           return (int)(dp[m-1][n-1]);
       }
   };

     ```

## 5: String Compression/After deletion we need to merge the string, and then consider again. 

1. **1531. String Compression II** [1531. String Compression II](https://leetcode.com/problems/string-compression-ii/description/?envType=problem-list-v2&envId=m7rkfnz1)
   - **Problem Statement:** 
     Run-length encoding is a string compression method that works by replacing consecutive identical characters (repeated 2 or more times) with the concatenation of the character and the number marking the count of the characters (length of the run). For example, to compress the string "aabccc" we replace "aa" by "a2" and replace "ccc" by "c3". Thus the compressed string becomes "a2bc3".

Notice that in this problem, we are not adding '1' after single characters.

Given a string s and an integer k. You need to delete at most k characters from s such that the run-length encoded version of s has minimum length.

Find the minimum length of the run-length encoded version of s after deleting at most k characters.
     
   - **C++ Code:**
      ```cpp
      class Solution {
      public:
          int f(int n) {
              if (n == 100) {
                  return 4;
              }
              if (n > 9) {
                  return 3;
              }
              if (n > 1) {
                  return 2;
              }
              if (n == 1) {
                  return 1;
              }
              return 0;
          }
      
          int getLengthOfOptimalCompression(string s, int K) {
              int n = s.size();
              int pref[n][26];
      
              memset(pref, 0, sizeof(pref));
      
              // Initialize prefix frequency array
              pref[0][s[0] - 'a'] = 1;
              for (int i = 1; i < n; i++) {
                  for (char c = 'a'; c <= 'z'; c++) {
                      pref[i][c - 'a'] = pref[i - 1][c - 'a'] + (c == s[i]);
                  }
              }
      
              int dp[n][K + 1];
      
              for (int i = 0; i < n; i++) {
                  for (int j = 0; j <= K; j++) {
                      dp[i][j] = 1e9;
                  }
              }
      
              // dp[i][k] = till i-th character and deleting at most k, minimum length of the string.
              dp[0][0] = 1;
      
              for (int i = 1; i <= K; i++) {
                  dp[0][i] = 0;
              }
      
              for (int i = 1; i < n; i++) { // till i-th character
                  for (int k = 0; k <= K; k++) { // total at most k character delete
                      for (int j = 0; j <= i; j++) { // (j...i) substring to be considered one.
                          int max_exits = 0; // which character exits the maximum time in j...i substring, its occurrence count.
      
                          for (char c = 'a'; c <= 'z'; c++) {
                              if (j == 0) {
                                  max_exits = max(max_exits, pref[i][c - 'a']);
                              } else {
                                  max_exits = max(max_exits, pref[i][c - 'a'] - pref[j - 1][c - 'a']);
                              }
                          }
      
                          int min_del = (i - j + 1) - max_exits; // Minimum deletions needed.
      
                          for (int del = min_del; del <= k; del++) { // Minimum delete to at most k delete
                              if (j == 0) {
                                  dp[i][k] = min(dp[i][k], f((i - j + 1) - del));
                              } else {
                                  dp[i][k] = min(dp[i][k], dp[j - 1][k - del] + f((i - j + 1) - del));
                              }
                          }
                      }
                  }
              }
      
              return dp[n - 1][K];
          }
      };
      ```

