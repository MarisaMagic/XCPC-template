/**
 * 题目来源：https://www.luogu.com.cn/problem/P10463
 * 题目简介：区间GCD + 区间修改
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid (l + r >> 1)

const int N = 5e5 + 10;

ll a[N], b[N], n, q;
ll sum[N << 2], g[N << 2];
// 由更相减损术 gcd(x,y)=gcd(x,y-x)
// 拓展得到 gcd_{l,r}=gcd(a_l, a_{l+1}-a_l, ... , a_r-a_{r-1})
// 令差分数组 d[i] = a[i] - a[i-1]
// 故 gcd_{l,r}=gcd(a_l, gcd(d[l+1], ... , d[r]))
// 其中 a_l = sum_{i=1}^{l} d[i]（线段树求区间和）
// gcd(d[l+1], ... , d[r])（线段树直接求区间GCD）
// 区间加x，利用差分思想单点修改 d[l] += x, d[r+1] -= x

inline void pushup(int u){
    sum[u] = sum[ls] + sum[rs];
    g[u] = gcd(g[ls], g[rs]);
}

void build(int u, int l, int r){
    if(l == r){
        sum[u] = b[l];
        g[u] = b[l];
        return;
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushup(u);
}   

ll query_sum(int u, int l, int r, int ql, int qr){
    if(ql <= l && r <= qr) return sum[u];
    ll res = 0;
    if(ql <= mid) res += query_sum(ls, l, mid, ql, qr);
    if(qr > mid) res += query_sum(rs, mid + 1, r, ql, qr);
    return res;
}

ll query_gcd(int u, int l, int r, int ql, int qr){
    if(ql <= l && r <= qr) return g[u];
    ll res = 0;
    if(ql <= mid) res = gcd(res, query_gcd(ls, l, mid, ql, qr));
    if(qr > mid) res = gcd(res, query_gcd(rs, mid + 1, r, ql, qr));
    return res;
}

void node_add(int u, int l, int r, int k, ll d){
    if(l == r){
        sum[u] += d;
        g[u] += d;
        return;
    }
    if(k <= mid) node_add(ls, l, mid, k, d);
    else node_add(rs, mid + 1, r, k, d);
    pushup(u);
}

void marisa(){
    cin >> n >> q;
    for(int i = 1; i <= n; i ++ ){
        cin >> a[i];
        b[i] = a[i] - a[i - 1];
    }

    build(1, 1, n);

    for(int i = 0, l, r; i < q; i ++ ){
        char op; cin >> op >> l >> r;
        if(op == 'Q'){  
            // d[1]+...+d[l]: a[l]
            ll a_l = query_sum(1, 1, n, 1, l); 
            // gcd(d[l+1],...,d[r]): gcd(a[l+1]-a[l],...,a[r]-a[r-1])
            ll g_r = query_gcd(1, 1, n, l + 1, r); 
            cout << abs(gcd(a_l, g_r)) << "\n";
        }else{
            ll d; cin >> d;
            node_add(1, 1, n, l, d); // d[l]++
            if(r < n) node_add(1, 1, n, r + 1, -d); // d[r+1]--
        }
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}