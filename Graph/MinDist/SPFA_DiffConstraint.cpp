/**
 * 题目来源：https://www.luogu.com.cn/problem/P1993
 * 题目简介：SPFA + 差分约束
 * 共 n 个值，m 个约束条件：
 * op1: x[u] 至少比 x[v] 大 w
 * op2: x[u] 至多比 x[v] 大 w
 * op3: x[u] 和 x[v] 相等
 * 判断是否存在一种解使得m个约束都满足
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pll = pair<ll, ll>;

void marisa(){
	int n, m; cin >> n >> m;
	vector<vector<pll>> e(n + 1);
	for(int i = 1; i <= n; i ++ ){
		e[0].emplace_back(i, 0); // x[i] <= x[0] + 0
	}
	for(int i = 1, op, u, v, w; i <= m; i ++ ){
		cin >> op >> u >> v;
		if(op == 1){
			cin >> w; // x[u] >= x[v] + w -> x[v] <= x[u] - w
			e[u].emplace_back(v, -w);
		}else if(op == 2){
			cin >> w; // x[u] <= x[v] + w
			e[v].emplace_back(u, w);
		}else{
			// x[u] <= x[v] + 0, x[v] <= x[u] + 0
			e[u].emplace_back(v, 0);
			e[v].emplace_back(u, 0);
		}
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
    				if(cnt[v] >= n + 1){ // 访问次数大于等于节点数，有负环
    					return true; // 无解
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

    cout << (!spfa(0) ? "Yes" : "No") << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}