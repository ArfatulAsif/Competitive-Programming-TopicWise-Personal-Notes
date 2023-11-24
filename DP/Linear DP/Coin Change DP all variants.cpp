// Intermediary
// Young kid on the block
// AIAsif try's Continuing the journey
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define endl "\n"
#define inf 1000000000000000000
#define int long long int
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

const int N = 1e6;
vector<int>coins;
int dp[N];

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);


### 1.Using given coins any number of times how many ways I can make `n`. where order matters. (3+1=4 , 1+3=4 counted different)

        dp[0] = 1;

        for (int i = 1; i <= n; ++i)
        {
                for(int j=0;j<coins.size();j++)
                {
                        if (i - coins[j] >= 0)
                        {
                                dp[i] += dp[i - coins[j]];
                        }
                }
        }



### 2.Using given coins any number of times how many ways I can make `n`. where order does n0t matters.  (3+1=4 , 1+3=4 counted once)

        dp[0] = 1;
        for(int i=0;i<coins.size();i++)
        {
                for (int j = 0; j <= n; j++)
                {
                        if(j-coins[i]>=0)
                        {
                                dp[j] += dp[j-coins[i]];
                        }
                        
                }
        }



### 3.Using given coins atmost once how many ways I can make `n`. where doesn't order matters.  (3+1=4 , 1+3=4 counted once)

	dp[0] = 1;

        for (int i = 0; i < coins.size(); ++i)
        {
                for (int j = n; j >= 0 ;j--) // Since I cant use any coin more than onces that's why we starts from j=n . To stop over counting
                {
                        if(j-coins[i]>=0)
                        {
                                dp[j] += dp[j - coins[i]];
                        }
                      
                }
        }


### 4.Using minimum number of coins make 'n' . you can use one coin more than once

        vector<int> dp(n + 1, INT_MAX);

        dp[0] = 0;

        for (int i = 1; i <= n; ++i)
        {
                for(int j=0;j<coins.size();j++)
                {
                        if (i - coins[j] >= 0)
                        {
                                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                        }
                }
        }


### 5.Using minimum number of coins make 'n' . you can use one coin atmost once

	dp[0] = 0;

        for(int i=0;i<coins.size();i++)
        {
                for (int j = n; j >= 0; --j) // Since I cant use any coin more than onces that's why we starts from j=n . To stop over counting
                {
                        if(j-coins[i]>=0)
                        {
                                dp[j] = min(dp[j], dp[j - coins[i]] + 1);
                        }
                        
                }
        }





}
