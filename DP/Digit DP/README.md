---
# Digit DP Common Approach

[![Digit DP Badge](https://img.shields.io/badge/Digit-Dynamic%20Programming-blue?style=for-the-badge&logo=appveyor&logoColor=white)](https://shields.io/)

Digit DP is a technique to solve problems related to numbers where decisions are made digit by digit from the most significant digit (MSD) to the least significant digit (LSD).


# Digit DP Common Problems:

1. **Count Numbers with Specific Constraints**  
   Count numbers within a range that meet certain digit-based constraints, such as having no two consecutive equal digits.

2. **Sum of Digits Problems**  
   Calculate the sum of the digits of numbers within a range that satisfy given properties.

3. **Numbers with Restricted Digits**  
   Count how many numbers can be formed using a given set of digits that are less than a given number.


# Define dp states TOP-DOWN dp[pos][tight][state]:

### Problem Statement

Given two integers `L` and `R`, compute the sum of all digits of every integer between `L` and `R` (inclusive).

We define a 3-dimensional DP array `dp[pos][tight][sum]` where:

- **`pos`**: The current digit position we are processing from the most significant digit (MSD) to the least significant digit (LSD).
  
- **`tight`**: A flag (0 or 1) indicating whether the current number being formed is tightly bound by the upper limit (`num`).
  - If `tight` is true, digits up to the current digit of `num` are considered.
  - If `tight` is false, any digit (0-9) can be used.
  
- **`sum`**: The accumulated sum of the digits from MSD to the current `pos`.


**dp[pos][tight][sum] = total sum of all digits of numbers that can be formed using the remaining `pos to lsb digits` (since it's top-down) `having already formed (msb to pos) digits and their sums = sum`**


### Implementation Details

```cpp
int dp[20][2][180];

int f(int pos, int tight, int sum, string &num) {
    if(pos == num.size()) return sum;

    if(dp[pos][tight][sum] != -1) return dp[pos][tight][sum];

    int ans = 0;
    int limit = tight ? (num[pos] - '0') : 9;

    for(int i = 0; i <= limit; i++) {
        ans += f(pos + 1, tight && (i == limit), sum + i, num);
    }

    return dp[pos][tight][sum] = ans;
}

int solve(string L, string R) {
    memset(dp, -1, sizeof(dp));
    int ansR = f(0, 1, 0, R);

    memset(dp, -1, sizeof(dp));
    int ansL = f(0, 1, 0, L);

    return ansR - ansL;
}

int main() {
    string L = "010";  // Lower limit
    string R = "155";  // Upper limit

    cout << "Sum of digits from " << L << " to " << R << ": " << solve(L, R) << endl;
    return 0;
}
```

# Define dp states (with previous zero considered) TOP-DOWN dp[pos][tight][prev_all_zero]:

### Problem Statement [902. Numbers At Most N Given Digit Set]

Given an array of digits which is sorted in non-decreasing order. You can write numbers using each digits[i] as many times as we want. For example, if digits = ['1','3','5'], we may write numbers such as '13', '551', and '1351315'.
Return the number of positive integers that can be generated that are less than or equal to a given integer n.

- **`prev_all_zero`**: Indicates whether all previously considered digits were zeros (`1` if true, `0` otherwise). This state helps in handling leading zeros effectively, preventing the formation of numbers that are invalid under the conditions given.

The `prev_all_zero` state is essential when the number of digits affects the solution, allowing us to differentiate between scenarios where leading zeros may alter the validity or counting of generated numbers.


**`dp[pos][tight][prev_all_zero]` counts the number of valid integer configurations that can be formed from the current digit position onwards, considering whether previous digits were all zeros and whether the current configuration is tightly bound to `num`.**

### Implementation Details

```cpp

int dp[10][2][2];

int f(int pos, int tight, int prev_all_zero, string num, vector<int> &digits) {
    if(pos == num.size()) {
        return prev_all_zero == 0;  // Return 1 if not all previous digits were zero, [when we are not counting zero (0)]
    }

    if(dp[pos][tight][prev_all_zero] != -1) {
        return dp[pos][tight][prev_all_zero];
    }

    int ans = 0;
    int limit = tight ? (num[pos] - '0') : 9;

    if(prev_all_zero) {
        // Continue with zero at the current position if all previous were zeros
        ans += f(pos + 1, tight && (0 == limit), 1, num, digits);
    }

    for(int digit : digits) {
        if(digit > limit) break;  // No need to consider larger digits if tight

        ans += f(pos + 1, tight && (digit == limit), 0, num, digits);
    }

    return dp[pos][tight][prev_all_zero] = ans;
}

int ans(vector<string>& digits, int n) {
    vector<int> v;
    for(string &s : digits) {
        v.push_back(s[0] - '0');
    }
    sort(v.begin(), v.end());

    string num = to_string(n);
    memset(dp, -1, sizeof(dp));

    return f(0, 1, 1, num, v);
}

```

# Define dp states [Divisibility condition included] with reminder as states dp[pos][tight][prev_all_zero][reminder]:

### Problem Statement [Custom Challenge - d-Magic Numbers] **https://codeforces.com/contest/628/problem/D**

Given two integers `m` and `d`, and two numbers `a` and `b` such that `a ≤ b`, the challenge is to find the count of d-magic numbers within the range `[a, b]` that are also multiples of `m`. A number is considered d-magic if the digit `d` appears on even positions in its decimal representation and nowhere else. The answer should be returned modulo \(10^9 + 7\).

***Define DP States TOP-DOWN: dp[pos][tight][prev_all_zero][is_prev_odd][remainder]***

#### Definition of DP Array:
- **`pos`**: The current digit position (0-indexed from the left) being considered in the number.
  
- **`tight`**: A flag indicating if the current number being generated is tightly bound by the upper limits of the range (`b` initially, and `a` when adjusted).
  
- **`prev_all_zero`**: Indicates whether all the previously considered digits were zeros, essential for handling leading zeros correctly.
  
- **`is_prev_odd`**: A flag indicating if the previous position was odd (1) or even (0), essential for placing the digit `d` correctly according to the problem constraints.
  
- **`remainder`**: The remainder when the number formed so far is divided by `m`, crucial for determining if the number is a multiple of `m`.

```cpp
int dp[2001][2][2][2][2001];
int Mod, d;
int MOD = 1e9 + 7;

int f(int pos, int tight, int prev_all_zero, int is_prev_odd, int remainder, string &num) {
    if (pos == num.size()) {
        return remainder == 0 && !prev_all_zero; // Valid number if divisible by m and not all zeros
    }
    if (dp[pos][tight][prev_all_zero][is_prev_odd][remainder] != -1) {
        return dp[pos][tight][prev_all_zero][is_prev_odd][remainder];
    }

    // For leading zero continuation
    if (prev_all_zero) {
        ans += f(pos + 1, tight && (0 == limit), true, false, remainder, num);
        ans %= MOD;
    }

    int ans = 0, limit = tight ? (num[pos] - '0') : 9;

    for (int digit = (prev_all_zero ? 1 : 0); digit <= limit; ++digit) {

        if ((is_prev_odd && digit != d) || (!is_prev_odd && digit == d)) continue;

        ans += f(pos + 1, tight && (digit == limit), false, !is_prev_odd, (remainder * 10 + digit) % Mod, num);
        ans %= MOD;
    }
   

    return dp[pos][tight][prev_all_zero][is_prev_odd][remainder] = ans;
}

int32_t main() {

    cin >> Mod >> d;
    string a, b;
    cin >> a >> b;

    memset(dp, -1, sizeof(dp));
    int ans = f(0, 1, 1, 0, 0, b); // Solve for upper bound

    memset(dp, -1, sizeof(dp));
    a = findDiff(a, "1");  // Decrement lower bound by 1
    ans -= f(0, 1, 1, 0, 0, a);  // Solve for one less than lower bound

    cout << (ans + MOD) % MOD << endl;  // Ensure non-negative output
}
```


# Define DP States with Lower and Upper Tight Conditions

For certain problems, instead of calculating the answer by using f(b) - f(a-1), it may be more efficient to determine the result for the range [a, b] in a single function call. This approach can be necessary due to constraints such as time limits or the computational cost of resetting the memoization table (using `memset(dp, -1, sizeof(dp))`) twice or specific problem types

### Problem Context - https://www.spoj.com/problems/NUMTSN/

This implementation is designed to count numbers within a specified range `[a, b]` where certain digits (specifically 3, 6, and 9) appear an equal number of times. This is determined using a dynamic programming approach that also checks for divisibility conditions.

### DP Array Definition

The dynamic programming state `dp[pos][tight][l_tight][3_cnt][6_cnt][9_cnt]` is utilized where:

- **`pos`**: Represents the current digit position being processed from the most significant digit (MSD) to the least significant digit (LSD).
- **`tight`**: A boolean flag indicating whether the current number being formed is tightly bound by the upper limit of the range (`num`), ensuring the digits do not exceed the corresponding digits of `b`.
- **`l_tight`**: A similar flag as `tight` but for the lower bound, ensuring the digits do not fall below the corresponding digits of `a`.
- **`3_cnt`**, **`6_cnt`**, **`9_cnt`**: Counters for the number of times digits 3, 6, and 9 respectively have appeared in the number being formed.

```cpp
int dp[51][17][17][17][2][2];
int Mod = 1e9+7;

int f(int pos, int tight, int l_tight, int t, int s, int n) {
    int mx = max(t, max(s, n));
    int remaining = mx * 3 - s - t - n;

    // Early termination if it's not possible to balance 3, 6, 9 counts
    if (remaining + pos > num.size()) {
        return 0;
    }

    if (pos == num.size()) {
        return ((t > 0) && (t == s) && (s == n)); // Check if all counts are equal and non-zero
    }

    int &ret = dp[pos][t][s][n][tight][l_tight];
    if (ret != -1) {
        return ret;
    }

    int start = (l_tight) ? (num1[pos] - '0') : 0;
    int limit = (tight) ? (num[pos] - '0') : 9;
    int ans = 0;

    for (int i = start; i <= limit; i++) {
        ans += f(pos + 1, tight && (i == num[pos] - '0'), l_tight && (i == num1[pos] - '0'), t + (i == 3), s + (i == 6), n + (i == 9));
        ans %= Mod;
    }

    return ret = ans;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--) {
        string a, b;
        cin >> a >> b;
        num = b;
        memset(dp, -1, sizeof(dp));
        num1 = a;

        // Pad the lower limit to match the size of the upper limit
        while (num1.size() != num.size()) {
            num1 = "0" + num1;
        }

        int ans = f(0, 1, 1, 0, 0, 0);
        cout << (ans + Mod) % Mod << endl;
    }
}

```


# Problem list

```
https://codeforces.com/blog/entry/53960
```
```
https://leetcode.com/list/50vtbd3v/
```

# My list
```
https://leetcode.com/list?selectedList=mm87jdsc
```
---


