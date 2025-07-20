/**
 * 题目来源：https://codeforces.com/problemset/problem/786/B
 * 题目简介：线段树优化建图 + dijkstra
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int N = 3e6 + 10, K = 5e5;
int h[N], e[N], ne[N], w[N], idx;
int n, m, src;

inline void add(int a, int b, int c){
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++ ;
}

#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid (l + r >> 1)
int id[N], a[N], tot; // a[i] 为单点 i 的编号

void build(int u, int l, int r){
    id[u] = ++ tot;
    if(l == r){
        a[l] = id[u];
        return;
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    // 出树
    add(id[u], id[ls], 0);
    add(id[u], id[rs], 0); 
    // 入树
    add(id[ls] + K, id[u] + K, 0);
    add(id[rs] + K, id[u] + K, 0);
}

// op = 2, 入树的节点 p 连 出树 [ql, qr] 的log个点
// op = 3, 入树的 [ql, qr] 的 log 个点 连 出树的节点 p
void range_add(int u, int l, int r, int ql, int qr, int op, int p, int w){
    if(ql <= l && r <= qr){
        if(op == 2){
            add(p + K, id[u], w);
        }else if(op == 3){
            add(id[u] + K, p, w);
        }
        return;
    }
    if(ql <= mid) range_add(ls, l, mid, ql, qr, op, p, w);
    if(qr > mid) range_add(rs, mid + 1, r, ql, qr, op, p, w);
}

const ll inf = 1e18;
ll dist[N];
bool vis[N];

void dijkstra(int src){
    for(int i = 0; i < N; i ++ ) dist[i] = 1e18;
    priority_queue<pll, vector<pll>, greater<pll>> q;
    q.emplace(dist[src] = 0, src);
    while(q.size()){
        auto [d, u] = q.top();
        q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(int i = h[u]; ~i; i = ne[i]){
            int v = e[i], c = w[i];
            if(dist[v] > d + c){
                q.emplace(dist[v] = d + c, v);
            }
        }
    }
}

void marisa(){
    cin >> n >> m >> src;
    memset(h, -1, sizeof h);

    build(1, 1, n);

    for(int i = 1; i <= n; i ++ ){
        add(a[i], a[i] + K, 0);
        add(a[i] + K, a[i], 0);
    }

    for(int i = 1; i <= m; i ++ ){
        int op; cin >> op;
        if(op == 1){
            int u, v, w; cin >> u >> v >> w;
            add(a[u] + K, a[v], w); // 节点 u -> v
        }else{
            // op=2, u 到区间 [l,r] 所有点连边
            // op=3, 区间 [l,r] 所有点 到 u 连边
            int u, l, r, w; cin >> u >> l >> r >> w;
            range_add(1, 1, n, l, r, op, a[u], w);
        }
    }

    dijkstra(a[src] + K);

    for(int i = 1; i <= n; i ++ ){
        ll res = dist[a[i]];
        cout << (res == inf ? -1 : res) << ' ';
    }
    cout << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}