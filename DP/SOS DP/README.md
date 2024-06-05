
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

- Maximum XOR subset is \( [1, 2, 3] \) and the maximum XOR value is \( 1 \oplus 2 \oplus 3 = 0 \).

## 3. Subset XOR Sum

### Problem Statement

Given an array of integers, calculate the sum of XOR of all subsets.

### Example

Given \( A = [1, 2, 3] \):

- Subset XOR sum is \( (1) + (2) + (3) + (1 \oplus 2) + (1 \oplus 3) + (2 \oplus 3) + (1 \oplus 2 \oplus 3) \).

## 4. Counting Subsets with a Specific Property

### Problem Statement

Given an array of integers, count the number of subsets that satisfy a given property, such as having a sum divisible by a certain number.

### Example

Given \( A = [1, 2, 3] \) and the property "sum divisible by 3":

- Subsets satisfying the property: \( [3], [1, 2] \)
- Count: 2

## 5. Compatibility Check

### Problem Statement

Given an array of integers, determine if each element is compatible with any other element using bitwise operations, such as AND or XOR.

### Example

Given \( A = [1, 2, 4, 8] \):

- \( 1 \& 2 = 0 \) (compatible)
- \( 1 \& 4 = 0 \) (compatible)
- \( 2 \& 4 = 0 \) (compatible)
- \( 1 \& 8 = 0 \) (compatible)

---

These problems illustrate the versatility and power of the SOS DP technique in solving various subset-related problems efficiently. The key is to leverage bitwise operations and dynamic programming to avoid redundant calculations and achieve optimal performance.

### Problem Statement

Given an array of integers, compute the sum of all subsets for each possible subset using the first `i` bits of the mask.

We define a 2-dimensional DP array `dp[mask][i]` where:

- **`mask`**: Represents the subset of elements we're considering.
- **`i`**: The current bit position we are processing.

**`dp[mask][i]` = sum of all subsets of `mask` that can be formed using only the first `i` bits of the mask.**

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

    if (mask & (1 << i)) {
        dp[mask][i] = f(mask, i - 1) + f(mask ^ (1 << i), i - 1);
    } else {
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
        for (int mask = 0; mask < (1 << n); mask++) {
            if (mask & (1 << i)) {
                dp[mask][i + 1] = dp[mask][i] + dp[mask ^ (1 << i)][i];
            } else {
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

# Problem: Subset and Superset Queries

### Problem Statement

Given a list of n integers, your task is to calculate for each element x:
1. The number of elements y such that \( x \mid y = x \)
2. The number of elements y such that \( x \& y = x \)
3. The number of elements y such that \( x \& y \neq 0 \)

### Recursive Implementation Details

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
        for (int mask = 0; mask < (1 << N); mask++) {
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
        for (int mask = 0; mask < (1 << N); mask++) {
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
    }
}
```

---

This detailed README includes explanations, problem statements, and both recursive and iterative implementations for SOS DP and the given problem.
