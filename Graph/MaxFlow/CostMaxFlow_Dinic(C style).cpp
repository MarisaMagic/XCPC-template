/**
 * 题目来源：https://www.luogu.com.cn/problem/P1006
 * 题目简介：最小费用最大流 + 拆点
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int N = 5010, M = 1e6 + 10;
int h[N], e[M], ne[M], w[M], cost[M], idx;

void add(int a, int b, int c, int d){
    e[idx] = b, ne[idx] = h[a], w[idx] = c, cost[idx] = d, h[a] = idx ++ ;
    e[idx] = a, ne[idx] = h[b], w[idx] = 0, cost[idx] = -d, h[b] = idx ++ ;
}

int src, des, sumcost;
int d[N], now[N];
bool st[N], vis[N];

bool spfa(){
    memset(d, -1, sizeof d);
    queue<int> q;
    q.emplace(src);
    d[src] = 0;
    now[src] = h[src];
    st[src] = true;
    while(q.size()){
        int u = q.front();
        q.pop();
        st[u] = false;
        for(int i = h[u]; ~i; i = ne[i]){
            int v = e[i], c = w[i];
            if(c > 0 && d[v] < d[u] + cost[i]){
                d[v] = d[u] + cost[i];
                now[v] = h[v];
                if(!st[v]){
                    q.emplace(v);
                    st[v] = true;
                }
            }
        }
    }
    return d[des] != -1;
}

int dfs(int u, int flow){
    if(u == des) return flow;
    int used = 0;
    vis[u] = true;
    for(int i = now[u]; ~i && used < flow; i = ne[i]){
        now[u] = i;
        int v = e[i], c = w[i];
        if(!vis[v] && c > 0 && d[v] == d[u] + cost[i]){
            int t = dfs(v, min(c, flow - used));
            w[i] -= t;
            w[i ^ 1] += t;
            used += t;
            sumcost += cost[i] * t;
        }
    }
    vis[u] = false;
    return used;
}

int dinic(){
    int res = 0;
    while(spfa()){
        res += dfs(src, 1e9);
    }
    return res;
}

void marisa(){
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i ++ ){
        for(int j = 1; j <= m; j ++ ){
            cin >> g[i][j];
        }
    }
    auto get_id = [&](int x, int y){
        return (x - 1) * m + y;
    };
    memset(h, -1, sizeof h);
    src = get_id(1, 1), des = get_id(n, m) + n * m;
    for(int i = 1; i <= n; i ++ ){
        for(int j = 1; j <= m; j ++ ){
            int u = get_id(i, j), v = u + n * m;
            int c = 1;
            if((i == 1 && j == 1) || (i == n && j == m)){
                c = 2;
                assert(g[i][j] == 0);
            }
            add(u, v, c, g[i][j]);
            if(i < n){
                add(v, get_id(i + 1, j), 1, 0);
            }
            if(j < m){
                add(v, get_id(i, j + 1), 1, 0);
            }
        }
    }
    dinic();
    cout << sumcost << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}