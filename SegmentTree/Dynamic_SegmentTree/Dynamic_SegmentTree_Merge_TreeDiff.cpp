/**
 * 题目来源：https://www.luogu.com.cn/problem/P4556
 * 题目简介：lca树上差分 + 动态开点线段树合并
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int N = 1e5 + 5;

int n, q; 
vector<int> e[N];
int f[N][22], dep[N];

void dfs(int u, int fa){
    f[u][0] = fa;
    dep[u] = dep[fa] + 1;
    for(int k = 1; k <= 20; k ++ ){
        f[u][k] = f[f[u][k - 1]][k - 1];
    }
    for(const auto& v : e[u]){
        if(v == fa) continue;
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

const int M = 1e5;
#define ls (lson[u])
#define rs (rson[u])
#define mid (l + r >> 1)
int tot, rt[N * 64], lson[N * 64], rson[N * 64];
int mx[N * 64], id[N * 64]; // 区间最大权值，最大权值对应编号

inline void pushup(int u){
    if(mx[rs] > mx[ls]){
        mx[u] = mx[rs];
        id[u] = id[rs];
    }else{
        mx[u] = mx[ls];
        id[u] = id[ls];
    }
}

void node_add(int& u, int l, int r, int k, int x){
    if(!u) u = ++ tot;
    if(l == r){
        mx[u] += x;
        id[u] = k;
        return;
    }
    if(k <= mid) node_add(ls, l, mid, k, x);
    else node_add(rs, mid + 1, r, k, x);
    pushup(u);
}

int merge(int u, int v, int l, int r){ // 线段树合并
    if(!u) return v;
    if(!v) return u;
    if(l == r){
        mx[u] += mx[v];
        return u;
    }
    lson[u] = merge(lson[u], lson[v], l, mid);
    rson[u] = merge(rson[u], rson[v], mid + 1, r);
    pushup(u);
    return u;
}

int ans[N];
void dfs1(int u){
    for(const auto& v : e[u]){
        if(v == f[u][0]) continue;
        dfs1(v);
        rt[u] = merge(rt[u], rt[v], 1, M); // 合并每个儿子
    }
    if(mx[rt[u]]) ans[u] = id[rt[u]];
}

void marisa(){
    cin >> n >> q;
    for(int i = 1, u, v; i < n; i ++ ){
        cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    dfs(1, 0);

    for(int i = 1, x, y, z; i <= q; i ++ ){
        cin >> x >> y >> z; // 树上差分
        node_add(rt[x], 1, M, z, 1);
        node_add(rt[y], 1, M, z, 1);
        int anc = lca(x, y);
        node_add(rt[anc], 1, M, z, -1);
        node_add(rt[f[anc][0]], 1, M, z, -1);
    }
    dfs1(1); // 动态开点线段树合并

    for(int i = 1; i <= n; i ++ ){
        cout << ans[i] << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}