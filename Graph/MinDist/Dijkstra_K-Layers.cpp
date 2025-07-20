/**
 * 题目来源：https://www.luogu.com.cn/problem/P4822
 * 题目简介：分层图最短路 K次机会 使得通过的某条道路时间减半
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pll = pair<ll, ll>;

void marisa(){
    int n, m, K; cin >> n >> m >> K;
    vector<vector<pll>> e((K + 1) * n + 1);
    for(int i = 1, u, v, w; i <= m; i ++ ){
    	cin >> u >> v >> w;
        // 每一层之间可以直接转移
    	for(int k = 0; k <= K; k ++ ){
            e[u + k * n].emplace_back(v + k * n, w);
            e[v + k * n].emplace_back(u + k * n, w);
        }
        // 相邻层之间可以转移
        for(int k = 0; k < K; k ++ ){
            e[u + k * n].emplace_back(v + (k + 1) * n, w / 2);
            e[v + k * n].emplace_back(u + (k + 1) * n, w / 2);
        }
    }
    
    vector<ll> dist((K + 1) * n + 1, 4e18);
    vector<bool> vis((K + 1) * n + 1);
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
    
    dijkstra(1);

    ll ans = 3e18;
    for(int k = 0; k <= K; k ++ ){
        ans = min(ans, dist[n + k * n]);
    }
    cout << ans << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}