/**
 * 题目来源：https://www.luogu.com.cn/problem/P3834
 * 题目简介：【模板】可持久化线段树 2
 * 可持久化权值线段树（主席树）+ 动态开点，静态区间第k小
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define mid (l + r >> 1)
#define lsum (sum[ls[u]] - sum[ls[pre]])
using ll = long long;
const int N = 2e5 + 10;

int n, q, tot, rt[N];
int sum[N * 32], ls[N * 32], rs[N * 32];

void node_add(int& u, int pre, int l, int r, int x){
    u = ++ tot;
    ls[u] = ls[pre], rs[u] = rs[pre], sum[u] = sum[pre] + 1;
    if(l == r) return;
    if(x <= mid) node_add(ls[u], ls[pre], l, mid, x);
    else node_add(rs[u], rs[pre], mid + 1, r, x);
}

int query_kth(int u, int pre, int l, int r, int k){
    if(l == r) return l;
    if(k <= lsum) return query_kth(ls[u], ls[pre], l, mid, k);
    return query_kth(rs[u], rs[pre], mid + 1, r, k - lsum);
}

void marisa(){
    const int L = 0, R = 1e9;
    cin >> n >> q;
    for(int i = 1, x; i <= n; i ++ ){
        cin >> x;
        node_add(rt[i], rt[i - 1], L, R, x);
    }
    for(int i = 1, l, r, k; i <= q; i ++ ){
        cin >> l >> r >> k; 
        // 区间内前缀和第一个大于等于k的位置，就是区间第k小的数
        cout << query_kth(rt[r], rt[l - 1], L, R, k) << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}