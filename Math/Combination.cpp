/**
 * 题目来源：https://www.luogu.com.cn/problem/B3717
 * 题目简介：组合数模板 逆元取模
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

const int N = 5e6 + 10, mod = 998244353;

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

inline ll inv(ll x){
	return qmi(x, mod - 2, mod);
}

ll fac[N], infac[N];
void get_fac(int n){
	fac[0] = 1;
	for(int i = 1; i <= n; i ++ ){
		fac[i] = fac[i - 1] * i % mod;
	}
	infac[n] = inv(fac[n]); // 反推阶乘逆元
	for(int i = n; i; i -- ){
		infac[i - 1] = infac[i] * i % mod;
	}
}

inline ll C(ll n, ll m){
	if(n < m) return 0ll;
	return fac[n] * infac[n - m] % mod * infac[m] % mod;
}