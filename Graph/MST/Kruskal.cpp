/**
 * 题目来源：https://www.luogu.com.cn/problem/P3366
 * 题目简介：最小生成树 kruskal算法模板
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
const int N = 5010, M = 2e5 + 10;

int fa[N];
int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

struct node{
    int u, v, w;
    bool operator< (const node& other) const {
        return w < other.w;
    }
};

void marisa(){
    int n, m; cin >> n >> m;
    vector<node> edges(m);
    for(auto& [u, v, w] : edges) cin >> u >> v >> w;
    for(int i = 1; i <= n; i ++ ) fa[i] = i;
    int cnt = 0, sum = 0;
    auto kruskal = [&](){
        sort(begin(edges), end(edges));
        for(const auto& [u, v, w] : edges){
            int fx = find(u), fy = find(v);
            if(fx == fy) continue;
            fa[fy] = fx;
            sum += w;
            cnt ++ ;
        }
    };
    kruskal();
    if(cnt < n - 1){ // 不满 n - 1个边，无最小生成树
        cout << "orz" << "\n";
        return;
    }
    cout << sum << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}