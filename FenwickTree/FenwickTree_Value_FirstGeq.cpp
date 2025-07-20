/**
 * 题目来源：https://atcoder.jp/contests/abc392/tasks/abc392_f
 * 题目简介：树状数组上二分 / 线段树上二分 + 单点修改
 * 一个长度为 n 的序列 p，p_i \leq i
 * p_i 表示数字 i 插入到当前序列的第 p_i 个位置
 * 求最终构成的序列
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
#define lowbit(x) (x) & (-x)
const int N = 5e5 + 10;

int p[N], tr[N];

inline void add(int x, int c){
    for(int i = x; i < N; i += lowbit(i)){
        tr[i] += c;
    }
}

// 找到全局第一个前缀和大于等于x的位置
inline int first_geq(int x, int n){
    int sum = 0, pos = 0;
    for(int k = 20; ~k; k -- ){ // 倍增
        if(pos + (1 << k) < n && sum + (tr[pos + (1 << k)]) < x){
            pos += (1 << k);
            sum += tr[pos];
        }
    }
    return pos + 1; // 向后一步就是答案
}

void marisa(){
    int n; cin >> n;
    for(int i = 1; i <= n; i ++ ) cin >> p[i];
    vector<int> ans(n + 1);
    for(int i = 1; i <= n; i ++ ) add(i, 1); // 初始 1 代表空位
    for(int i = n; i; i -- ){ // 反过来考虑
        int pos = first_geq(p[i], n); // 第一个前缀和大于等于p_i的位置
        ans[pos] = i; // 放入这个数字
        add(pos, -1); // 撤除空位，后续p_i的只能放到后面
    }
    for(int i = 1; i <= n; i ++ ){
        cout << ans[i] << " \n"[i == n];
    }
}

int main(){
    fastio;
    
    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
} 