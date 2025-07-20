#include<bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
const int N = 210, M = 1e4 + 10;
const ll inf = 1e18;

int h[N], e[M], ne[M], idx; // 链式前向星
int n, m, src, des;
ll cap[M]; // 边的容量

inline void add(int u, int v, ll c){
    e[idx] = v, ne[idx] = h[u], cap[idx] = c, h[u] = idx ++ ;
    e[idx] = u, ne[idx] = h[v], cap[idx] = 0, h[v] = idx ++ ;
}

int d[N], cur[M]; // d: 点的层次 cur: 当前弧

bool bfs(){
    memset(d, -1, sizeof d);
    queue<int> q;
    q.emplace(src);
    d[src] = 0;
    cur[src] = h[src];
    while(q.size()){
        int u = q.front();
        q.pop();
        for(int i = h[u]; ~i; i = ne[i]){
            int v = e[i];
            ll c = cap[i];
            if(c > 0 && d[v] == -1){
                q.emplace(v);
                d[v] = d[u] + 1;
                cur[v] = h[v];
                if(v == des) return true;
            }
        }
    }
    return false;
}

ll dfs(int u, ll f){
    if(u == des) return f;
    ll used = 0; // 记录当前使用的流量
    for(int i = cur[u]; ~i && used < f; i = ne[i]){
        cur[u] = i; // 当前弧优化
        int v = e[i];
        ll c = cap[i];
        if(c > 0 && d[v] == d[u] + 1){
            ll t = dfs(v, min(f - used, c)); // 剩余流量递归寻找增广路
            cap[i] -= t; // 更新边的容量
            cap[i ^ 1] += t;
            used += t; // 更新使用的流量
        }
    }
    return used; // 当前增广路使用的流量
}

ll dinic(){
    ll res = 0;
    while(bfs()){
        res += dfs(src, inf);
    }
    return res;
}

void marisa(){
    cin >> n >> m >> src >> des;
    memset(h, -1, sizeof h);
    for(int i = 1, u, v, c; i <= m; i ++ ){
        cin >> u >> v >> c;
        add(u, v, c);
    }
    cout << dinic() << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}