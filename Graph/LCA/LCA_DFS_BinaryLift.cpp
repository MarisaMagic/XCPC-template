/**
 * 题目来源：https://www.luogu.com.cn/problem/P3379
 * 题目简介：【模板】最近公共祖先（LCA）
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using pii = pair<int, int>;
const int N = 5e5 + 5;

int n, q, rt; 
vector<pii> e[N];
int f[N][22], dep[N], dist[N];

void dfs(int u, int fa){
    f[u][0] = fa, dep[u] = dep[fa] + 1;
    for(int k = 1; k <= 20; k ++ ){
        f[u][k] = f[f[u][k - 1]][k - 1];
    }
    for(const auto& [v, w] : e[u]){
        if(v == fa) continue;
        dist[v] = dist[u] + w;
        dfs(v, u);
    }
}

int lca(int x, int y){
    if(dep[x] < dep[y]) swap(x, y);
    for(int k = 20; k >= 0; k -- ){
        if(dep[f[x][k]] >= dep[y]){ // 跳到和y同一个高度
            x = f[x][k]; 
        }
    }
    if(x == y) return x;
    for(int k = 20; k >= 0; k -- ){
        if(f[x][k] != f[y][k]){ // 跳到最上面不相同的位置
            x = f[x][k], y = f[y][k];
        }
    }
    return f[x][0]; // 往上一步就是lca
}

inline int get_dist(int x, int y){
    return dist[x] + dist[y] - 2 * dist[lca(x, y)];
}

void marisa(){
    cin >> n >> q >> rt;
    for(int i = 1, u, v; i < n; i ++ ){
        cin >> u >> v;
        e[u].emplace_back(v, 1);
        e[v].emplace_back(u, 1);
    }
    dfs(rt, 0);
    for(int i = 1, x, y; i <= q; i ++ ){
        cin >> x >> y;
        cout << lca(x, y) << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();

    return 0;
}