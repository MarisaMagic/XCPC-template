#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

const int N = 2e5 + 10;
int n, m;
int fa[N], sz[N];

int find(int x){
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

// 迭代版find
// int find(int x){
// 	while(x != fa[x]){
// 		x = fa[x] = fa[fa[x]];
// 	}
// 	return x;
// }

inline void merge(int x, int y){
	x = find(x), y = find(y);
	if(x == y) return;
	fa[y] = x;
	sz[x] += sz[y];
}

inline bool same(int x, int y){
	return find(x) == find(y);
}

void marisa(){
 	cin >> n >> m;
 	for(int i = 1; i <= n; i ++ ){
 		fa[i] = i, sz[i] = 1;
 	}   
 	for(int i = 1, op, x, y; i <= m; i ++ ){
 		cin >> op >> x >> y;
 		if(op == 2){
 			cout << (same(x, y) ? 'Y' : 'N') << "\n";
 		}else{
 			merge(x, y);
 		}
 	}
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}