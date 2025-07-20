/**
 * 题目来源：https://www.luogu.com.cn/problem/P3469
 * 题目简介：图中割去一个点会造成多少有序点对不连通
 * tarjan求割点 + 子树节点数统计，计算两两部分之间贡献
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
const int N = 1e5 + 10;

// 如果u为割点
// 1. 子树v互相之间的有序点对数量 + 每个子树v到向上子树的有序点对 + 每个子树v到u的有序点对
// sz[v] * (n - sz[v]) 
// 2. 向上子树到u的有序点对 + 向上子树到每个子树v的有序点对
// (sum + 1) * (n - sum - 1)
// 3. u到每个子树v的有序点对 + u到向上子树的有序点对
// n - 1

int n, m, rt;
vector<int> e[N];
int low[N], dfn[N], num;
bool cut[N];
ll sz[N], ans[N];

void tarjan(int u){
    low[u] = dfn[u] = ++ num;
    int son = 0;
    ll sum = 0; // 统计u之下不会返祖到u之上的v子树节点数量之和
    sz[u] = 1;
    for(const auto& v : e[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
            sz[u] += sz[v];
            if(low[v] >= dfn[u]){ // v返祖dfn序比当前u靠后
                son ++ ; // u=rt, 大于一个儿子是割点
                if(u != rt || son > 1) cut[u] = true;

                // 不会返祖到u之上
                sum += sz[v];
                ans[u] += sz[v] * (n - sz[v]); // 1.
            }
        }else{
            low[u] = min(low[u], dfn[v]);
        }
    }

    if(!cut[u]){
        ans[u] = 2 * (n - 1); // 如果不是割点
    }else{
        ans[u] += (sum + 1) * (n - sum - 1); // 2.
        ans[u] += (n - 1); // 3.
    }
}

void marisa(){
    cin >> n >> m;
    for(int i = 1, u, v; i <= m; i ++ ){
        cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    tarjan(rt = 1);
    for(int i = 1; i <= n; i ++ ){
        cout << ans[i] << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}