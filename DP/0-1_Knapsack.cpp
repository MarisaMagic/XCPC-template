/**
 * 题目来源：https://www.acwing.com/activity/content/problem/content/997/
 * 题目简介：01 背包
**/
#include<iostream>
using namespace std;

const int N = 1010;
int dp[N], v[N], w[N];
int n, c;

int main(){
    cin >> n >> c;
    for(int i = 1; i <= n; i++) cin >> v[i] >> w[i];
    for(int i = 1; i <= n; i++){
        for(int j = c; j >= v[i]; j--){
            dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
        }
    }
    cout << dp[c];
}