/**
 * 题目来源：https://www.luogu.com.cn/problem/P1892
 * 题目简介：扩展域并查集模板
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)

struct DSU {
    vector<int> fa, sz;
    DSU() {}
    DSU(int n){
        init(n);
    }
    void init(int n){
        fa.resize(n);
        iota(begin(fa), end(fa), 0);
        sz.assign(n, 1);
    }
    int find(int x){
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    bool same(int x, int y){
        return find(x) == find(y);
    }
    bool merge(int x, int y){
        x = find(x), y = find(y);
        if(x == y){
            return false;
        }
        fa[y] = x;
        sz[x] += sz[y];
        return true;
    }
    int size(int x){
        return sz[find(x)];
    }
};


void marisa(){
    int n, m; cin >> n >> m;
    DSU dsu(2 * n + 1);
    for(int i = 1, x, y; i <= m; i ++ ){
        char op; cin >> op >> x >> y;
        if(op == 'F'){
        	dsu.merge(x, y);
        }else{
            dsu.merge(x + n, y);
            dsu.merge(y + n, x);
    	}
    }
    int ans = 0;
    for(int i = 1; i <= n; i ++ ){
        ans += dsu.fa[i] == i;
    }
    cout << ans << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}