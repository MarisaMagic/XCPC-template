/**
 * 题目来源：https://www.luogu.com.cn/problem/B3609
 * 题目简介：tarjan求scc模板题
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
const int N = 1e4 + 10;

int n, m;
vector<int> e[N];
int low[N], dfn[N], num; // low_u: u可以回溯到的最小 dfn 序
int id[N], scc_cnt; // 每个点所属scc
vector<int> scc[N]; // scc中的点
int st[N], top; // 栈
bool in_st[N];  // 是否在栈中

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
    if(low[u] == dfn[u]){ // 一个 scc 的顶点
        scc_cnt ++ ;
        int v;
        do{
            v = st[top -- ], in_st[v] = false;
            id[v] = scc_cnt;
            scc[scc_cnt].emplace_back(v);
        }while(u != v);
    }
}

void marisa(){
    cin >> n >> m;
    for(int i = 0, u, v; i < m; i ++ ){
        cin >> u >> v;
        e[u].emplace_back(v);
    }
    for(int i = 1; i <= n; i ++ )
        if(!dfn[i]) tarjan(i);
    cout << scc_cnt << "\n";
    for(int i = 1; i <= scc_cnt; i ++ ){
        sort(begin(scc[i]), end(scc[i]));
    }
    sort(scc + 1, scc + scc_cnt + 1);
    for(int i = 1; i <= scc_cnt; i ++ ){
        for(const auto& x : scc[i]) cout << x << ' ';
        cout << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}