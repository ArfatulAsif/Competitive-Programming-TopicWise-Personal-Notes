
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



### 2.Using given coins any number of times how many ways I can make `n`. where order doesn't matters.  (3+1=4 , 1+3=4 counted once)

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
