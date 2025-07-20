/**
 * 题目来源：atcoder
 * 题目编号：https://atcoder.jp/contests/practice2/tasks/practice2_j
 * 题目简介：线段树 + 单点修改 + 区间询问 + 树上二分
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define mid (l + r >> 1)
#define ls (u << 1)
#define rs (u << 1 | 1)
const int N = 2e5 + 10;

int n, q, a[N];
int mx[N << 2];

inline void pushup(int u){
    mx[u] = max(mx[ls], mx[rs]);
}

void build(int u, int l, int r){
    if(l == r){
        mx[u] = a[l];
        return;
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushup(u);
}

void node_cov(int u, int l, int r, int k, int x){
    if(l == r){
        mx[u] = x;
        return;
    }
    if(k <= mid) node_cov(ls, l, mid, k, x);
    else node_cov(rs, mid + 1, r, k, x);
    pushup(u);
}

int query_mx(int u, int l, int r, int ql, int qr){
    if(ql <= l && r <= qr) return mx[u];
    int res = -1e9;
    if(ql <= mid) res = query_mx(ls, l, mid, ql, qr);
    if(qr > mid) res = max(res, query_mx(rs, mid + 1, r, ql, qr));
    return res;
}

// 找到 [ql, qr] 区间内第一个大于等于 x 的下标
int first_geq(int u, int l, int r, int ql, int qr, int x){
    if(l > qr || r < ql || mx[u] < x) return -1;
    if(l == r) return l;
    int pos = first_geq(ls, l, mid, ql, qr, x);
    if(pos != -1) return pos;
    return first_geq(rs, mid + 1, r, ql, qr, x);
}

void marisa(){
    int n, q; cin >> n >> q;
    for(int i = 1; i <= n; i ++ ) cin >> a[i];

    build(1, 1, n);

    for(int i = 0, op, x, v, l, r; i < q; i ++ ){
        cin >> op;
        if(op == 1){
            cin >> x >> v;
            node_cov(1, 1, n, x, v);
        }else if(op == 2){
            cin >> l >> r;
            cout << query_mx(1, 1, n, l, r) << "\n";
        }else{
            cin >> x >> v;
            cout << first_geq(1, 1, n, x, n, v) << "\n";
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