/**
 * 题目来源：https://www.luogu.com.cn/problem/P3379
 * 题目简介：【模板】最近公共祖先（LCA）
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using pii = pair<int, int>;
const int N = 5e5 + 5;


struct LCA {
    int n;
    vector<int> dep;
    vector<vector<int>> e;
    vector<array<int, 21>> f;
    LCA() {}
    LCA(int n){
        init(n);
    }
    void init(int n){
        this -> n = n;
        dep.resize(n + 1);
        e.resize(n + 1);
        f.resize(n + 1);
    }
    void add_edge(int u, int v){
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    void dfs(int u, int fa){
        dep[u] = dep[fa] + 1;
        f[u][0] = fa;
        for(int k = 1; k <= 20; k ++ ){
            f[u][k] = f[f[u][k - 1]][k - 1];
        }
        for(const auto& v : e[u]){
            if(v == fa) continue;
            dfs(v, u);
        } 
    }
    int lca(int u, int v){
        if(dep[u] < dep[v]) swap(u, v);
        for(int k = 20; k >= 0; k -- ){
            if(dep[f[u][k]] >= dep[v]){
                u = f[u][k];
            }
        }
        if(u == v) return u;
        for(int k = 20; k >= 0; k -- ){
            if(f[u][k] != f[v][k]){
                u = f[u][k], v = f[v][k];
            }
        }
        return f[u][0];
    }
    int get_dist(int u, int v){
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    int get_fa(int u, int x){ // u 向上 x 步的祖先
        int sum = 0;
        for(int k = 20; ~k; k -- ){
            if(sum + (1 << k) <= x){
                u = f[u][k];
                sum += (1 << k);
            }
        }
        return u;
    }
};

void marisa(){
    int n, q, rt; cin >> n >> q >> rt;
    LCA lca(n);
    for(int i = 1, u, v; i < n; i ++ ){
        cin >> u >> v;
        lca.add_edge(u, v);
    }
    lca.dfs(rt, 0);
    for(int i = 1, x, y; i <= q; i ++ ){
        cin >> x >> y;
        cout << lca.lca(x, y) << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();

    return 0;
}