/**
 * 题目来源：https://www.luogu.com.cn/problem/P3379
 * 题目简介：【模板】最近公共祖先（LCA）dfn序转st表求lca
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int N = 5e5 + 10;
int n, m, rt;
int dfn[N], num;
int f[N][21];
vector<int> e[N];
int logn[N];

void pre_log(){
    for(int i = 2; i < N; i ++ ){
        logn[i] = logn[i >> 1] + 1;
    }
}

void dfs(int u, int fa){
    dfn[u] = ++ num;
    f[dfn[u]][0] = fa;
    for(const auto& v : e[u]){
        if(v == fa) continue;
        dfs(v, u);
    }
}

inline int get_mn(int x, int y){
    return dfn[x] < dfn[y] ? x : y;
}

int lca(int u, int v){
    if(u == v) return u;
    u = dfn[u], v = dfn[v];
    if(u > v) swap(u, v); // v - u 为两点距离
    int k = logn[v - u];
    return get_mn(f[u + 1][k], f[v - (1 << k) + 1][k]);
}

void marisa(){
    cin >> n >> m >> rt;
    for(int i = 1, u, v; i < n; i ++ ){
        cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    dfs(rt, 0);
    for(int j = 1; j < 21; j ++ ){
        for(int i = 1; i + (1 << j) - 1 <= n; i ++ ){
            f[i][j] = get_mn(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
    for(int i = 1, x, y; i <= m; i ++ ){
        cin >> x >> y;
        cout << lca(x, y) << "\n";
    }
}

int main(){
    fastio;

    pre_log();

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}