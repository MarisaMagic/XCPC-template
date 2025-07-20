/**
 * 题目来源：https://www.luogu.com.cn/problem/P3387
 * 题目简介：scc 缩点求拓扑图，topo排序 + dp求最大路径权值和
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
const int N = 1e4 + 10;
using ll = long long;

// ------ scc 缩点求拓扑图 ------
int n, m;
vector<int> e[N];
int low[N], dfn[N], num;
int st[N], top;
bool in_st[N];
int id[N], scc_cnt;
ll scc_val[N], a[N];

void tarjan(int u){
    low[u] = dfn[u] = ++ num;
    st[ ++ top] = u, in_st[u] = true;
    for(const auto& v : e[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }else if(in_st[v]){
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]){
        scc_cnt ++ ;
        int v;
        do{
            v = st[top -- ], in_st[v] = false;
            id[v] = scc_cnt;
            scc_val[scc_cnt] += a[v];
        }while(u != v);
    }
}

// ------ topo + dp ------
vector<int> g[N];
int ind[N];
ll dp[N]; // dp[u]: 以u结尾的路径的最大权值和

ll topo(){
    ll ans = 0;
    queue<int> q;
    for(int i = 1; i <= scc_cnt; i ++ ) if(!ind[i]){
        dp[i] = scc_val[i];
        q.emplace(i);
    }
    while(q.size()){
        int u = q.front();
        q.pop();
        ans = max(ans, dp[u]);
        for(const auto& v : g[u]){
            dp[v] = max(dp[v], dp[u] + scc_val[v]);
            if(!( -- ind[v])) q.emplace(v);
        }
    }
    return ans;
}

void marisa(){
    cin >> n >> m;
    for(int i = 1; i <= n; i ++ ) cin >> a[i];
    for(int i = 1, u, v; i <= m; i ++ ){
        cin >> u >> v;
        e[u].emplace_back(v);
    }
    // tarjan 求出所有 scc
    for(int i = 1; i <= n; i ++ ) if(!dfn[i]) tarjan(i);
    // 构建拓扑图
    for(int u = 1; u <= n; u ++ )
        for(const auto& v : e[u])
            if(id[u] != id[v]){
                g[id[u]].emplace_back(id[v]);
                ind[id[v]] ++ ;
            }
    // 拓扑排序 + dp 求最大路径权值和
    cout << topo() << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}