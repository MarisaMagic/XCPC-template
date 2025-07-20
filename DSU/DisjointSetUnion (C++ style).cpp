/**
 * 题目来源：https://www.luogu.com.cn/problem/P3367
 * 题目简介：并查集模板
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
        fa.resize(n + 1);
        iota(begin(fa), end(fa), 0);
        sz.assign(n + 1, 1);
    }
    int find(int x){ // 迭代版find
        while(x != fa[x]){
            x = fa[x] = fa[fa[x]];
        }
        return x;
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
    DSU dsu(n);
    for(int i = 1, op, x, y; i <= m; i ++ ){
        cin >> op >> x >> y;
        if(op == 1){
            dsu.merge(x, y);
        }else{
            cout << (dsu.same(x, y) ? 'Y' : 'N') << "\n";
        }
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}