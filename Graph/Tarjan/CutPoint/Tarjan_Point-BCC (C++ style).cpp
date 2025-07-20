/**
 * 题目来源：https://www.luogu.com.cn/problem/P8435
 * 题目简介：tarjan 求点双连通分量（point-bcc）模板
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)

struct PBCC{    
    int n, num, cnt;
    vector<vector<int>> e;
    vector<int> dfn, low, id;
    vector<bool> cut;
    vector<int> st;
    vector<vector<int>> bcc; // 一个点可能属于多个bcc
    PBCC() {}
    PBCC(int n){
        init(n);
    }
    void init(int n){
        this -> n = n;
        num = cnt = 0;
        e.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        id.assign(n + 1, 0);
        cut.assign(n + 1, 0);
        st.clear();
        bcc.assign(n + 1, {});
    }
    void add_edge(int u, int v){
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    void tarjan(int u, int rt){
        dfn[u] = low[u] = ++ num;
        st.emplace_back(u);
        if(e[u].empty()){
            cnt ++ ;
            id[u] = cnt; // 孤立点特判为一个bcc
            bcc[cnt].emplace_back(u);
            return;
        }
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
                    cnt ++ ; // u 是 bcc 的顶点
                    id[u] = cnt;
                    bcc[cnt].emplace_back(u);
                    int t;
                    do{
                        t = st.back();
                        st.pop_back();
                        id[t] = cnt;
                        bcc[cnt].emplace_back(t);
                    }while(v != t);
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
    PBCC bcc(n);
    for(int i = 1, u, v; i <= m; i ++ ){
        cin >> u >> v;
        if(u == v) continue; // 忽略自环，避免孤立点特判出错
        bcc.add_edge(u, v);
    }
    bcc.work();
    cout << bcc.cnt << "\n";
    for(int i = 1; i <= bcc.cnt; i ++ ){
        const auto& cur = bcc.bcc[i];
        cout << cur.size() << ' ';
        for(const auto& x : cur) cout << x << ' ';
        cout << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}