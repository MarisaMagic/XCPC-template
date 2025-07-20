/**
 * 题目来源：https://www.luogu.com.cn/problem/P4779
 * 题目简介：单源最短路径 dijkstra
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pll = pair<ll, ll>;


void marisa(){
    int n, m, src; cin >> n >> m >> src;
    vector<vector<pll>> e(n + 1);
    for(int i = 1, u, v, w; i <= m; i ++ ){
    	cin >> u >> v >> w;
    	e[u].emplace_back(v, w);
    }
    
    vector<ll> dist(n + 1, 4e18);
    vector<bool> vis(n + 1);
    auto dijkstra = [&](int src){
    	priority_queue<pll, vector<pll>, greater<pll>> q;
    	q.emplace(dist[src] = 0, src);
    	while(q.size()){
    		auto [d, u] = q.top();
    		q.pop();
    		if(vis[u]) continue;
    		vis[u] = true;
    		for(const auto& [v, w] : e[u]){
    			if(dist[v] > d + w){
    				q.emplace(dist[v] = d + w, v);
    			}
    		}
    	}
    };
    
    dijkstra(src);

    for(int i = 1; i <= n; i ++ ){
    	cout << dist[i] << " \n"[i == n];
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}