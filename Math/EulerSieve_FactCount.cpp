/**
 * 题目来源：
 * 题目简介：欧拉筛法求1~N每个数约数个数
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)

const int N = 1e5 + 10;
vector<int> primes;
int mnp[N];
int mnp_cnt[N]; // mnp_cnt[x]: x最小质因子数量
int d[N]; // d[x]: x约数个数
void euler_sieve(int n){
    d[1] = 1;
    for(int i = 2; i <= n; i ++ ){
        if(mnp[i] == 0){
            primes.emplace_back(i);
            mnp[i] = i;
            mnp_cnt[i] = 1; // 最小质因子是自己
            d[i] = 2;
        }
        for(const auto& p : primes){
            if(i * p > n) break;
            mnp[i * p] = p;
            if(i % p == 0){
                mnp_cnt[i * p] = mnp_cnt[i] + 1;
                d[i * p] = d[i] / (mnp_cnt[i] + 1) * (mnp_cnt[i] + 2);
                break;
            }
            mnp_cnt[i * p] = 1; // p 是最小质因子
            d[i * p] = d[i] * 2;
        }
    }
}

int main(){
    fastio;

    euler_sieve(N - 5);

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}