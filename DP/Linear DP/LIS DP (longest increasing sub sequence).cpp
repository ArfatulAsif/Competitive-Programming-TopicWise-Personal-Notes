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
int dp[N];
vector<int>nums;
int n;

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        

        dp[0] = 1;

        for (int i = 1; i < n; i++)
        {
                for (int j = 0; j < i; j++)
                {
                        if (nums[i] > nums[j])
                        {
                                dp[i] = max(dp[i], dp[j] + 1);
                        }
                }
        }

  
}
