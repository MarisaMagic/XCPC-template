/**
 * 题目来源：https://www.luogu.com.cn/problem/P3811
 * 题目简介：线性求逆元
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

// p = ki + j -> k = p / i, j = p % i
// 两边同乘 inv(i) * inv(j) -> k * inv(j) + inv(i) = 0(mod p)
// inv(i) = -k * inv(j) = (-p / i) * inv(p % i), p % i < i

void marisa(){
    ll n, p; cin >> n >> p;
    vector<ll> inv(n + 1);
    inv[1] = 1;
    for(int i = 2; i <= n; i ++ ){
        inv[i] = (p - p / i) * inv[p % i] % p;
    }
    for(int i = 1; i <= n; i ++ ){
        cout << inv[i] << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}