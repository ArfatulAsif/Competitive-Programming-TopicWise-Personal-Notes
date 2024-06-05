
---

# SOS DP (Sum Over Subsets DP) Common Approach

[![SOS DP Badge](https://img.shields.io/badge/SOS-Dynamic%20Programming-blue?style=for-the-badge&logo=appveyor&logoColor=white)](https://shields.io/)

SOS DP is a technique to efficiently compute values involving sums over all subsets of a set. It leverages bitwise operations and dynamic programming for optimal performance.

# SOS DP Common Problems:

1. **Subset Sum Queries**  
   Efficiently compute the sum of elements for all subsets of a given set.

2. **Counting Subsets with Specific Properties**  
   Count the number of subsets that meet specific conditions, such as having a particular sum or containing specific elements.

# Define dp states TOP-DOWN dp[mask][i]:

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
