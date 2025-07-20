/**
 * 题目来源：https://codeforces.com/gym/102770/problem/E
 * 题目简介：主席树求区间前 k 大数之和
 * 变一下即可求区间前k小数和
**/
#include<bits/stdc++.h>
using namespace std;

#define ios ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define mid (l + r >> 1)
#define rnum (num[rs[u]] - num[rs[pre]])
#define rsum (sum[rs[u]] - sum[rs[pre]])
typedef long long ll;
const int N = 5e5 + 10;

int n, q, tot;
int num[N << 5], ls[N << 5], rs[N << 5], rt[N];
ll sum[N << 5], pre[N];

void node_add(int& u, int pre, int l, int r, int x){
    u = ++ tot;
    ls[u] = ls[pre], rs[u] = rs[pre];
    num[u] = num[pre] + 1, sum[u] = sum[pre] + x;
    if(l == r) return;
    if(x <= mid) node_add(ls[u], ls[pre], l, mid, x);
    else node_add(rs[u], rs[pre], mid + 1, r, x);
}

// 区间前k大数之和
ll query_kmx_sum(int u, int pre, int l, int r, int k){ 
    if(l == r) return (ll)k * l; // 一个数可能出现多次
    if(k <= rnum) return query_kmx_sum(rs[u], rs[pre], mid + 1, r, k);
    return rsum + query_kmx_sum(ls[u], ls[pre], l, mid, k - rnum);
}