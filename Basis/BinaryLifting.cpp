/**
 * 题目来源：https://atcoder.jp/contests/abc367/tasks/abc367_e
 * 题目简介： 倍增
 * 给定两个长度相同的数组 x 和数组 a
 * 每次将整个数组的 a_i 变为 a_{x_i}
 * 求变化 K 次后的数组 a（K <= 1e18）
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

void marisa(){
    int n; ll K; cin >> n >> K;
    vector<int> x(n + 1);
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i ++ ) cin >> x[i];
    for(int i = 1; i <= n; i ++ ) cin >> a[i];
    
    vector<array<int, 61>> f(n + 1);
    for(int i = 1; i <= n; i ++ ) f[i][0] = x[i]; // a_i 变化 1 次后对应下标
    for(int j = 1; j < 61; j ++ ){
        for(int i = 1; i <= n; i ++ ){
            f[i][j] = f[f[i][j - 1]][j - 1]; // a_i 变化 2^j 次后对应的下标
        }
    }

    vector<int> ans(n + 1);
    for(int i = 1; i <= n; i ++ ){
        ll sum = 0, pos = i; // 对于每个位置 i 找到变化 K 次的对于 x 下标
        for(int j = 60; ~j; j -- ){
            if(sum + (1ll << j) <= K){
                sum += (1ll << j);
                pos = f[pos][j];
            }
        }
        ans[i] = a[pos];
    }
    for(int i = 1; i <= n; i ++ ){
        cout << ans[i] << " \n"[i == n];
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}