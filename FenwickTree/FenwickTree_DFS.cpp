/**
 * 题目来源：https://ac.nowcoder.com/acm/problem/204871
 * 题目简介：dfn序 + 树状数组
 * 求出dfn序及子树大小，子树管辖范围为 dfn ~ dfn + sz - 1
 * 单点修改 + 区间和询问，树状数组维护
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

const int N = 1e6 + 10;
int dfn[N], num;
int sz[N];
vector<int> e[N];

void dfs(int u, int fa){
	dfn[u] = ++ num;
	sz[u] = 1;
	for(const auto& v : e[u]){
		if(v == fa) continue;
		dfs(v, u);
		sz[u] += sz[v];
	}
}

int n, m, rt;
int val[N];
ll tr[N];

void add(int x, ll c){
	for(int i = x; i < N; i += i & -i){
		tr[i] += c;
	}
}

ll query(int x){
	ll res = 0;
	for(int i = x; i; i -= i & -i){
		res += tr[i];
	}
	return res;
}

inline ll get_sum(int l, int r){
	return query(r) - query(l - 1);
}

void marisa(){
    cin >> n >> m >> rt;
    for(int i = 1; i <= n; i ++ ) cin >> val[i];
    for(int i = 1, u, v; i < n; i ++ ){
    	cin >> u >> v;
    	e[u].emplace_back(v);
    	e[v].emplace_back(u);
    }
    dfs(rt, 0);
    for(int i = 1; i <= n; i ++ ) add(dfn[i], val[i]);
    for(int i = 1, op, a, x; i <= m; i ++ ){
    	cin >> op >> a;
    	if(op == 1){
    		cin >> x;
    		add(dfn[a], x);
    	}else{
    		// a 节点管辖的子树节点范围为 dfn ~ dfn + sz - 1
    		cout << get_sum(dfn[a], dfn[a] + sz[a] - 1) << "\n";
    	}
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}