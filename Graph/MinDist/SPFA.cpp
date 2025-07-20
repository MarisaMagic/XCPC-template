/**
 * 题目来源：https://www.luogu.com.cn/problem/P3385
 * 题目简介：spfa判断负环
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pll = pair<ll, ll>;

void marisa(){
    int n, m; cin >> n >> m;
    vector<vector<pll>> e(n + 1);
    for(int i = 1, u, v, w; i <= m; i ++ ){
    	cin >> u >> v >> w;
    	e[u].emplace_back(v, w);
    	if(w >= 0) e[v].emplace_back(u, w);
    }
    
    vector<ll> dist(n + 1, 3e18);
    vector<bool> vis(n + 1);
    vector<int> cnt(n + 1);
    auto spfa = [&](int src){
    	deque<int> q;
    	q.emplace_back(src);
    	dist[src] = 0; 
    	vis[src] = true;
    	while(q.size()){
    		int u = q.front();
    		q.pop_front();
    		vis[u] = false;
    		for(const auto& [v, w] : e[u]){
    			if(dist[v] > dist[u] + w){
    				dist[v] = dist[u] + w;
    				cnt[v] = cnt[u] + 1;
    				if(cnt[v] >= n){ // 一个点访问量大于等于n次，有负环
    					return true; 
    				}
    				if(!vis[v]){
    					q.emplace_back(v);
    					vis[v] = true;
    				}
    			}
    		}
    	}
    	return false;
    };

    cout << (spfa(1) ? "YES" : "NO") << "\n";
}

int main(){
    fastio;

    int T = 1; cin >> T;
    while(T -- ) marisa();
    
    return 0;
}