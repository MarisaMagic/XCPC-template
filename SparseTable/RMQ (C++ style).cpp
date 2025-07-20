/**
 * 题目来源：https://www.luogu.com.cn/problem/T584340
 * 题目简介：ST 表解决静态区间最值询问，ST表二分
 * 询问区间第一个大于x的数的位置
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
const int N = 2e6 + 10;

int logn[N]; // 预处理log数组
void pre_log(){ 
    for(int i = 2; i < N; i ++ ){
        logn[i] = logn[i >> 1] + 1;
    }
}

template <typename T>
class ST {
    using func_type = function<T(const T&, const T&)>;
    vector<array<T, 21>> f;
    func_type op;
    static T default_func(const T& x, const T& y){
        return max(x, y);
    }
public:
    ST() {}
    ST(const vector<T>& v, func_type _func = default_func){
        init(v, _func);
    }
    void init(const vector<T>& v, func_type _func = default_func){
        op = _func; 
        int n = v.size() - 1; // 数组v下标从1开始
        f.resize(n + 1);
        for(int i = 1; i <= n; i ++ ){
            f[i][0] = v[i];
        }
        for(int j = 1; j <= logn[n]; j ++ ){
            for(int i = 1; i + (1 << j) - 1 <= n; i ++ ){
                f[i][j] = op(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    T query(int l, int r){
        if(l > r) return -1;
        int k = logn[r - l + 1];
        return op(f[l][k], f[r - (1 << k) + 1][k]);
    }
};  

void marisa(){
    int n, q; cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i ++ ) cin >> a[i];
    ST<int> mx(a, [](const int& x, const int& y){
        return max(x, y);
    });
    for(int i = 0, L, R, x; i < q; i ++ ){
        cin >> L >> R >> x;
        int l = L, r = R;
        while(l < r){
            int mid = l + r >> 1;
            if(mx.query(L, mid) > x){
                r = mid;
            }else{
                l = mid + 1;
            }
        }
        cout << (mx.query(L, r) <= x ? -1 : r) << "\n";
    }
}

int main(){
    fastio;
     
    pre_log();

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}