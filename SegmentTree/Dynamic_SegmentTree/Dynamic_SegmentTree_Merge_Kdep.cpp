/**
 * 题目来源：https://codeforces.com/contest/208/problem/E
 * 题目简介：a 为 b 向上的 k 级祖先，询问 b 有多少个表亲有共同的 k 级祖先 a
 * 树上倍增找到每个节点向上k步的祖先，预处理得到每个点向下k步的所有儿子
 * 以层级为权值，动态开点线段树合并，dfs过程中合并 + 离线处理询问
 * 也可以求出每个节点向下 k 步的节点数量 或者 向下 k_1 ~ k_2 步的节点数量
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
int sum[N * 20];

inline void pushup(int u){
    sum[u] = sum[ls] + sum[rs];
}

void node_add(int& u, int l, int r, int k, int x){
    if(!u) u = ++ tot;
    if(l == r){
        sum[u] += x;
        return;
    }
    if(k <= mid) node_add(ls, l, mid, k, x);
    else node_add(rs, mid + 1, r, k, x);
    pushup(u);
}

int query_node(int u, int l, int r, int k){
    if(!u) return 0;
    if(l == r) return sum[u];
    if(k <= mid) return query_node(ls, l, mid, k);
    else return query_node(rs, mid + 1, r, k);
}

int merge(int u, int v, int l, int r){ // 线段树合并
    if(!u) return v;
    if(!v) return u;
    if(l == r){
        sum[u] += sum[v];
        return u;
    }
    lson[u] = merge(lson[u], lson[v], l, mid);
    rson[u] = merge(rson[u], rson[v], mid + 1, r);
    pushup(u);
    return u;
}

void marisa(){
    int n; cin >> n;
    vector<bool> is_rt(n + 1);
    vector<vector<int>> e(n + 1);
    for(int i = 1, r; i <= n; i ++ ){
        cin >> r;
        if(r) e[r].emplace_back(i);
        else{
            is_rt[i] = true;
        }
    }

    vector<int> dep(n + 1);
    vector<array<int, 21>> f(n + 1);
    function<void(int, int)> dfs = [&](int u, int fa){
        dep[u] = dep[fa] + 1;
        f[u][0] = fa;
        for(int k = 1; k <= 20; k ++ ){
            f[u][k] = f[f[u][k - 1]][k - 1];
        }
        for(const auto& v : e[u]){
            if(v == fa) continue;
            dfs(v, u);
        }
    };
    for(int i = 1; i <= n; i ++ ){
        if(is_rt[i]) dfs(i, 0);
    }

    auto find_k = [&](int u, int x){
        int sum = 0;
        for(int k = 20; ~k; k -- ){
            if(f[u][k] && sum + (1 << k) < x){
                u = f[u][k];
                sum += (1 << k);
            }
        }
        return f[u][0];
    };

    int q; cin >> q;
    vector<vector<pii>> qs(n + 1);
    for(int i = 1, v, k; i <= q; i ++ ){
        cin >> v >> k;
        int u = find_k(v, k);
        if(u) qs[u].emplace_back(k, i);
    }

    vector<int> ans(q + 1);
    function<void(int)> dfs2 = [&](int u){
        node_add(rt[u], 1, n, dep[u], 1);
        for(const auto& v : e[u]){
            if(v == f[u][0]) continue;
            dfs2(v);
            rt[u] = merge(rt[u], rt[v], 1, n);
        }
        for(const auto& [k, id] : qs[u]){
            ans[id] = query_node(rt[u], 1, n, dep[u] + k) - 1;
        }
    };
    for(int i = 1; i <= n; i ++ ){
        if(is_rt[i]) dfs2(i);
    }

    for(int i = 1; i <= q; i ++ ){
        cout << ans[i] << " \n"[i == q];
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}