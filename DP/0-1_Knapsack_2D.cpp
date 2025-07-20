/**
 * 题目来源：https://www.acwing.com/problem/content/description/8/
 * 题目简介：二维费用背包问题
**/
#include<iostream>
using namespace std;

const int N = 110;
int dp[N][N], n, c1, c2;
int v, m, w;

int main(){
    cin >> n >> c1 >> c2;
    for(int i = 1; i <= n; i ++ ){
        cin >> v >> m >> w;
        for(int j = c1; j >= v; j -- ) // 第一维度费用
            for(int k = c2; k >= m; k -- ) // 第二维度费用
                dp[j][k] = max(dp[j][k], dp[j - v][k - m] + w); 
    }
    cout << dp[c1][c2] << endl;

    return 0;
}