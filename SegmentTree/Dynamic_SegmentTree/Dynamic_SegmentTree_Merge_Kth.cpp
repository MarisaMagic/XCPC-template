/**
 * 题目来源：https://www.luogu.com.cn/problem/P3224
 * 题目简介：两种操作，添加一条边 和 询问一个点可达的权重第k小点
 * 并查集 + 线段树合并，线段树上二分找权重第k小点
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
int tot, rt[N * 30], lson[N * 30], rson[N * 30];
int sum[N * 30];

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

int query_kth(int u, int l, int r, int k){ 
    if(!u) return -1;
    if(l == r) return l;
    if(k <= sum[ls]) return query_kth(ls, l, mid, k);
    return query_kth(rs, mid + 1, r, k - sum[ls]);
}

int fa[N];
int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void marisa(){
    int n, m; cin >> n >> m;
    vector<int> mp(n + 1);
    for(int i = 1, x; i <= n; i ++ ){
        cin >> x;
        mp[x] = i;
        node_add(rt[i], 1, M, x, 1);
    }
    for(int i = 1; i <= n; i ++ ) fa[i] = i;
    for(int i = 1, u, v; i <= m; i ++ ){
        cin >> u >> v;
        u = find(u), v = find(v);
        if(u != v){
            if(sum[rt[u]] < sum[rt[v]]) swap(u, v); // 合并到较大的
            rt[u] = merge(rt[u], rt[v], 1, M);
            fa[v] = u;
        }
    }
    int q; cin >> q;
    for(int i = 1; i <= q; i ++ ){
        char op; cin >> op;
        if(op == 'B'){
            int u, v; cin >> u >> v;
            u = find(u), v = find(v);
            if(u != v){
                if(sum[rt[u]] < sum[rt[v]]) swap(u, v); // 合并到较大的
                rt[u] = merge(rt[u], rt[v], 1, M); // 将两个集合合并
                fa[v] = u;
            }
        }else{
            int x, k; cin >> x >> k;
            x = find(x);
            int res = query_kth(rt[x], 1, M, k);
            cout << (res != -1 ? mp[res] : -1) << "\n";
        }
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}