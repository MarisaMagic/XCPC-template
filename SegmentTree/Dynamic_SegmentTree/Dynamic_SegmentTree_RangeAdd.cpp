/**
 * 题目来源：luogu 
 * 题目编号：P3372 【模板】 线段树 1（动态开点）
 * 题目简介：线段树区间加 + 询问区间和（动态开点）
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define mid (l + r >> 1)
#define ls (lson[u])
#define rs (rson[u])
using ll = long long;
const int N = 1e5 + 10;

int n, q, rt, tot, lson[N << 2], rson[N << 2];
ll sum[N << 2], add[N << 2];

inline void pushup(int u){
    sum[u] = sum[ls] + sum[rs];
}

inline void pushdown(int u, int l, int r){
    if(add[u]){
        if(!ls) ls = ++ tot;
        if(!rs) rs = ++ tot;
        add[ls] += add[u];
        add[rs] += add[u];
        sum[ls] += add[u] * (mid - l + 1);
        sum[rs] += add[u] * (r - mid);
        add[u] = 0;
    }
}

void node_add(int& u, int l, int r, int k, ll x){
    if(!u) u = ++ tot;
    if(l == r){
        sum[u] = x;
        return;
    }
    if(k <= mid) node_add(ls, l, mid, k, x);
    else node_add(rs, mid + 1, r, k, x);
    pushup(u);
}

void range_add(int& u, int l, int r, int ql, int qr, ll x){
    if(!u) u = ++ tot;
    if(ql <= l && r <= qr){
        add[u] += x;
        sum[u] += x * (r - l + 1);
        return;
    }
    pushdown(u, l, r);
    if(ql <= mid) range_add(ls, l, mid, ql, qr, x);
    if(qr > mid) range_add(rs, mid + 1, r, ql, qr, x);
    pushup(u);
}

ll range_query(int u, int l, int r, int ql, int qr){
    if(!u) return 0;
    if(ql <= l && r <= qr) return sum[u];
    pushdown(u, l, r);
    ll res = 0;
    if(ql <= mid) res += range_query(ls, l, mid, ql, qr);
    if(qr > mid) res += range_query(rs, mid + 1, r, ql, qr);
    return res;
}

void marisa(){
    int n, q; cin >> n >> q;
    for(int i = 1; i <= n; i ++ ){
        ll x; cin >> x;
        node_add(rt, 1, n, i, x);
    }
    for(int i = 0, op, l, r; i < q; i ++ ){
        cin >> op >> l >> r;
        if(op == 1){
            ll x; cin >> x;
            range_add(rt, 1, n, l, r, x);
        }else{
            cout << range_query(rt, 1, n, l, r) << "\n";
        }
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}