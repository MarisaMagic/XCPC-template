/**
 * 题目来源：https://www.luogu.com.cn/problem/P5431
 * 题目简介：求任意n个数的逆元
 * 先求前 n 个数mod p意义下的乘积，并用费马小定理求出前n数乘积的逆元
 * 逆向反推前i个数乘积的逆元 sv[i - 1] = sv[i] * a[i] % p
 * 第 i 个数的逆元即 sv[i] * s[i - 1]
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

ll qmi(ll a, ll b, ll p){
    ll res = 1;
    a %= p;
    while(b){
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

void marisa(){
    int n, p, k; read(n), read(p), read(k);
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i ++ ) read(a[i]);

    // 求前 n 个数乘积
    vector<int> s(n + 1);
    s[0] = 1;
    for(int i = 1; i <= n; i ++ ){
        s[i] = 1ll * s[i - 1] * a[i] % p;
    }
    // 前 n 个数乘积的逆元
    vector<int> sv(n + 1);
    sv[n] = qmi(s[n], p - 2, p);
    for(int i = n; i; i -- ){
        sv[i - 1] = 1ll * sv[i] * a[i] % p;
    }
    // 求出第 i 个数的逆元
    vector<int> inv(n + 1);
    for(int i = 1; i <= n; i ++ ){
        inv[i] = 1ll * sv[i] * s[i - 1] % p;
    }

    int ans = 0; // 输出答案形式
    for(int i = 1, j = 1; i <= n; i ++ ){
        j = 1ll * j * k % p;
        ans = (ans + 1ll * j * inv[i] % p) % p;
    }
    print(ans);
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}