/**
 * 题目来源：https://www.luogu.com.cn/problem/T589831
 * 题目简介：删除一个子串使得构成最长回文串
 * 字符串前后缀哈希。先将已有的回文前后缀清除并记录长度l
 * 将剩余部分的串枚举其保留的回文前缀
 * 反过来再进行一次，取较大值 + l * 2。
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

struct Hash{
    using ll = long long;
    const int base = 233;
    const int mod = 1e9 + 9;
    int n;
    vector<ll> b, h, rh;
    Hash() {}
    Hash(const string& s){
        init(s);
    }
    void init(const string& s){
        n = s.size();
        b.resize(n + 1);
        h.resize(n + 1), rh.resize(n + 1);
        b[0] = 1;
        h[0] = rh[0] = 0;
        for(int i = 1; i <= n; i ++ ){
            b[i] = b[i - 1] * base % mod;
            h[i] = (h[i - 1] * base % mod + s[i - 1]) % mod;
            rh[i] = (rh[i - 1] * base % mod + s[n - i]) % mod;
        }
    }
    ll get_h(int l, int r){
        return (h[r] - h[l - 1] * b[r - l + 1] % mod + mod) % mod; 
    }
    ll get_rh(int l, int r){
    	return (rh[r] - rh[l - 1] * b[r - l + 1] % mod + mod) % mod;
    }
    bool same(int l1, int r1, int l2, int r2){
        return get_h(l1, r1) == get_h(l2, r2);
    }
    // 拼接两个不重叠子串（哈希拼接） s_{l1, r1} + s_{l2, r2}, r1 < l2
    ll concate(int l1, int r1, int l2, int r2){
        return (get_h(l1, r1) * b[r2 - l2 + 1] % mod + get_h(l2, r2)) % mod;
    }
    // 后缀哈希下标范围反过来
    ll is_palindrome(int l, int r){ 
    	return get_h(l, r) == get_rh(n - r + 1, n - l + 1);
    }
};

int get_ans(const string& s){
    Hash hs(s);
    int n = s.size();
    for(int i = n; i; i -- ){ // 枚举前缀长度
        if(hs.is_palindrome(1, i)){
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