/**
 * 题目来源：https://www.luogu.com.cn/problem/B3611
 * 题目简介：floyd 求传递闭包 bitset 优化
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

void marisa(){
    int n; cin >> n;
    vector<bitset<101>> d(n + 1);
    for(int i = 1; i <= n; i ++ ){
        for(int j = 1; j <= n; j ++ ){
            int x; cin >> x;
            d[i][j] = x;
        }
    }
    for(int k = 1; k <= n; k ++ ){
        for(int i = 1; i <= n; i ++ ){
            if(d[i][k]){
                d[i] = d[i] | d[k];
            }
        }
    }
    for(int i = 1; i <= n; i ++ ){
        for(int j = 1; j <= n; j ++ ){
            cout << d[i][j] << " \n"[j == n];
        }
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}