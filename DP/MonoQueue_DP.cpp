/**
 * 题目来源：https://www.acwing.com/problem/content/1091/
 * 题目简介：单调队列优化DP
 * 一个数组 a，每连续m个中至少选择一个，求最小总代价
 * dp[i] 表示前i个且选择第 i 个的最小总代价
 * dp[i] = min_{i - m <= j < i}
**/
#include<bits/stdc++.h>
using namespace std;

#define ios ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
const int N = 2e5 + 10;
typedef long long ll;

int n, m, q[N], hh, tt;
ll dp[N];

int main(){
    ios;

    cin >> n >> m;
    vector<int> a(n + 2);
    for(int i = 1; i <= n; i ++ ) cin >> a[i];
    // n + 1 为虚点 最终答案由[n-m+1,n]中转移
    for(int i = 1, x; i <= n + 1; i ++ ){  
        while(hh <= tt && i - q[hh] > m) hh ++ ;
        dp[i] = dp[q[hh]] + a[i]; // dp_i = min dp_j + x
        while(hh <= tt && dp[q[tt]] >= dp[i]) tt -- ;
        q[ ++ tt] = i;
    }
    cout << dp[n + 1] << "\n";

    return 0;
}