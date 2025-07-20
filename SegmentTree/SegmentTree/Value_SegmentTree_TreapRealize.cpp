/**
 * 题目来源：https://www.luogu.com.cn/problem/P3369
 * 题目简介：普通平衡树，插入、删除、询问全局rk、询问前驱后继
 * 用权值线段树解决，线段树 + 离散化 + 树上二分
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define mid (l + r >> 1)
#define ls (u << 1)
#define rs (u << 1 | 1)
const int N = 1e5 + 10;

int n, q, a[N], sum[N << 2];

inline void pushup(int u){
    sum[u] = sum[ls] + sum[rs];
}

void node_add(int u, int l, int r, int k, int x){
    if(l == r){
        sum[u] += x;
        return;
    }
    if(k <= mid) node_add(ls, l, mid, k, x);
    else node_add(rs, mid + 1, r, k, x);
    pushup(u);
}

int query_range(int u, int l, int r, int ql, int qr){
    if(ql <= l && r <= qr) return sum[u];
    int res = 0;
    if(ql <= mid) res += query_range(ls, l, mid, ql, qr);
    if(qr > mid) res += query_range(rs, mid + 1, r, ql, qr);
    return res;
}

int first_geq(int u, int l, int r, int ql, int qr, int x){ // 树上二分
    if(l > qr || r < ql || sum[u] < x) return qr + 1;
    if(l == r) return l;
    int pos = first_geq(ls, l, mid, ql, qr, x);
    if(pos != qr + 1) return pos;
    return first_geq(rs, mid + 1, r, ql, qr, x - sum[ls]);
}

void marisa(){
    cin >> q;
    vector<pair<int, int>> qs(q + 1);
    for(int i = 1; i <= q; i ++ ){
        cin >> qs[i].first >> qs[i].second;
        if(qs[i].first != 4) a[ ++ n] = qs[i].second;
    }
    sort(a + 1, a + n + 1);
    n = unique(a + 1, a + n + 1) - a - 1;

    auto find = [&](int x){
        return lower_bound(a + 1, a + n + 1, x) - a;
    };

    for(int i = 1; i <= q; i ++ ){
        auto& [op, x] = qs[i];
        if(op != 4) x = find(x);
        if(op == 1){
            node_add(1, 1, n, x, 1); // 增加一个x
        }else if(op == 2){
            node_add(1, 1, n, x, -1); // 删除一个x
        }else if(op == 3){
            if(x == 1){
                cout << 1 << "\n";
                continue;
            }
            // [1, x-1] 范围内的数的数量和，就是比x小的数的数量
            cout << query_range(1, 1, n, 1, x - 1) + 1 << "\n";
        }else if(op == 4){
            // 范围内第一个前缀和大于等于k的位置，该位置的数就是排第k位的
            cout << a[first_geq(1, 1, n, 1, n, x)] << "\n";
        }else if(op == 5){
            // 小于x的数的数量rk，排第rk的数就是x的前驱 
            int rk = query_range(1, 1, n, 1, x - 1);
            cout << a[first_geq(1, 1, n, 1, n, rk)] << "\n";
        }else{
            // 小于等于x的数的数量 + 1 为 rk，排第rk的数就是x的后继
            int rk = query_range(1, 1, n, 1, x) + 1;
            cout << a[first_geq(1, 1, n, 1, n, rk)] << "\n";
        }
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}