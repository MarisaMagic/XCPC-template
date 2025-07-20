/**
 * 题目来源：luogu
 * 题目编号：P1253 扶苏的问题
 * 题目简介：线段树 + 区间修改 + 区间加 + 询问最值
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define mid (l + r >> 1)
#define ls (u << 1)
#define rs (u << 1 | 1)
const int N = 1e6 + 10;
using ll = long long;

int a[N], n, q;
ll mx[N << 2], cov[N << 2], add[N << 2];

inline void pushup(int u){
    mx[u] = max(mx[ls], mx[rs]);
}

inline void pushdown(int u){
    if(cov[u] != -1e18){ // 修改优先
        add[ls] = 0;
        add[rs] = 0; // 加需要赋0
        cov[ls] = cov[u];
        cov[rs] = cov[u];
        mx[ls] = cov[u];
        mx[rs] = cov[u];
        cov[u] = -1e18;
    }
    if(add[u]){
        add[ls] += add[u];
        add[rs] += add[u];
        mx[ls] += add[u];
        mx[rs] += add[u];
        add[u] = 0;
    }
}

void build(int u, int l, int r){
    add[u] = 0, cov[u] = -1e18;
    if(l == r){
        mx[u] = a[l];
        return;
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushup(u);
}

void range_add(int u, int l, int r, int ql, int qr, ll k){
    if(ql <= l && r <= qr){
        add[u] += k;
        mx[u] += k;
        return;
    }
    pushdown(u);
    if(ql <= mid) range_add(ls, l, mid, ql, qr, k);
    if(qr > mid) range_add(rs, mid + 1, r, ql, qr, k);
    pushup(u);
}

void range_cov(int u, int l, int r, int ql, int qr, ll k){
    if(ql <= l && r <= qr){
        add[u] = 0;
        cov[u] = k;
        mx[u] = k;
        return;
    }
    pushdown(u);
    if(ql <= mid) range_cov(ls, l, mid, ql, qr, k);
    if(qr > mid) range_cov(rs, mid + 1, r, ql, qr, k);
    pushup(u);
}

ll query_mx(int u, int l, int r, int ql, int qr){
    if(ql <= l && r <= qr) return mx[u];
    pushdown(u);
    ll res = -1e18;
    if(ql <= mid) res = max(res, query_mx(ls, l, mid, ql, qr));
    if(qr > mid) res = max(res, query_mx(rs, mid + 1, r, ql, qr));
    return res;
}

void marisa(){
    cin >> n >> q;
    for(int i = 1; i <= n; i ++ ) cin >> a[i];

    build(1, 1, n);

    for(int i = 0, op, l, r; i < q; i ++ ){
        cin >> op >> l >> r;
        if(op == 1){
            ll k; cin >> k;
            range_cov(1, 1, n, l, r, k);
        }else if(op == 2){
            ll k; cin >> k;
            range_add(1, 1, n, l, r, k);
        }else{
            cout << query_mx(1, 1, n, l, r) << "\n";
        }
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ){
        marisa();
    }

    return 0;
}