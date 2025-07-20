/**
 * 题目来源：https://www.luogu.com.cn/problem/P1226
 * 题目简介：快速幂以及费马小定理求逆元(前提mod为素数)
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

ll qmi(ll a, ll b, ll mod){
    ll res = 1;
    a %= p;
    while(b){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll inv(ll x, ll mod){
    return qmi(x, mod - 2, mod);
}