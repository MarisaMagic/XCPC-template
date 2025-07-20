/**
 * 题目来源：https://www.luogu.com.cn/problem/P1144
 * 题目简介：dijkstra 最短路计数
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pll = pair<ll, ll>;
const int mod = 100003;


void marisa(){
    int n, m; cin >> n >> m;
    vector<vector<pll>> e(n + 1);
    for(int i = 1, u, v; i <= m; i ++ ){
    	cin >> u >> v;
    	e[u].emplace_back(v, 1);
    	e[v].emplace_back(u, 1);
    }
    
    vector<ll> dist(n + 1, 4e18);
    vector<bool> vis(n + 1);
    vector<ll> cnt(n + 1);
    auto dijkstra = [&](int src){
    	priority_queue<pll, vector<pll>, greater<pll>> q;
    	q.emplace(dist[src] = 0, src);
    	cnt[src] = 1;
    	while(q.size()){
    		auto [d, u] = q.top();
    		q.pop();
    		if(vis[u]) continue;
    		vis[u] = true;
    		for(const auto& [v, w] : e[u]){
    			if(dist[v] > d + w){
    				q.emplace(dist[v] = d + w, v);
    				cnt[v] = cnt[u];
    			}else if(dist[v] == d + w){
    				cnt[v] = (cnt[v] + cnt[u]) % mod;
    			}
    		}
    	}
    };
    
    dijkstra(1);

    for(int i = 1; i <= n; i ++ ){
    	cout << cnt[i] << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}