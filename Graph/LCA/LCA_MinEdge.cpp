/**
 * 题目来源：https://www.luogu.com.cn/problem/P1967
 * 题目简介：kruskal重构树，倍增 LCA 求树上两点之间最小边
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

const int N = 1e4 + 10, M = 5e4 + 10;

int n, m; 
struct node{
    int u, v, w;
    bool operator< (const node& o) const {
        return w > o.w;
    }
}edges[M];

int fa[N];
int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

using pii = pair<int, int>;
vector<pii> e[N];
int f[N][21], mn[N][21]; // mn[u][k]: u -> 向上 2^k-1 到达点的最小边
int dep[N]; 

void dfs(int u, int fa, int pre_w){
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    mn[u][0] = pre_w;
    for(int k = 1; k < 21; k ++ ){
        f[u][k] = f[f[u][k - 1]][k - 1]; // 倍增
        mn[u][k] = min(mn[u][k - 1], mn[f[u][k - 1]][k - 1]);
    }
    for(const auto& [v, w] : e[u]){
        if(v == fa) continue;
        dfs(v, u, w);
    }
}

int lca(int u, int v){
    if(find(u) != find(v)) return -1; // 无法到达
    if(dep[u] < dep[v]) swap(u, v);
    int res = 1e9; // 借助倍增求树上两点之间的最小边
    for(int k = 20; k >= 0; k -- ){
        if(dep[f[u][k]] >= dep[v]){
            res = min(res, mn[u][k]);
            u = f[u][k];
        }
    }
    if(u == v) return res;
    for(int k = 20; k >= 0; k -- ){
        if(f[u][k] != f[v][k]){
            res = min(res, mn[u][k]);
            res = min(res, mn[v][k]);
            u = f[u][k];
            v = f[v][k];
        }
    }
    res = min(res, mn[u][0]);
    res = min(res, mn[v][0]);
    return res;
}

void marisa(){
    cin >> n >> m;
    for(int i = 1, u, v, w; i <= m; i ++ ){
        cin >> u >> v >> w;
        edges[i] = node{u, v, w};
    }
    // kruskal 构建最大边连通树
    sort(edges + 1, edges + m + 1);
    for(int i = 1; i <= n; i ++ ) fa[i] = i;
    for(int i = 1; i <= m; i ++ ){
        const auto& [u, v, w] = edges[i];
        int fx = find(u), fy = find(v);
        if(fx == fy) continue;
        fa[fx] = fy;
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }

    for(int i = 1; i <= n; i ++ ){
        if(!dep[i]) dfs(i, 0, 1e9);
    }

    int q; cin >> q;
    for(int i = 1, u, v; i <= q; i ++ ){
        cin >> u >> v;
        cout << lca(u, v) << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}