/**
 * 题目来源：https://www.luogu.com.cn/problem/P5410
 * 题目简介：Z函数 字符串 s 和其每个后缀的最长公共前缀 LCP
 * b 与 b 的每个后缀 LCP 长度，即 b 的 z 函数
 * b 与 a 的每个后缀 LCP 长度，求 b + a 的 z 函数
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

vector<int> Z(const string& s){
    int n = s.size();
    vector<int> z(n + 1); // s_{i, i + z[i] - 1} 是公共前缀
    z[0] = n;
    // j 记录上一个右边界最靠右的子串
    for(int i = 1, j = 1; i < n; i ++ ){ 
        z[i] = max(0, min(z[i - j], j + z[j] - i));
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]){
            z[i] ++ ;
        }
        if(i + z[i] > j + z[j]){
            j = i;
        }
    }
    return z;
}

void marisa(){
    string a, b; cin >> a >> b;
    int n = b.size();
    b += a;

    auto z = Z(b);

    ll ans1 = 0;
    for(int i = 0; i < n; i ++ ){
        ans1 ^= 1ll * (min(z[i], n - i) + 1) * (i + 1);
    }
    cout << ans1 << "\n";

    ll ans2 = 0;
    for(int i = 0; i < a.size(); i ++ ){
        ans2 ^= 1ll * (z[n + i] + 1) * (i + 1);
    }
    cout << ans2 << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}