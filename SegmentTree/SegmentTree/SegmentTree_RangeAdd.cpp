/**
 * 题目来源：luogu 
 * 题目编号：P3372 【模板】 线段树 1
 * 题目简介：线段树区间加 + 询问区间和
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define mid (l + r >> 1)
#define ls (u << 1)
#define rs (u << 1 | 1)
using ll = long long;
const int N = 1e5 + 10;

ll a[N];
ll sum[N << 2], add[N << 2];

inline void pushup(int u){
    sum[u] = sum[ls] + sum[rs];
}

inline void pushdown(int u, int l, int r){
    if(add[u]){
        add[ls] += add[u];
        sum[ls] += (mid - l + 1) * add[u];
        add[rs] += add[u];
        sum[rs] += (r - mid) * add[u];
        add[u] = 0; 
    }
}

void build(int u, int l, int r){
    if(l == r){ 
        sum[u] = a[l]; 
        return; 
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushup(u);
}

ll query(int u, int l, int r, int ql, int qr){
    if(ql <= l && r <= qr) return sum[u];
    pushdown(u, l, r);
    ll res = 0;
    if(ql <= mid) res += query(ls, l, mid, ql, qr);
    if(qr > mid) res += query(rs, mid + 1, r, ql, qr);
    return res;
}

void range_add(int u, int l, int r, int ql, int qr, ll k){
    if(ql <= l && r <= qr){
        add[u] += k;
        sum[u] += (r - l + 1) * k;
        return;
    }
    pushdown(u, l, r);
    if(ql <= mid) range_add(ls, l, mid, ql, qr, k);
    if(qr > mid) range_add(rs, mid + 1, r, ql, qr, k);
    pushup(u);
}

void marisa(){
    int n, m; cin >> n >> m;
    for(int i = 1; i <= n; i ++ ) cin >> a[i];

    build(1, 1, n);

    for(int i = 0, op, l, r; i < m; i ++ ){
        cin >> op >> l >> r;
        if(op == 1){
            ll k; cin >> k;
            range_add(1, 1, n, l, r, k);
        }else{
            cout << query(1, 1, n, l, r) << "\n";
        }
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();

    return 0;
}