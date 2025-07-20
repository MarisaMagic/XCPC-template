/**
 * 题目来源：https://www.luogu.com.cn/problem/T103481
 * 题目简介：tarjan 求割边（bridge）模板
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)

struct BRIDGE{
    using pii = pair<int, int>;
    int n, m, num, cnt;
    vector<vector<pii>> e;
    vector<int> dfn, low;
    vector<bool> bridge;
    BRIDGE() {}
    BRIDGE(int n, int m){
        init(n, m);
    }
    void init(int n, int m){
        this -> n = n;
        this -> m = m;
        num = cnt = 0;
        e.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        bridge.assign(m + 1, 0);
    }
    void add_edge(int u, int v, int eid){
        e[u].emplace_back(v, eid);
        e[v].emplace_back(u, eid);
    }
    void tarjan(int u, int pre_eid){
        dfn[u] = low[u] = ++ num;
        for(const auto& [v, eid] : e[u]){
            if(!dfn[v]){
                tarjan(v, eid);
                low[u] = min(low[u], low[v]);
                if(low[v] > dfn[u]){ // v返祖dfn序在u之后
                    bridge[eid] = true; // 说明为割边
                }
            }else if(eid != pre_eid){ // 遍历过但不是同一条边
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    void work(){
        for(int i = 1; i <= n; i ++ ){
            if(!dfn[i]) tarjan(i, 0);
        }
    }
};

void marisa(){
    int n, m; cin >> n >> m;
    BRIDGE bridges(n, m);
    for(int i = 1, u, v; i <= m; i ++ ){
        cin >> u >> v;
        bridges.add_edge(u, v, i);
    }
    bridges.work();
    int ans = 0;
    for(int i = 1; i <= m; i ++ ){
        ans += bridges.bridge[i];
    }
    cout << ans << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}