/**
 * 题目来源：https://www.acwing.com/problem/content/9/
 * 题目简介：分组背包，每组有若干个物品，每组最多选择1个物品
**/
#include<iostream>
using namespace std;

const int N = 110;
int dp[N], n, c, cnt;
int v[N], w[N];

int main(){
    cin >> n >> c;
    for(int i = 1; i <= n; i ++ ){
        cin >> cnt;
        for(int j = 1; j <= cnt; j ++ ) cin >> v[j] >> w[j];
        for(int j = c; j >= 0; j -- ) 
            for(int k = 1; k <= cnt; k ++ )
                if(j >= v[k]) dp[j] = max(dp[j], dp[j - v[k]] + w[k]);
    }
    
    cout << dp[c] << endl;
    
    return 0;
}