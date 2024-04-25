---
# Bitmask DP Common Approach

[![Bitmask DP Badge](https://img.shields.io/badge/Bitmask-Dynamic%20Programming-orange?style=for-the-badge&logo=appveyor&logoColor=black)](https://shields.io/)

1. Bitmask DP involves using bits to represent subsets of a set, often used when dealing with states that can be represented with `on` or `off` conditions.
   
2. It is particularly useful in problems requiring optimization over combinations or permutations, especially when the input size is small (n <= 20).


# Bitmask DP Common Problems:
- Traveling Salesman Problem (TSP)
- Assignment Problem
- Optimal task assignment based on abilities



# Step - Define dp states TOP-DOWN [Single state, dp[mask]]:

[![Define States Badge](https://img.shields.io/badge/Define%20States-Crucial-cyan)](https://shields.io/) 

## Maximize/Minimize [base case = 111111111111]:

- `dp[mask]` = minimum/maximum number of additional things requires `to fill remaining unmasked bits`... For example if musk = 010100, then `to fill 101011` the minimum/maximum number of additional things require is the answer for this state...


```cpp
int f(int mask) {
    if ( mask == (1<<n)-1) {    // base condition is all bits are set in the mask...
        return baseValue(mask);
    }

    if (dp[mask] != -1) {
        return dp[mask];
    }

    int ans = inf; // or appropriate initial value
    for (int i = 0; i < n; ++i) {
       if (can_transition(mask, i)) {
            int new_mask = transition(mask, i);
            result = min(result, solve(new_mask) + cost_or_value_of_transition);
        }
    }
    dp[mask] = ans;
    return ans;
}

// answer = f(0)



// here can_transition might include checking whether (mask & (1<<i))==0 or even in cases where we can use same item multiple times, then we have to consider other style checking. Or even some cases might include generating musk.

// new_must might inlcude new_mask = (mask | (1<<i)) most of the time.
// However in cases where can use more than one item at a time, we might be require to do OR with multiple set bits... Depending on the problem..

```

## Maximize/Minimize [base case = 0000000]:

- `dp[mask]` = minimum/maximum number of additional things requires `to unset remaining set bits`... For example if musk = 010100, then `to unset all the one's` the minimum/maximum number of additional things require is the answer for this state...

```cpp
int f(int mask) {
    if ( mask == 0 {    // base condition is all bits are unset
        return baseValue(mask);
    }

    if (dp[mask] != -1) {
        return dp[mask];
    }

    int ans = inf; // or appropriate initial value
    for (int i = 0; i < n; ++i) {
       if (can_transition(mask, i)) {
            int new_mask = transition(mask, i);
            result = min(result, f(new_mask) + cost_or_value_of_transition);
        }
    }
    dp[mask] = ans;
    return ans;
}

anser = f( (1<<n)-1)

```

## Count of things [base case = 11111...]

- `dp[mask]` = count of additional things `to set remaining unset bits`... For example if musk = 010100, then `to set all the zero's`, the number of additional things require is the answer for this state...


```cpp
int f(int mask) {
    if ( mask == (1<<n)-1) {    // base condition is all bits are set in the mask...
        return baseValue(mask);
    }

    if (dp[mask] != -1) {
        return dp[mask];
    }

    int ans = 0; // or appropriate initial value
    for (int i = 0; i < n; ++i) {
       if (can_transition(mask, i)) {
            int new_mask = transition(mask, i);
            ans +=  f(new_mask);
        }
    }
    dp[mask] = ans;
    return ans;
}

answer = f(0)

```

## Count of things [base case = 0000000...]

- `dp[mask]` = count of additional things `to unset remaining set bits`... For example if musk = 010100, then `to unset all the one's`, the number of additional things require is the answer for this state...


```cpp
int f(int mask) {
    if ( mask == 0) {    
        return baseValue(mask);
    }

    if (dp[mask] != -1) {
        return dp[mask];
    }

    int ans = 0; // or appropriate initial value
    for (int i = 0; i < n; ++i) {
       if (can_transition(mask, i)) {
            int new_mask = transition(mask, i);
            ans +=  f(new_mask);
        }
    }
    dp[mask] = ans;
    return ans;
}

anser = f((1<<n)-1)

```

---

# Step - Define dp states TOP-DOWN [Multiple states, dp[i][mask]]:


## Maximize/Minimize [base case = (i == n) && musk = 1111111...]:

- `dp[i][mask]` = minimum/maximum number of additional things requires from `i-th row to n-th` and  `to fill remaining unmasked bits`... For example if musk = 010100, then `from i-th row to n-th` and  `to fill 101011` the minimum/maximum number of additional things require is the answer for this state...

```cpp
int f(int i, int mask) {
    if ( i == n && mask == (1<<n)-1) {   
        return baseValue(mask);
    }

    if (i == n) {
        return 0; // return inf; [In this case all 2nd condition is not sathisfied. i.e. all bits are not visited/used..
     }

    if (dp[i][mask] != -1) {
        return dp[mask];
    }

    int ans = inf; // or appropriate initial value
    for (int j = 0; j < n; ++j) {
       if (can_transition(mask, j)) {
            int new_mask = transition(mask, j);
            result = min(result, f(i+1, new_mask) + cost_or_value_of_transition); // going to next row, with new valid mask.
        }
    }
    dp[i][mask] = ans;
    return ans;
}

answer = f(0,0) // starting from 0-th row. then base case i == n-1 thakbe
//or,
answer = f(1,0) // 1-based. , then base case e i == n thakbe

// For example consider this problem :  723. Find Minimum Time to Finish All Jobs

 // dp[i][mask] = from i to n minimum of the maximum working time of a working while assigning the rest of the unmasked job...

int f(int p, int mask, vector<int> &jobs, int k, vector<vector<int>> &dp )
    {
        if(p == k) // here for the last row/person , we are making all the unset bits set so musk is essentailly = 1111111...
        {          // both (i == n) and mask = 11111 is satishfied..
            int rem = 0;
            for(int j=0;j<jobs.size();j++)
            {
                if(mask & (1<<j))
                {

                }
                else 
                {
                    // all unset items are now visited , making musk = 111111...
                    rem += jobs[j]; // assigning remaining all the jobs to this last one, as all the jobs must be assigned..
                }
            }            
            return rem;
        }        
        if(dp[p][mask]!=-1)
        {
            return dp[p][mask];
        }

        int ans = f(p+1, mask, jobs, k, dp);

        vector<int> remi;

        for(int i=0;i<jobs.size();i++)
        {
            if(mask & (1<<i))
            {

            }
            else 
            {
                remi.push_back(i);
            }
        }

        for(int i = 0; i < (1<<remi.size()); i++)
        {
            int cost = 0;

            int add_mask = 0;

            for(int j = 0; j<remi.size();j++)
            {
                if(i & (1<<j))
                {
                    cost += jobs[remi[j]];
                    add_mask |= (1<<remi[j]);
                }
            }
            ans = min(ans, max(cost, f(p+1, mask | add_mask, jobs, k, dp)));
        }
        return dp[p][mask] = ans;
    }
    int minimumTimeRequired(vector<int>& jobs, int k) {
        int n = jobs.size();

        vector<vector<int>> dp(k , vector<int> ( (1<<jobs.size()), -1));

        return f(1, 0, jobs, k , dp);
    }
};



```


## Maximize/Minimize [base case = (i == 0) && musk = 000000...]:

- `dp[i][mask]` = minimum/maximum number of additional things requires from `i-th row to 0-th` and  `to unset remaining set bits`... For example if musk = 010100, then `from i-th row to 0-th` and  `to unset 101011` the minimum/maximum number of additional things require is the answer for this state...

```cpp
int f(int i, int mask) {
    if ( i == 0 && mask == 0 ) {    // base condition is all bits are unset in the mask...
        return baseValue(mask);
    }

    if (i == 0) {
        return 0; // return inf; [In this case all 2nd condition is not sathisfied. i.e. all bits are not unset..
     }

    if (dp[i][mask] != -1) {
        return dp[mask];
    }

    int ans = inf; // or appropriate initial value
    for (int j = 0; j < n; ++j) {
       if (can_transition(mask, j)) {
            int new_mask = transition(mask, j);
            result = min(result, f(i+1, new_mask) + cost_or_value_of_transition); // going to next row, with new valid mask.
        }
    }
    dp[i][mask] = ans;
    return ans;
}

```



## Maximize/Minimize [base case = (i == n)]:

- `dp[i][mask]` = minimum/maximum number of additional things requires from `i-th row to n-th` row and  `via visiting valid next musks`... 

```cpp
int f(int i, int mask) {

    if (i == n) {
        return 0 // return inf; [In this case all bits are not required to be sets. Problem like this involves visiting next valid subsets.  
     }

    if (dp[i][mask] != -1) {
        return dp[mask];
    }

    int ans = inf; // or appropriate initial value
    for (int j = 0; j < n; ++j) {
       if (can_transition(mask, j)) {
            int new_mask = transition(mask, j);
            result = min(result, f(i+1, new_mask) + cost_or_value_of_transition); // going to next row, with new valid mask.
        }
    }
    dp[i][mask] = ans;
    return ans;
}

answer = f(0,0) // starting from 0-th row. then base case i == n-1 thakbe
//or,
answer = f(1,0) // 1-based. , then base case e i == n thakbe

```


## Maximize/Minimize [base case = (i == 0)]:

- `dp[i][mask]` = minimum/maximum number of additional things requires from `i-th row to 0-th` row and  `via visiting valid next musks`... 

```cpp
int f(int i, int mask) {

    if (i == 0) {
        return 0 // return inf; [In this case all bits are not required to be sets. Problem like this involves visiting next valid subsets.  
     }

    if (dp[i][mask] != -1) {
        return dp[mask];
    }

    int ans = inf; // or appropriate initial value
    for (int j = 0; j < n; ++j) {
       if (can_transition(mask, j)) {
            int new_mask = transition(mask, j);
            result = min(result, f(i+1, new_mask) + cost_or_value_of_transition); // going to next row, with new valid mask.
        }
    }
    dp[i][mask] = ans;
    return ans;
}

answer = f(n-1, 0) // starting from (n-1)-th row to 0-th, taking current valid musk = 00000000..
//or,
answer = f(n-1 , (1<<n)-1) starting from (n-1)-th row to 0-th, taking current valid musk = 11111111. depending on the problem..

```


## Count of additional things [base case = (i == n) && musk = 1111111...]:

- `dp[i][mask]` = count of the number of additional things requires from `i-th row to n-th` and  `to fill remaining unmasked bits`... For example if musk = 010100, then `from i-th row to n-th` and  `to fill 101011` the number of additional things require is the answer for this state...

```cpp
int f(int i, int mask) {
    if ( i == n && mask == (1<<n)-1) {   
        return baseValue(mask);
    }

    if (i == n) {
        return 0;  [In this case all 2nd condition is not sathisfied. i.e. all bits are not visited/used..
     }

    if (dp[i][mask] != -1) {
        return dp[mask];
    }

    int ans = inf; // or appropriate initial value
    for (int j = 0; j < n; ++j) {
       if (can_transition(mask, j)) {
            int new_mask = transition(mask, j);
            ans += f(i+1, new_mask); // going to next row, with new valid mask.
        }
    }
    dp[i][mask] = ans;
    return ans;
}
```

## Count of additional things rest base case think your self [similar to maximize and minimize, just count of additinal]


---
## Problem List
```
https://leetcode.com/discuss/general-discussion/1050391/Must-do-Dynamic-programming-Problems-Category-wise
```
---
My List 
```
https://leetcode.com/list?selectedList=mom8z6mr
```
---

---
This README was created by Me ........ If any mistakes, please inform me
