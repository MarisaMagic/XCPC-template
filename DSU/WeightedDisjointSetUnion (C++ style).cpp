/**
 * 题目来源：https://www.luogu.com.cn/problem/P1196
 * 题目简介：带权并查集模板
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)

struct DSU {
    vector<int> fa, sz, d; // d[u]: u到其leader距离
    DSU() {}
    DSU(int n){
        init(n);
    }
    void init(int n){
        fa.resize(n);
        iota(begin(fa), end(fa), 0);
        sz.assign(n, 1);
        d.assign(n, 0);
    }
    int find(int x){
        if(fa[x] == x) return x;
        int tmp = find(fa[x]);
        d[x] += d[fa[x]];
        return fa[x] = tmp;
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
        d[y] = sz[x];
        sz[x] += sz[y];
        return true;
    }
    int size(int x){
        return sz[find(x)];
    }
    int get_d(int x, int y){
        if(find(x) == find(y)){
            return abs(d[x] - d[y]) - 1;
        }
        return -1;
    }
};


void marisa(){
    const int N = 1e5 + 10;
    DSU dsu(N);
    int m; cin >> m;
    for(int i = 1, x, y; i <= m; i ++ ){
        char op; cin >> op >> x >> y;
        if(op == 'M'){
        	dsu.merge(x, y);
        }else{
            cout << dsu.get_d(x, y) << "\n";
    	}
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}