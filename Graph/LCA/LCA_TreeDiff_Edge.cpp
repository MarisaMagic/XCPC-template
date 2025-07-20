/**
 * 题目来源：https://www.luogu.com.cn/problem/P8855
 * 题目简介：倍增LCA + 树上差分（边差分）
 * 但本题实际不需要差分，只是为了用于做模板例题
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
    int n; cin >> n;
    for(int i = 1, u, v; i < n; i ++ ){
    	cin >> u >> v;
    	e[u].emplace_back(v); 
    	e[v].emplace_back(u);
    }
    dfs(1, 0);
    int m; cin >> m;
    vector<int> a(m + 1);
    for(int i = 1; i <= m; i ++ ) cin >> a[i];
    for(int i = 1, u, v; i < m; i ++ ){
    	u = a[i], v = a[i + 1];	
    	int anc = lca(u, v); // 每条边看作是点的权值，rt点无权值
    	b[u] ++ , b[anc] -- ; // anc 的下一个点 -> u 全部 + 1 
    	b[v] ++ , b[anc] -- ; // anc 的下一个点 -> v 全部 + 1
    }
    dfs2(1);
    int ans = 0;
    for(int i = 2; i <= n; i ++ ){
    	ans += b[i];
    }
    cout << ans << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}