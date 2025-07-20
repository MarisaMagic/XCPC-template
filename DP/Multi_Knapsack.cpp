/**
 * 题目来源：https://www.acwing.com/problem/content/5/
 * 题目简介：二进制优化多重背包
 * 每种物品二进制拆分成若干个，转化为01背包
**/
#include<iostream>
using namespace std;

const int N = 2010;
int n, c, v, w, s;
int dp[N];

int main(){
    cin >> n >> c;
    for(int i = 1; i <= n; i ++ ){
        cin >> v >> w >> s;
        for(int k = 1; k <= s; k <<= 1){
            for(int j = c; j >= k * v; j -- ){
                dp[j] = max(dp[j], dp[j - k * v] + k * w);
            }
            s -= k;
        }
        if(s){ // 最后一个
            for(int j = c; j >= s * v; j -- )
                dp[j] = max(dp[j], dp[j - s * v] + s * w);
        }
    }

    cout << dp[c] << endl;

    return 0;
}