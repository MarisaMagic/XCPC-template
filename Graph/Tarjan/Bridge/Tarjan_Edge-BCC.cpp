/**
 * 题目来源：https://www.luogu.com.cn/problem/P8436
 * 题目简介：tarjan 求 edge-bcc（边双连通分量）模板
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pii = pair<int, int>;
const int N = 5e5 + 10, M = 2e6 + 10;

int n, m;
vector<pii> e[N];
int low[N], dfn[N], num;
bool bridge[M];
int st[N], top;
int bcc_id[N], bcc_cnt;
vector<int> bcc[N];

void tarjan(int u, int in_edge){
    low[u] = dfn[u] = ++ num;
    st[ ++ top] = u;
    for(const auto& [v, id] : e[u]){
        if(!dfn[v]){
            tarjan(v, id);
            low[u] = min(low[u], low[v]);
            if(low[v] > dfn[u]){ // v返祖dfn序在u之后才会遍历到
                bridge[id] = true; // 表明这个边是割边
            }
        }else if(id != in_edge){ // 遍历过但不是同一条边，更新
            low[u] = min(low[u], dfn[v]);
        }
    }

    if(low[u] == dfn[u]){ // bcc 的一个顶点
        bcc_cnt ++ ;
        int v;
        do{
            v = st[top -- ];
            bcc_id[v] = bcc_cnt;
            bcc[bcc_cnt].emplace_back(v);
        }while(u != v);
    }
}

void marisa(){
    cin >> n >> m;
    for(int i = 1, u, v; i <= m; i ++ ){
        cin >> u >> v;
        e[u].emplace_back(v, i);
        e[v].emplace_back(u, i);
    }
    for(int i = 1; i <= n; i ++ )
        if(!dfn[i]) tarjan(i, 0);
    cout << bcc_cnt << "\n";
    for(int i = 1; i <= bcc_cnt; i ++ ){
        cout << bcc[i].size() << ' ';
        for(const auto& x : bcc[i]) cout << x << ' ';
        cout << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}