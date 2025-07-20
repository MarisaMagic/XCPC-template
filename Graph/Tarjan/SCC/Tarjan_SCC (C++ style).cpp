/**
 * 题目来源：https://www.luogu.com.cn/problem/B3609
 * 题目简介：tarjan求scc模板题
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
const int N = 1e4 + 10;


struct SCC{
    int n, num, cnt;
    vector<vector<int>> e;
    vector<int> dfn, low, id;
    vector<int> st; 
    SCC() {}
    SCC(int n){
        init(n);
    }
    void init(int n){
        this -> n = n;
        num = cnt = 0;
        e.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        id.assign(n + 1, 0);
        st.clear();
    }
    void add_edge(int u, int v){
        e[u].emplace_back(v);
    }   
    void tarjan(int u){
        dfn[u] = low[u] = ++ num;
        st.emplace_back(u);
        for(const auto& v : e[u]){
            if(!dfn[v]){
                tarjan(v);
                low[u] = min(low[u], low[v]);
            }else if(!id[v]){ // 无id说明还在栈中
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(low[u] == dfn[u]){
            cnt ++ ;
            int v;
            do{
                v = st.back();
                st.pop_back();
                id[v] = cnt;
            }while(u != v);
        }
    }
    void work(){
        for(int i = 1; i <= n; i ++ ){
            if(!dfn[i]) tarjan(i);
        }
    }
};

void marisa(){
    int n, m; cin >> n >> m;
    SCC scc(n);
    for(int i = 1, u, v; i <= m; i ++ ){
        cin >> u >> v;
        scc.add_edge(u, v);
    }
    scc.work();
    vector<vector<int>> ans(scc.cnt + 1);
    for(int i = 1; i <= n; i ++ ){
        ans[scc.id[i]].emplace_back(i);
    }
    sort(begin(ans), end(ans));
    cout << scc.cnt << "\n";
    for(int i = 1; i <= scc.cnt; i ++ ){
        for(const auto& x : ans[i]) cout << x << ' ';
        cout << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}