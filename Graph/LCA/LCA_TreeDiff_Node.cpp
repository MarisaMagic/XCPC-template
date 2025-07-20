/**
 * 题目来源：https://www.luogu.com.cn/problem/P3128
 * 题目简介：倍增LCA + 树上差分（点差分）
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

const int N = 5e4 + 10;
vector<int> e[N];
int dep[N], f[N][21];

void dfs(int u, int fa){
	dep[u] = dep[fa] + 1;
	f[u][0] = fa;
	for(int k = 1; k < 21; k ++ ){
		f[u][k] = f[f[u][k - 1]][k - 1];
	}
	for(const auto& v : e[u]){
		if(v == fa) continue;
		dfs(v, u);
	}
}

inline int lca(int u, int v){
	if(dep[u] < dep[v]) swap(u, v);
	for(int k = 20; k >= 0; k -- ){
		if(dep[f[u][k]] >= dep[v]){
			u = f[u][k];
		}
	}
	if(u == v) return u;
	for(int k = 20; k >= 0; k -- ){
		if(f[u][k] != f[v][k]){
			u = f[u][k], v = f[v][k];
		}
	}
	return f[u][0];
}

int b[N]; // 差分数组

void dfs2(int u){
	for(const auto& v : e[u]){
		if(v == f[u][0]) continue;
		dfs2(v);
		b[u] += b[v]; // 还原前缀和
	}
}

void marisa(){
    int n, q; cin >> n >> q;
    for(int i = 1, u, v; i < n; i ++ ){
    	cin >> u >> v;
    	e[u].emplace_back(v);
    	e[v].emplace_back(u);
    }
    dfs(1, 0);
    for(int i = 1, u, v; i <= q; i ++ ){
    	cin >> u >> v;	
    	int anc = lca(u, v); 
    	b[u] ++ , b[anc] -- ; // anc 到 u 路径上下一个节点 -> u 全部 + 1 
    	b[v] ++ , b[f[anc][0]] -- ; // anc -> v 全部 + 1
    }
    dfs2(1);
    int ans = 0;
    for(int i = 1; i <= n; i ++ ){
    	ans = max(ans, b[i]);
    }
    cout << ans << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}