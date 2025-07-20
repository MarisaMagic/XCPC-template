/**
 * 题目来源：https://www.luogu.com.cn/problem/P3369
 * 题目简介：普通平衡树，插入、删除、询问rk、询问前驱后继
 * 用权值线段树解决，动态开点线段树 + 树上二分
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define mid (l + r >> 1)
#define ls (lson[u])
#define rs (rson[u])
const int N = 1e5 + 10;

int q, rt, tot, sum[N * 30], lson[N * 30], rson[N * 30];

inline void pushup(int u){
    sum[u] = sum[ls] + sum[rs];
}

void node_add(int& u, int l, int r, int k, int x){
    if(!u) u = ++ tot;
    if(l == r){
        sum[u] += x;
        return;
    }
    if(k <= mid) node_add(ls, l, mid, k, x);
    else node_add(rs, mid + 1, r, k, x);
    pushup(u);
}

int query_range(int u, int l, int r, int ql, int qr){
    if(!u) return 0;
    if(ql <= l && r <= qr) return sum[u];
    int res = 0;
    if(ql <= mid) res += query_range(ls, l, mid, ql, qr);
    if(qr > mid) res += query_range(rs, mid + 1, r, ql, qr);
    return res;
}

int query_kth(int u, int l, int r, int k){ 
    if(l == r) return l;
    if(k <= sum[ls]) return query_kth(ls, l, mid, k);
    return query_kth(rs, mid + 1, r, k - sum[ls]);
}

void marisa(){
    cin >> q;
    const int L = -1e7, R = 1e7; // 值域范围
    for(int i = 1, op, x; i <= q; i ++ ){
        cin >> op >> x;
        if(op == 1){
            node_add(rt, L, R, x, 1); // 增加一个x
        }else if(op == 2){
            node_add(rt, L, R, x, -1); // 删除一个x
        }else if(op == 3){
            if(x == 1){
                cout << 1 << "\n";
                continue;
            }
            // [1, x-1] 范围内的数的数量和，就是比x小的数的数量
            cout << query_range(rt, L, R, L, x - 1) + 1 << "\n";
        }else if(op == 4){
            // 范围内第一个前缀和大于等于k的位置，该位置的数就是排第k位的
            cout << query_kth(rt, L, R, x) << "\n";
        }else if(op == 5){
            // 小于x的数的数量rk，排第rk的数就是x的前驱 
            int rk = query_range(rt, L, R, L, x - 1);
            cout << query_kth(rt, L, R, rk) << "\n";
        }else{
            // 小于等于x的数的数量 + 1 为 rk，排第rk的数就是x的后继
            int rk = query_range(rt, L, R, L, x) + 1;
            cout << query_kth(rt, L, R, rk) << "\n";
        }
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}