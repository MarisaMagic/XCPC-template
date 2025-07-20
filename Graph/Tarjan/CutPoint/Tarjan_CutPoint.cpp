/**
 * 题目来源：https://www.luogu.com.cn/problem/P3388
 * 题目简介：tarjan 求割点（cut）模板
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
const int N = 2e4 + 10;

int n, m, rt;
vector<int> e[N];
int low[N], dfn[N], num;
bool cut[N];

void tarjan(int u){
    low[u] = dfn[u] = ++ num;
    int son = 0;
    for(const auto& v : e[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]){ // v返祖dfn序比当前u靠后
                son ++ ; // u=rt, 大于一个儿子是割点
                if(u != rt || son > 1) cut[u] = true;
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
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    for(int i = 1; i <= n; i ++ )
        if(!dfn[i]) tarjan(rt = i);
    vector<int> ans;
    for(int i = 1; i <= n; i ++ )
        if(cut[i]) ans.emplace_back(i);
    cout << ans.size() << "\n";
    for(const auto& x : ans) cout << x << ' ';
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}