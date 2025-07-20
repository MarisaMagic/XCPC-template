/**
 * 题目来源：https://www.luogu.com.cn/problem/T589831
 * 题目简介：删除一个子串使得构成最长回文串
 * 字符串前后缀哈希。先将已有的回文前后缀清除并记录长度l
 * 将剩余部分的串枚举其保留的回文前缀
 * 反过来再进行一次，取较大值 + l * 2。
**/
#include<bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
const int N = 2e6 + 10;
const int mod = 1e9 + 9;

ll h[N], rh[N], b[N], base;

void pre_hash(const string& s){
    int n = s.size();
    base = 233;
    b[0] = 1;
    h[0] = rh[0] = 0;
    for(int i = 1; i <= n; i ++ ){
        b[i] = (b[i - 1] * base) % mod;
        h[i] = (h[i - 1] * base + s[i - 1]) % mod; // 前缀哈希值
        rh[i] = (rh[i - 1] * base + s[n - i]) % mod; // 后缀哈希值        
    }
}

inline ll get_h(int l, int r){
    return ((h[r] - h[l - 1] * b[r - l + 1]) % mod + mod) % mod;
}

inline ll get_rh(int l, int r){
    return ((rh[r] - rh[l - 1] * b[r - l + 1]) % mod + mod) % mod;
}

inline bool is_palindrome(const string& s, int l, int r){
    int n = s.size();
    return get_h(l, r) == get_rh(n - r + 1, n - l + 1);
}

int get_ans(const string& s){
    pre_hash(s);
    int n = s.size();
    for(int i = n; i; i -- ){ // 枚举保留的前缀长度
        if(is_palindrome(s, 1, i)){
            return i;
        }
    }
    return 0;
}

void marisa(){
    string s; cin >> s;
    int l = 0, r = s.size() - 1;
    for( ; l < r && s[l] == s[r]; l ++ , r -- );
    if(l >= r){ // 本身就是回文串
        cout << s.size() << "\n";
        return;
    }
    s = s.substr(l, r - l + 1); // 剩余部分
    string t(s.rbegin(), s.rend());
    cout << max(get_ans(s), get_ans(t)) + l * 2 << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();

    return 0;
}