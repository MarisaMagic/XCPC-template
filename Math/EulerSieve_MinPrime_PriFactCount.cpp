/**
 * 题目来源：https://atcoder.jp/contests/abc400/tasks/abc400_e
 * 题目简介：欧拉筛预处理出质因子数量为 2 的所有数
 * 二分求出最大的不小于 x 的两个质因子指数均为偶数的数
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

const int N = 1e6 + 10;

vector<int> primes;
int mn_p[N], cnt_p[N]; // 最小质因子 质因子数量

void eular_sieve(int n){
    for(int i = 2; i <= n; i ++ ){
        if(mn_p[i] == 0){ // 质数
            mn_p[i] = i;  // 最小质因子为本身
            cnt_p[i] = 1; // 质因子数量为 1
            primes.emplace_back(i);
        }
        for(auto p : primes){
            if(p * i > n) break;
            mn_p[i * p] = p; // 最小质因子
            if(mn_p[i] == p){ // i 被 p 筛过，i乘上其它质数一定会被p的倍数筛掉
                cnt_p[i * p] = cnt_p[i];
                break; 
            } 
            cnt_p[i * p] = cnt_p[i] + 1;
        }
    }
}

void marisa(){
    vector<ll> v;
    for(int i = 1; i < N; i ++ ){
        if(cnt_p[i] == 2){
            v.emplace_back(1ll * i * i);
        }
    }
    sort(begin(v), end(v));
    int q; cin >> q;
    for(int i = 1; i <= q; i ++ ){
        ll x; cin >> x;
        int pos = upper_bound(begin(v), end(v), x) - begin(v);
        pos -- ;
        cout << v[pos] << "\n";
    }
}

int main(){
    fastio;

    eular_sieve(N - 1);

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}