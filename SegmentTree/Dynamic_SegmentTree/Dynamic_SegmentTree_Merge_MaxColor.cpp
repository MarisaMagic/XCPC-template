/**
 * 题目来源：https://codeforces.com/contest/600/problem/E
 * 题目简介：询问子树u中最多颜色的编号之和，一个子树可能有多个最多颜色的编号
 * 动态开点权值线段树合并，维护子树最多颜色数量以及最多颜色编号之和
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int N = 1e5 + 5, M = 1e5;
#define ls (lson[u])
#define rs (rson[u])
#define mid (l + r >> 1)
int tot, rt[N * 20], lson[N * 20], rson[N * 20];
ll sum[N * 20]; // 最多数量对应所有颜色编号之和
int mx[N * 20]; // 最多颜色数量

inline void pushup(int u){
    if(mx[ls] == mx[rs]){
        mx[u] = mx[ls];
        sum[u] = sum[ls] + sum[rs];
    }else if(mx[ls] > mx[rs]){
        mx[u] = mx[ls];
        sum[u] = sum[ls];
    }else{
        mx[u] = mx[rs];
        sum[u] = sum[rs];
    }
}

void node_add(int& u, int l, int r, int k, int x){
    if(!u) u = ++ tot;
    if(l == r){
        mx[u] += x;
        sum[u] = k;
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
        sum[u] = l;
        return u;
    }
    lson[u] = merge(lson[u], lson[v], l, mid);
    rson[u] = merge(rson[u], rson[v], mid + 1, r);
    pushup(u);
    return u;
}

void marisa(){
    int n; cin >> n;
    vector<int> c(n + 1);
    for(int i = 1; i <= n; i ++ ) cin >> c[i];
    vector<vector<int>> e(n + 1);
    for(int i = 1, u, v; i < n; i ++ ){
        cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    vector<ll> ans(n + 1);
    function<void(int, int)> dfs = [&](int u, int fa){
        node_add(rt[u], 1, n, c[u], 1);
        for(const auto& v : e[u]){
            if(v == fa) continue;
            dfs(v, u);
            rt[u] = merge(rt[u], rt[v], 1, n);
        }
        ans[u] = sum[rt[u]];
    };
    dfs(1, 0);

    for(int i = 1; i <= n; i ++ ){
        cout << ans[i] << ' ';
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}