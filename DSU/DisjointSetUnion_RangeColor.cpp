/**
 * 题目来源：https://www.luogu.com.cn/problem/P1840
 * 题目简介：并查集区间染色
 * 每次将 [l, r] 染色，询问剩余的未染色点数
 * 染色的区间范围越来越大，通常可以考虑并查集维护区间连通性
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

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
        if(x < y) swap(x, y); // 合并到大的
        fa[y] = x;
        sz[x] += sz[y];
        return true;
    }
    int size(int x){
        return sz[find(x)];
    }
};

void marisa(){
    int n, q; cin >> n >> q;
    DSU uf(n + 1); // 区间看作 [1, n + 1]
    int res = 0;
    for(int i = 1, l, r; i <= q; i ++ ){
        cin >> l >> r;
        l = uf.find(l); // [l, n] 第一个未染色的点作为 leader
        while(l <= r){
            if(l != r && l == uf.find(r)) break; // 在同一块中，退出
            uf.merge(l, l + 1); // 向右合并，下一个块的 leader 作为 l 的leader
            res ++ ;
            l = uf.find(l + 1); // 到下一个未染色的点
        }
        cout << n - res << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}