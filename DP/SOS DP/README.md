
---

# SOS DP (Sum Over Subsets DP) Common Approach

[![SOS DP Badge](https://img.shields.io/badge/SOS-Dynamic%20Programming-blue?style=for-the-badge&logo=appveyor&logoColor=white)](https://shields.io/)

SOS DP is a technique to efficiently compute values involving sums over all subsets of a set. It leverages bitwise operations and dynamic programming for optimal performance.

# Common Problems:

## Sum Over Subsets (SOS):

Given an array \( A \) of \( 2^N \) integers, calculate \( F(x) \) for all \( x \), where \( F(x) \) is defined as the sum of all \( A[i] \) such that \( i \) is a subset of \( x \).

## Example
Given \( A = [1, 2, 4, 8] \) for \( N = 2 \):

Let's break down the example using bit representation of subset sum generation:

- \( F(0) = F(00) = A[00] = A[0] = 1 \)
- \( F(1) = F(01) = A[00] + A[01] = A[0] + A[1] = 1 + 2 = 3 \)
- \( F(2) = F(10) = A[00] + A[10] = A[0] + A[2] = 1 + 4 = 5 \)
- \( F(3) = F(11) = A[00] + A[01] + A[10] + A[11] = A[0] + A[1] + A[2] + A[3] = 1 + 2 + 4 + 8 = 15 \)


## 2. Maximum XOR Subset

### Problem Statement

Given an array of integers, find the maximum value of XOR of any subset of the given array.

### Example

Given \( A = [1, 2, 3] \):

- Maximum XOR subset is \( [1, 2] \) and the maximum XOR value is = 3.

## 3. Counting Subsets with a Specific Property

### Problem Statement

Given an array of integers, count the number of subsets that satisfy a given property, such as having a sum divisible by a certain number.

### Example

Given \( A = [1, 2, 3] \) and the property "sum divisible by 3":

- Subsets satisfying the property: \( [3], [1, 2] \)
- Count: 2

## 4. Compatibility Check

### Problem Statement

Given an array of integers, determine if each element is compatible with any other element using bitwise operations, such as AND or XOR.

### Example

Given \( A = [1, 2, 4, 8] \):

- \( 1 \& 2 = 0 \) (compatible)
- \( 1 \& 4 = 0 \) (compatible)
- \( 2 \& 4 = 0 \) (compatible)
- \( 1 \& 8 = 0 \) (compatible)

---


# Define dp state : SOS DP :  dp[mask][i] (base case i == 0 or -1):

**`dp[mask][i]` = sum of all subsets of `mask` that can be formed using only the first `i` bits of the mask.**

keep in mind that here if mask = 101. This includes subsets all the following subsets [A[0] by 0000], [ A[0] + A[1] by 001], [ A[0] + A[4] by 100], [A[0] + A[1] + A[4] + A[5] by 101]

### Recursive Implementation Details

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 20;
vector<int> A, SOS;
int dp[1 << N][N];

int f(int mask, int i) {
    if (i == -1) {
        return A[mask];
    }

    if (dp[mask][i] != -1) {
        return dp[mask][i];
    }

    if (mask & (1 << i)) {  // if current bit of the mask is set, then for subsets, we can either consider this bit or not,
                  // taking current bit       // getting new set without considering current bit
        dp[mask][i] = f(mask, i - 1) + f(mask ^ (1 << i), i - 1);

    } else { // if current bit is zero then we can't consider it.
                       // leaving as it is.
        dp[mask][i] = f(mask, i - 1);
    }

    return dp[mask][i];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n = 2;
    A = {7, 12, 14, 16};
    SOS.resize(1 << n);

    memset(dp, -1, sizeof(dp));

    for (int i = 0; i < (1 << n); i++) {
        SOS[i] = f(i, n - 1);
    }

    for (int i = 0; i < (1 << n); i++) {
        cout << SOS[i] << endl;
    }
}
```

### Iterative Implementation Details

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 20;
vector<int> A, SOS;
int dp[1 << N][N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n = 2;
    A = {7, 12, 14, 16};
    SOS.resize(1 << n);

    for (int mask = 0; mask < (1 << n); mask++) {
        dp[mask][0] = A[mask];
    }

    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {    // This implementation does not repeats counts. Like fix number of coins in coin change dp 

            if (mask & (1 << i)) {   // if current bit of the mask is set, then for subsets, we can either consider this bit or not,
                               // taking current bit       // getting new set without considering current bit
                dp[mask][i + 1] = dp[mask][i] + dp[mask ^ (1 << i)][i];

            } else { // if current bit is zero then we can't consider it.
                             // leaving as it is.
                dp[mask][i + 1] = dp[mask][i];
            }
        }
    }

    for (int mask = 0; mask < (1 << n); mask++) {
        SOS[mask] = dp[mask][n];
    }

    for (int mask = 0; mask < (1 << n); mask++) {
        cout << SOS[mask] << endl;
    }
}
```

## CSES Example problem[ Subset and Superset Queries](https://cses.fi/problemset/task/1654/)

### Problem Statement

Given a list of n integers, your task is to calculate for each element x:
1. The number of elements y such that ( x | y = x )
2. The number of elements y such that ( x & y = x )
3. The number of elements y such that ( x & y != 0)

### Recursive Implementation Details

For this kind of problem:
1. ( x | y = x ) , here y is a bitwise subset of x
2. ( x & y = x ) , here y is a bitwise superset of x
3. ( x & y != 0) , here y is either bitwise subset or super set of x. So just by removing all the subsets of inverse_x we get this count


```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 20;
int dp1[1 << N][N + 1]; // dp1[mask][i] = count of subsets of `mask` that can be formed using (0 to i-th bits) and exist as elements in the array 
int dp2[1 << N][N + 1]; // dp2[mask] = count of supersets of `mask` that can be formed using (0 to i-th bits) and exist as elements in the array

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> v;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        v.push_back(a);

        dp1[a][0]++;
        dp2[a][0]++;
    }

    for (int i = 0; i < N; i++) {
        for (int mask = 0; mask < (1 << N); mask++) {  // This implementation does not repeats counts. Like fix number of coins in coin change dp. Count for each elements occurs once only
            if (mask & (1 << i)) {
                dp1[mask][i + 1] += dp1[mask ^ (1 << i)][i] + dp1[mask][i];  // subset  
                dp2[mask][i + 1] += dp2[mask][i];
            } else {
                dp2[mask][i + 1] += dp2[mask ^ (1 << i)][i] + dp2[mask][i];  // supersets
                dp1[mask][i + 1] += dp1[mask][i];  
            }
        }
    }

    for (auto x : v) {
        int inv_x = (~x & ((1 << N) - 1));
        cout << dp1[x][N] << " " << dp2[x][N] << " " << (n - dp1[inv_x][N]) << endl;
    }
}
```

### Optimized Implementation Details

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 21;
int dp1[1 << N]; // dp1[mask] = count of subsets of mask that exist as elements in the array
int dp2[1 << N]; // dp2[mask] = count of supersets of mask that exist as elements in the array

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> v;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        v.push_back(a);

        dp1[a]++;
        dp2[a]++;
    }

    for (int i = 0; i < N; i++) {
        for (int mask = 0; mask < (1 << N); mask++) { // This implementation does not repeats counts. Like fix number of coins in coin change dp. Count for each elements occurs once only

            if (mask & (1 << i)) {
                dp1[mask] += dp1[mask ^ (1 << i)];  // subset  
            } else {
                dp2[mask] += dp2[mask ^ (1 << i)];  // supersets
            }
        }
    }

    for (auto x : v) {
        int inv_x = (~x & ((1 << N) - 1));
        cout << dp1[x] << " " << dp2[x] << " " << (n - dp1[inv_x]) << endl;
                                                // inv er kuno sub sets er sathe AND korle 0 asbe

    }
}
```

---


## Problem list :
```
https://codeforces.com/blog/entry/45223
```
```
https://usaco.guide/adv/dp-sos?lang=cpp
```
