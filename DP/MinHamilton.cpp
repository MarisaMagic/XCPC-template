/**
 * 题目来源：https://www.acwing.com/problem/content/93/
 * 题目简介：最短hamilton路径，从起点0~n-1经过每个点恰好1次的最短路径长度
**/
#include<bits/stdc++.h>
using namespace std;

#define ios ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
const int N = 20, M = (1 << N), inf = 0x3f3f3f3f;
int n, g[N][N], dp[M][N];
// dp[i][j] 表示走到点j的经过的点的状态为i

int main(){
    ios;

    cin >> n;
    for(int i = 0; i < n; i ++ ){ 
        for(int j = 0; j < n; j ++ ){ 
            cin >> g[i][j];
        }
    }

    memset(dp, 0x3f, sizeof dp);
    dp[1][0] = 0;
    for(int i = 0; i < (1 << n); i ++ ){
        for(int j = 0; j < n; j ++ ){
            if(i >> j & 1){
                for(int k = 0; k < n; k ++ ){
                    if((i - (1 << j)) >> k & 1){
                        dp[i][j] = min(dp[i][j], dp[i - (1 << j)][k] + g[k][j]);
                    }
                }
            }
        }
    }
    cout << dp[(1 << n) - 1][n - 1] << "\n";

    return 0;
}