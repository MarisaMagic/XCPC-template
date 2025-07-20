/**
 * 题目来源：https://ac.nowcoder.com/acm/contest/62880/D
 * 题目简介：欧拉定理求 a^{b^n} \mod p，前提 b 和 p 互质
 * 欧拉定理求 k = b^n \mod phi(p)
 * 快速幂求 a^k \mod p
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

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

int euler_phi(int n){ // 欧拉函数
    int ans = n;
    for(int i = 2; i * i <= n; i ++ ){
        if(n % i == 0){
            ans = ans / i * (i - 1);
            while(n % i == 0){
                n /= i;
            }
        }
    }
    if(n > 1) ans = ans / n * (n - 1);
    return ans;
}

void marisa(){
    ll n, p; cin >> n >> p;
    ll k = qmi(2, n, euler_phi(p)); // 前提 a 与 p 互质
    cout << qmi(2, k, p) << "\n";
}

/*
a^b \mod p，若 a 与 p 不互质，拓展欧拉定理
if b >= phi, b = b % phi + phi
*/

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}