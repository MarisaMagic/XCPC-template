/**
 * 题目来源：https://www.luogu.com.cn/problem/P3939
 * 题目简介：主席树询问区间某元素个数 + 交换相邻元素
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define mid (l + r >> 1)
#define lsum (sum[ls[u]] - sum[ls[pre]])
const int N = 1e6 + 10;

int n, q, tot, rt[N];
int sum[N * 32], ls[N * 32], rs[N * 32];

void node_add(int& u, int pre, int l, int r, int x, int c){
    u = ++ tot;
    ls[u] = ls[pre], rs[u] = rs[pre], sum[u] = sum[pre] + c;
    if(l == r) return;
    if(x <= mid) node_add(ls[u], ls[pre], l, mid, x, c);
    else node_add(rs[u], rs[pre], mid + 1, r, x, c);
}

int query_sum(int u, int pre, int l, int r, int x){
    if(l == r) return sum[u] - sum[pre];
    if(x <= mid) return query_sum(ls[u], ls[pre], l, mid, x);
    return query_sum(rs[u], rs[pre], mid + 1, r, x);
}

void marisa(){
    const int L = 0, R = N;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i ++ ){
        cin >> a[i];
        node_add(rt[i], rt[i - 1], L, R, a[i], 1);
    }
    for(int i = 1, op, l, r, x; i <= q; i ++ ){
        cin >> op;
        if(op == 1){
            cin >> l >> r >> x;
            cout << query_sum(rt[r], rt[l - 1], L, R, x) << "\n";
        }else{
            cin >> x;
            if(a[x] == a[x + 1]) continue;
            // 修改第 x 个版本的线段树，第 x + 1 个版本不动
            node_add(rt[x], rt[x], L, R, a[x], -1); 
            node_add(rt[x], rt[x], L, R, a[x + 1], 1);
            swap(a[x], a[x + 1]);
        }
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}