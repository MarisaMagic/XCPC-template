/**
 * 题目来源：https://www.luogu.com.cn/problem/P4822
 * 题目简介：DP最短路 K次机会 使得通过的某条道路时间减半
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pll = pair<ll, ll>;

struct node{
	ll d, t, u;
	node(ll _d, ll _t, ll _u): d(_d), t(_t), u(_u) {}
	bool operator< (const node& other) const {
		return d > other.d;
	}
};

void marisa(){
    int n, m, K; cin >> n >> m >> K;
    vector<vector<pll>> e(n + 1);
    for(int i = 1, u, v, w; i <= m; i ++ ){
    	cin >> u >> v >> w;
    	e[u].emplace_back(v, w);
    	e[v].emplace_back(u, w);
    }
    // dist[u][k] 到达 u 使用 k 次机会的最短距离
    vector<vector<ll>> dist(n + 1, vector<ll>(K + 1, 3e18));
    vector<vector<bool>> vis(n + 1, vector<bool>(K + 1));
    auto dijkstra = [&](int src){		
    	priority_queue<node> q;
    	q.emplace(dist[src][0] = 0, 0, src);
    	while(q.size()){
    		auto [d, t, u] = q.top();
    		q.pop();
    		if(vis[u][t]) continue;
    		vis[u][t] = true;
    		for(const auto& [v, w] : e[u]){
    			if(dist[v][t] > d + w){ // 不使用机会直接转移
    				dist[v][t] = d + w;
    				q.emplace(dist[v][t], t, v);
    			}
    			if(t < K && dist[v][t + 1] > d + w / 2){ // 使用一次机会
    				dist[v][t + 1] = d + w / 2;
    				q.emplace(dist[v][t + 1], t + 1, v); 
    			}
    		}
    	}
    };

    dijkstra(1);

    ll ans = 3e18;
    for(int i = 0; i <= K; i ++ ){
    	ans = min(ans, dist[n][i]);
    }
    cout << ans << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}