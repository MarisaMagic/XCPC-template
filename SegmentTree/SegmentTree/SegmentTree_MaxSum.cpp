/**
 * 题目来源：https://www.acwing.com/problem/content/description/246/
 * 题目简介：区间最大子段和 线段树维护最大子段和
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid (l + r >> 1)
const int N = 5e5 + 5;

struct node{
    ll sum, mxs, lmx, rmx;
}tr[N << 2];
int n, m, a[N];
void pushup(node& nu, node& nl, node& nr){
    nu.sum = nl.sum + nr.sum;
    nu.lmx = max(nl.lmx, nl.sum + nr.lmx);
    nu.rmx = max(nr.rmx, nr.sum + nl.rmx);
    nu.mxs = max({nl.mxs, nr.mxs, nl.rmx + nr.lmx});
}

void build(int u, int l, int r){
    if(l == r){
        tr[u] = node{a[l], a[l], a[l], a[l]};
        return;
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushup(tr[u], tr[ls], tr[rs]);
}

node query(int u, int l, int r, int ql, int qr){
    if(ql <= l && r <= qr) return tr[u];
    if(qr <= mid) return query(ls, l, mid, ql, qr);
    if(ql > mid) return query(rs, mid + 1, r, ql, qr);
    node nl = query(ls, l, mid, ql, qr);
    node nr = query(rs, mid + 1, r, ql, qr);
    node res{};
    pushup(res, nl, nr);
    return res;
}

int query_node(int u, int l, int r, int k){
    if(l == r) return tr[u].sum;
    if(k <= mid) return query_node(ls, l, mid, k);
    else return query_node(rs, mid + 1, r, k);
}

void node_add(int u, int l, int r, int k, int x){
    if(l == r){
        tr[u] = node{x, x, x, x};
        return;
    }
    if(k <= mid) node_add(ls, l, mid, k, x);
    else node_add(rs, mid + 1, r, k, x);
    pushup(tr[u], tr[ls], tr[rs]);
}

void marisa(){
    cin >> n >> m;
    for(int i = 1; i <= n; i ++ ) cin >> a[i];

    build(1, 1, n);

    while(m -- ){
        int op; cin >> op;
        if(op == 1){
            int l, r; cin >> l >> r;
            if(l > r) swap(l, r);
            cout << query(1, 1, n, l, r).mxs << endl;
        }else{
            int k, x; cin >> k >> x;
            node_add(1, 1, n, k, x);
        }
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}