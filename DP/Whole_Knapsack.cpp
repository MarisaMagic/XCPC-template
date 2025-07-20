/**
 * 题目来源：https://www.acwing.com/activity/content/problem/content/998/
 * 题目简介：完全背包，物品数量没有限制
**/
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1010;
int n, c;
int dp[N];
int v[N], w[N];

int main(){
    cin >> n >> c;
    for(int i = 1; i <= n; i++) cin >> v[i] >> w[i];
    for(int i = 1; i <= n; i++)
        for(int j = v[i]; j <= c; j++){
            dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
        }

    cout<<dp[c];
}