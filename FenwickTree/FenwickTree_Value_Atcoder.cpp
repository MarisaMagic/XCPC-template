/**
 * 题目来源：https://atcoder.jp/contests/practice2/tasks/practice2_b
 * 题目简介：树状数组
 * 1. 将某一个数 +x；2. 询问区间和
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define lowbit(x) (x) & (-x)
const int N = 5e5 + 10;
using ll = long long;

int n, q;
ll tr[N];

inline void add(int x, ll c){
    for(int i = x; i <= n; i += lowbit(i)){
        tr[i] += c;
    }
}

inline ll query(int x){
    ll res = 0;
    for(int i = x; i; i -= lowbit(i)){
        res += tr[i];
    }
    return res;
}

void marisa(){
    cin >> n >> q;
    for(int i = 1, x; i <= n; i ++ ){
        cin >> x;
        add(i, x);
    }
    for(int i = 1, op; i <= q; i ++ ){
        cin >> op;
        if(op == 0){
            int p; ll x; cin >> p >> x;
            p ++ ;
            add(p, x);
        }else{
            int l, r; cin >> l >> r;
            cout << query(r) - query(l) << "\n";
        }
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}