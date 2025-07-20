/**
 * 题目来源：https://www.luogu.com.cn/problem/P3388
 * 题目简介：tarjan 求割点（cut）模板
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)

struct CUT{    
    int n, num, cnt;
    vector<vector<int>> e;
    vector<int> dfn, low;
    vector<bool> cut;
    CUT() {}
    CUT(int n){
        init(n);
    }
    void init(int n){
        this -> n = n;
        num = cnt = 0;
        e.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        cut.assign(n + 1, 0);
    }
    void add_edge(int u, int v){
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    void tarjan(int u, int rt){
        dfn[u] = low[u] = ++ num;
        int son = 0;
        for(const auto& v : e[u]){
            if(!dfn[v]){
                tarjan(v, rt);
                low[u] = min(low[u], low[v]);
                if(low[v] >= dfn[u]){ // v返祖dfn序比u靠后
                    son ++ ; // u=rt, 大于一个儿子是割点
                    if(u != rt || son > 1){
                        cut[u] = true;
                    }
                }
            }else{
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    void work(){
        for(int i = 1; i <= n; i ++ ){
            if(!dfn[i]) tarjan(i, i);
        }
    }
};

void marisa(){
    int n, m; cin >> n >> m;
    CUT cut(n);
    for(int i = 1, u, v; i <= m; i ++ ){
        cin >> u >> v;
        cut.add_edge(u, v);
    }
    cut.work();
    vector<int> ans;
    for(int i = 1; i <= n; i ++ ){
        if(cut.cut[i]) ans.emplace_back(i);
    }
    cout << ans.size() << "\n";
    for(const auto& x : ans) cout << x << " ";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}