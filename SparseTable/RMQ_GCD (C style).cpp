#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
const int N = 1e5 + 10, M = 21;

int a[N], n, q;
int g[N][M]; // gcd[i][j]: [i, i+2^j-1] 的区间最值
int logn[N];

void pre_log(){ // 预处理log数组
    for(int i = 2; i < N; i ++ ){
        logn[i] = logn[i >> 1] + 1;
    }
}

void rmq_gcd(){
    for(int i = 1; i <= n; i ++ ) g[i][0] = a[i];
    for(int j = 1; j < M; j ++ ){
        for(int i = 1; i + (1 << j) - 1 <= n; i ++ ){ 
            // [i, i+2^(j-1)-1], [i+2^(j-1), i+2^j-1]
            g[i][j] = gcd(g[i][j - 1], g[i + (1 << (j - 1))][j - 1]);
        }
    }
}

inline int query_gcd(const int& l, const int& r){
    int k = logn[r - l + 1];
    return gcd(g[l][k], g[r - (1 << k) + 1][k]);
}

void marisa(){
    cin >> n >> q;
    for(int i = 1; i <= n; i ++ ) cin >> a[i];

    pre_log();
    rmq_gcd();

    for(int i = 0, l, r; i < q; i ++ ){
        cin >> l >> r;
        cout << query_gcd(l, r) << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}