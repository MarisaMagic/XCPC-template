/**
 * 题目来源：https://www.luogu.com.cn/problem/B3647
 * 题目简介：Floyd 模板
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

void marisa(){
    int n, m; cin >> n >> m;
    vector<vector<ll>> d(n + 1, vector<ll>(n + 1, 3e18));
   	for(int i = 1, u, v, w; i <= m; i ++ ){
   		cin >> u >> v >> w;
   		d[u][v] = d[v][u] = min<ll>(d[u][v], w);
   	}

   	auto floyd = [&](){
   		for(int i = 1; i <= n; i ++ ) d[i][i] = 0;
   		for(int k = 1; k <= n; k ++ ){
   			for(int i = 1; i <= n; i ++ ){
   				for(int j = 1; j <= n; j ++ ){
   					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
   				}
   			}
   		}
   	};

   	floyd();

   	for(int i = 1; i <= n; i ++ ){
   		for(int j = 1; j <= n; j ++ ){
   			cout << d[i][j] << " \n"[j == n];
   		}
   	}
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}