/**
 * 题目来源：https://www.luogu.com.cn/problem/P3376
 * 题目简介：最大流 dinic + 当前弧优化 模板
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

template <typename T>
class MaxFlow { // dinic + 当前弧优化求最大流
    struct _Edge {
        int to; // 边指向点
        T cap;  // 边的容量
        _Edge(int _to, T _cap): to(_to), cap(_cap) {}
    };
public:
    int n, src, des; // src: 源点  des: 汇点
    vector<_Edge> e; // e[j]: 编号为 j 的边
    vector<vector<int>> g; // g[u][i]: u出去的第i条边的编号
    vector<int> cur; // 当前弧
    vector<int> dep; // 点的层次
    MaxFlow() {}
    MaxFlow(int n, int src, int des){
        init(n, src, des);
    } 
    void init(int n, int src, int des){
        this -> n = n;
        this -> src = src;
        this -> des = des;
        e.clear();
        g.assign(n + 1, {});
        cur.resize(n + 1);
        dep.resize(n + 1);
    }
    bool bfs(){ // bfs 求层次图
        dep.assign(n + 1, -1);
        queue<int> q;
        q.emplace(src);
        dep[src] = 0;
        while(q.size()){
            int u = q.front();
            q.pop();
            for(const auto& i : g[u]){
                const auto& [v, c] = e[i];
                if(c > 0 && dep[v] == -1){
                    q.emplace(v);
                    dep[v] = dep[u] + 1;
                    if(v == des) return true; // 可以到达汇点
                }
            }
        }
        return false;
    }
    T dfs(int u, T flow){
        if(u == des) return flow;
        T used = 0; // 记录使用的流量
        for(int i = cur[u]; i < (int)g[u].size() && used < flow; i ++ ){
            cur[u] = i; // 当前弧优化
            const int& j = g[u][i];
            auto [v, c] = e[j];
            if(c > 0 && dep[v] == dep[u] + 1){
                auto t = dfs(v, min(flow - used, c)); // 递归寻找增广路
                e[j].cap -= t; // 更新边的容量
                e[j ^ 1].cap += t; // 反向边增加
                used += t; // 更新使用的流量
            }
        }
        return used; // 当前增广路使用的流量
    }
    void add_edge(int u, int v, T c){
        g[u].emplace_back(e.size());
        e.emplace_back(v, c);
        g[v].emplace_back(e.size());
        e.emplace_back(u, 0); // 反向边初始容量为 0
    }
    T dinic(){
        T res = 0;
        while(bfs()){
            cur.assign(n + 1, 0); // 重置当前弧
            res += dfs(src, numeric_limits<T>::max());
        }
        return res;
    }
};

void marisa(){
    int n, m, src, des; cin >> n >> m >> src >> des;
    MaxFlow<ll> mf(n, src, des);
    for(int i = 1, u, v; i <= m; i ++ ){
        ll c; cin >> u >> v >> c;
        mf.add_edge(u, v, c);
    }
    cout << mf.dinic() << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}