/**
 * 题目来源：https://www.luogu.com.cn/problem/P8435
 * 题目简介：tarjan 求点双连通分量（point-bcc）模板
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
const int N = 5e5 + 10;

int n, m, rt;
vector<int> e[N];
int low[N], dfn[N], num;
bool cut[N];
int st[N], top;
int bcc_id[N], bcc_cnt;
vector<int> bcc[N];

void tarjan(int u){
    low[u] = dfn[u] = ++ num;
    st[ ++ top] = u;
    if(e[u].empty()){ // 孤立点特判，没有子树，视为一个bcc
        bcc[ ++ bcc_cnt].emplace_back(u);
    }
    int son = 0;
    for(const auto& v : e[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]){ // v返祖dfn序比当前u靠后
                son ++ ; // u=rt, 大于一个儿子是割点
                if(u != rt || son > 1) cut[u] = true;

                bcc_cnt ++ ; // u是一个点双连通分量的顶点
                int t;
                do{
                    t = st[top -- ];
                    bcc[bcc_cnt].emplace_back(t);
                    bcc_id[t] = bcc_cnt;
                }while(v != t);
                bcc[bcc_cnt].emplace_back(u);
            }
        }else{
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void marisa(){
    cin >> n >> m;
    for(int i = 1, u, v; i <= m; i ++ ){
        cin >> u >> v;
        if(u == v) continue; // 忽略自环，否则孤立点特判出错
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    for(int i = 1; i <= n; i ++ )
        if(!dfn[i]) tarjan(rt = i);
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