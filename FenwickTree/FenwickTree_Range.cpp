/**
 * 题目来源：https://www.luogu.com.cn/problem/P3368
 * 题目简介：树状数组 2
 * 1. 将区间 +x；2. 询问某一个数的值
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define lowbit(x) (x) & (-x)
const int N = 5e5 + 10;
using ll = long long;

int n, q;
ll a[N], tr[N];

inline void add(int x, ll c){
    for(int i = x; i <= n; i += lowbit(i)){
        tr[i] += c;
    }
}

inline int query(int x){
    ll res = a[x];
    for(int i = x; i; i -= lowbit(i)){
        res += tr[i];
    }
    return res;
}

void marisa(){
    cin >> n >> q;
    for(int i = 1; i <= n; i ++ ){
        cin >> a[i];
    }
    for(int i = 1, op, x; i <= q; i ++ ){
        cin >> op >> x;
        if(op == 1){
            int y; ll k; cin >> y >> k;
            add(x, k), add(y + 1, -k);
        }else{
            cout << query(x) << "\n";
        }
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}