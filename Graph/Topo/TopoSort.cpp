/**
 * 题目来源：https://www.luogu.com.cn/problem/P1137
 * 题目简介：topo 排序 + 简单 dp
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

const int N = 1e5 + 10;

int n, m;
vector<int> e[N];
int ind[N], dp[N];

void topo(){
	queue<int> q;
	for(int i = 1; i <= n; i ++ ){
		if(!ind[i])	q.emplace(i);
		dp[i] = 1;
	}
	while(q.size()){
		int u = q.front();
		q.pop();
		for(const auto& v : e[u]){
			dp[v] = max(dp[v], dp[u] + 1);
			if(!( -- ind[v])) q.emplace(v);
		}
	}
}

void marisa(){
    cin >> n >> m;
    for(int i = 1, u, v; i <= m; i ++ ){
    	cin >> u >> v;
    	e[u].emplace_back(v);
    	ind[v] ++ ;
    }
    topo();
    for(int i = 1; i <= n; i ++ ){
    	cout << dp[i] << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}