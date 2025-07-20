/**
 * 题目来源：luogu
 * 题目编号：P3373 【模板】线段树 2
 * 题目简介：线段树区间乘 + 区间加 + 区间和
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define mid (l + r >> 1)
#define ls (u << 1)
#define rs (u << 1 | 1)
const int N = 1e5 + 10;
using ll = long long;

int n, q;
ll mod;
ll a[N], sum[N << 2], add[N << 2], mul[N << 2];

inline void pushup(int u){
    sum[u] = (sum[ls] + sum[rs]) % mod;
}

inline void pushdown(int u, int l, int r){
    if(mul[u] != 1){ // 乘法优先
        mul[ls] = (mul[ls] * mul[u]) % mod;
        mul[rs] = (mul[rs] * mul[u]) % mod;
        add[ls] = (add[ls] * mul[u]) % mod;
        add[rs] = (add[rs] * mul[u]) % mod;
        sum[ls] = (sum[ls] * mul[u]) % mod;
        sum[rs] = (sum[rs] * mul[u]) % mod;
        mul[u] = 1;
    }
    if(add[u]){
        add[ls] = (add[ls] + add[u]) % mod;
        add[rs] = (add[rs] + add[u]) % mod;
        sum[ls] = (sum[ls] + add[u] * (mid - l + 1) % mod) % mod;
        sum[rs] = (sum[rs] + add[u] * (r - mid) % mod) % mod;
        add[u] = 0;
    }
}

void build(int u, int l, int r){
    add[u] = 0, mul[u] = 1;
    if(l == r){
        sum[u] = a[l] % mod;
        return;
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushup(u);
}

void range_add(int u, int l, int r, int ql, int qr, ll x){
    if(ql <= l && r <= qr){
        add[u] = (add[u] + x) % mod;
        sum[u] = (sum[u] + x * (r - l + 1) % mod) % mod;
        return;
    }
    pushdown(u, l, r);
    if(ql <= mid) range_add(ls, l, mid, ql, qr, x);
    if(qr > mid) range_add(rs, mid + 1, r, ql, qr, x);
    pushup(u);
}

void range_mul(int u, int l, int r, int ql, int qr, ll x){
    if(ql <= l && r <= qr){
        mul[u] = (mul[u] * x) % mod;
        add[u] = (add[u] * x) % mod;
        sum[u] = (sum[u] * x) % mod;
        return;
    }
    pushdown(u, l, r);
    if(ql <= mid) range_mul(ls, l, mid, ql, qr, x);
    if(qr > mid) range_mul(rs, mid + 1, r, ql, qr, x);
    pushup(u);
}

ll query_range(int u, int l, int r, int ql, int qr){
    if(ql <= l && r <= qr) return sum[u];
    pushdown(u, l, r);
    ll res = 0;
    if(ql <= mid) res = (res + query_range(ls, l, mid, ql, qr)) % mod;
    if(qr > mid) res = (res + query_range(rs, mid + 1, r, ql, qr)) % mod;
    return res;
}

void marisa(){
    cin >> n >> q >> mod;
    for(int i = 1; i <= n; i ++ ) cin >> a[i];

    build(1, 1, n);

    for(int i = 0, op, l, r; i < q; i ++ ){
        cin >> op >> l >> r;
        if(op == 1){
            ll x; cin >> x;
            range_mul(1, 1, n, l, r, x);
        }else if(op == 2){
            ll x; cin >> x;
            range_add(1, 1, n, l, r, x);
        }else{
            cout << query_range(1, 1, n, l, r) << "\n";
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