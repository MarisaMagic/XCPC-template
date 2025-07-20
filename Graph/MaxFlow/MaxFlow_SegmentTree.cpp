/**
 * 题目来源：https://ac.nowcoder.com/acm/problem/20951
 * 题目简介：线段树优化建图 + 最大流
 * 共有n名用户，编号从1到n，服务器共有m条服务线。
 * 每个用户最多只能登陆一条线，第i条线最多可以容纳 v_i 名用户同时在线，
 * 且只能给编号在 [l_i, r_i] 范围内的用户提供服务。求最大同时在线人数
 * 线段树优化 + 最大流，源点连单点，每个区间的log个点连区间虚点，虚点连汇点
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int N = 1e5 + 10, M = 2e6 + 10;
const ll inf = 1e18;
int h[N], e[M], ne[M], idx; // 链式前向星
int n, m, src, des;
ll cap[M]; // 边的容量

inline void add(int u, int v, ll c){
    e[idx] = v, ne[idx] = h[u], cap[idx] = c, h[u] = idx ++ ;
    e[idx] = u, ne[idx] = h[v], cap[idx] = 0, h[v] = idx ++ ;
}

int d[N], cur[M]; // d: 点的层次 cur: 当前弧

bool bfs(){
    memset(d, -1, sizeof d);
    queue<int> q;
    q.emplace(src);
    d[src] = 0;
    cur[src] = h[src];
    while(q.size()){
        int u = q.front();
        q.pop();
        for(int i = h[u]; ~i; i = ne[i]){
            int v = e[i];
            ll c = cap[i];
            if(c > 0 && d[v] == -1){
                q.emplace(v);
                d[v] = d[u] + 1;
                cur[v] = h[v];
                if(v == des) return true;
            }
        }
    }
    return false;
}

ll dfs(int u, ll f){
    if(u == des) return f;
    ll used = 0; // 记录当前使用的流量
    for(int i = cur[u]; ~i && used < f; i = ne[i]){
        cur[u] = i; // 当前弧优化
        int v = e[i];
        ll c = cap[i];
        if(c > 0 && d[v] == d[u] + 1){
            ll t = dfs(v, min(f - used, c)); // 剩余流量递归寻找增广路
            cap[i] -= t; // 更新边的容量
            cap[i ^ 1] += t;
            used += t; // 更新使用的流量
        }
    }
    return used; // 当前增广路使用的流量
}

ll dinic(){
    ll res = 0;
    while(bfs()){
        res += dfs(src, inf);
    }
    return res;
}

#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid (l + r >> 1)
int id[N << 2], tot; // 线段树每个点的编号

void build(int u, int l, int r){
    id[u] = ++ tot;
    if(l == r){
        add(0, id[u], 1); // 源点连接每个单点
        return;
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    add(id[ls], id[u], mid - l + 1);
    add(id[rs], id[u], r - mid);
}

// 代表区间 [ql, qr] 的 logn 个点 连接 当前的虚点 p
void range_add(int u, int l, int r, int ql, int qr, int p){
    if(ql <= l && r <= qr){
        add(id[u], p, r - l + 1);
        return;
    }
    if(ql <= mid) range_add(ls, l, mid, ql, qr, p);
    if(qr > mid) range_add(rs, mid + 1, r, ql, qr, p);
}

void marisa(){
    while(cin >> n >> m){
        //cin >> n >> m;
        tot = idx = 0;
        memset(h, -1, sizeof h);
        // memset(cur, 0, sizeof cur);
        build(1, 1, n);
        src = 0, des = tot + m + 1;
        for(int i = 1, l, r, v; i <= m; i ++ ){
            cin >> l >> r >> v;
            range_add(1, 1, n, l, r, tot + i);
            add(tot + i, des, v);
        }
        cout << dinic() << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}