/**
 * 题目来源：https://www.acwing.com/problem/content/description/843/
 * 题目简介：字符串哈希 单base 模底哈希 
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
    vector<ll> b, h;
    Hash() {}
    Hash(const string& s){
        init(s);
    }
    void init(const string& s){
        n = s.size();
        b.resize(n + 1), h.resize(n + 1);
        b[0] = 1, h[0] = 0;
        for(int i = 1; i <= n; i ++ ){
            b[i] = b[i - 1] * base % mod;
            h[i] = (h[i - 1] * base % mod + s[i - 1]) % mod;
        }
    }
    ll get_h(int l, int r){
        return (h[r] - h[l - 1] * b[r - l + 1] % mod + mod) % mod; 
    }
    bool same(int l1, int r1, int l2, int r2){
        return get_h(l1, r1) == get_h(l2, r2);
    }
    // 拼接两个不重叠子串（哈希拼接） s_{l1, r1} + s_{l2, r2} r1 < l2
    ll concate(int l1, int r1, int l2, int r2){
        return (get_h(l1, r1) * b[r2 - l2 + 1] % mod + get_h(l2, r2)) % mod;
    }
};

void marisa(){
    int n, q; cin >> n >> q;
    string s; cin >> s;
    Hash hs(s);
    for(int i = 0, l1, r1, l2, r2; i < q; i ++ ){
        cin >> l1 >> r1 >> l2 >> r2;
        cout << (hs.same(l1, r1, l2, r2) ? "Yes" : "No") << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}