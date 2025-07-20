/**
 * 题目来源：https://ac.nowcoder.com/acm/contest/39114/A
 * 题目简介：0 ~ n 中数位上数字 x 出现的次数
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

// 0 ~ n 中数位上数字 x 出现的次数
ll count_x(ll n, ll x){
    ll res = 0, k;
    for(ll i = 1; k = n / i; i *= 10){
        ll high = k / 10; // 高位数字
        if(x == 0){
            if(high) high -- ; // 最高不可为0
            else break;
        }
        res += high * i;
        ll cur = k % 10; // 当前位数字
        if(cur > x){
            res += i;
        }else if(cur == x){
            ll low = n - k * i; // 低位数字
            res += low + 1;
        }
    }
    return res + (x == 0);
}

void marisa(){
    ll n, k; cin >> n >> k;
    if(count_x(n, 0) < k){
        cout << -1 << "\n";
        return;
    }
    ll l = 0, r = n;
    while(l < r){
        ll mid = l + r + 1 >> 1;
        if(count_x(n, 0) - count_x(mid - 1, 0) >= k){
            l = mid;
        }else{
            r = mid - 1;
        }
    }
    cout << l << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}