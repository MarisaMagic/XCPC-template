/**
 * 题目来源：https://www.luogu.com.cn/problem/P3374
 * 题目简介：树状数组 1
 * 1. 将某一个数 +x；2. 询问区间和
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

template <typename T>
struct Fenwick {
    int n;
    vector<T> a;
    Fenwick() {}
    Fenwick(int n){
        init(n);
    }
    void init(int n){
        this -> n = n;
        a.assign(n + 1, 0);
    }
    void add(int x, const T& d){
        for(int i = x; i <= n; i += i & -i){
            a[i] += d;
        }
    }
    T query(int x){
        T res{};
        for(int i = x; i; i -= i & -i){
            res = res + a[i];
        }
        return res;
    }
    T range_sum(int l, int r){
        return query(r) - query(l - 1);
    }
    int first_geq(const T& x){ // 前缀和第一个大于等于x的位置    
        int pos = 0;
        T sum = 0;
        for(int k = 20; ~k; k -- ){ // 倍增
            if(pos + (1 << k) < n && sum + a[pos + (1 << k)] < x){
                pos += (1 << k);
                sum += a[pos];
            }
        }
        return pos + 1; // 向后一步就是答案
    }
};

void marisa(){
    int n, q; cin >> n >> q;
    Fenwick<ll> tr(n);
    for(int i = 1, x; i <= n; i ++ ){
        cin >> x;
        tr.add(i, x);
    }
    for(int i = 1, op; i <= q; i ++ ){
        cin >> op;
        if(op == 1){
            int p; ll x; cin >> p >> x;
            tr.add(p, x);
        }else{
            int l, r; cin >> l >> r;
            cout << tr.range_sum(l, r) << "\n";
        }
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}