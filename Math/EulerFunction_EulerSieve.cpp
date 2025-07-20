/**
 * 题目来源：https://www.luogu.com.cn/problem/P2158
 * 题目简介：线性筛法求 1 ~ n 的欧拉函数
 * 统计 1 ~ n 中有多少对 x, y 互质
 * 欧拉函数: phi[1] = 1
 * 若 i 为质数，有 phi[i] = i - 1
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

const int N = 1e5 + 10;
vector<int> primes;
bool not_prime[N];
int phi[N];

void get_phi(int n){
	phi[1] = 1;
	for(int i = 2; i <= n; i ++ ){
		if(!not_prime[i]){
			primes.emplace_back(i);
			phi[i] = i - 1;
		}
		for(const auto& p : primes){
			if(p > n / i) break;
			not_prime[i * p] = true;
			if(i % p == 0){
				phi[i * p] = phi[i] * p;
				break;
			}
			phi[i * p] = phi[i] * (p - 1);
		}
	}
}

void marisa(){
    int n; cin >> n;
    n -- ;
    if(n == 0){
    	cout << 0 << "\n";
    	return;
    }

    get_phi(n);

    ll ans = 3; // (0, 1), (1, 0), (1, 1) 特判
    for(int i = 2; i <= n; i ++ ){
    	ans += phi[i] * 2;
    }
    cout << ans << "\n"; 
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}