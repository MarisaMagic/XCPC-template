/**
 * 题目来源：https://www.luogu.com.cn/problem/P7009
 * 题目简介：找到一个连续子数组，使得区间gcd乘区间长度最大
 * ST表预处理区间GCD，区间gcd数量log级别
 * 二分找到每种gcd的右边界更新答案，再在右边界之后继续
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
const int N = 1e5 + 10;

ll a[N], n;
ll g[N][21];
int logn[N];

void pre_log(){
    for(int i = 2; i < N; i ++ ){
        logn[i] = logn[i >> 1] + 1;
    }
}

void rmq_gcd(){
    for(int i = 1; i <= n; i ++ ) g[i][0] = a[i];
    for(int j = 1; j < 21; j ++ ){
        for(int i = 1; i + (1 << j) - 1 <= n; i ++ ){
            g[i][j] = gcd(g[i][j - 1], g[i + (1 << (j - 1))][j - 1]);
        }
    }
}

inline ll query_gcd(int l, int r){
    int k = logn[r - l + 1];
    return gcd(g[l][k], g[r - (1 << k) + 1][k]);
}

void marisa(){
    cin >> n;
    for(int i = 1; i <= n; i ++ ) cin >> a[i];

    rmq_gcd();

    ll ans = 0;
    for(int i = 1; i <= n; i ++ ){
        ll cur_g = a[i];
        ll bound = query_gcd(i, n);
        int l = i;
        while(cur_g > bound){ // 区间中的gcd数量log级别
            int r = n;
            while(l < r){ // 找到最后一个等于cur_g的gcd_{i,j}
                int mid = l + r + 1 >> 1;
                if(query_gcd(i, mid) == cur_g) l = mid;
                else r = mid - 1;
            }
            ans = max(ans, cur_g * (l - i + 1));
            cur_g = query_gcd(i, l + 1);
            l ++ ; // 转到下一个gcd
        }
        ans = max(ans, bound * (n - i + 1));
    }
    cout << ans << "\n";
}

int main(){
    fastio;

    pre_log();

    int T = 1; cin >> T;
    while(T -- ) marisa();
    
    return 0;
}