/**
 * 题目来源：https://www.acwing.com/problem/content/description/843/
 * 题目简介：字符串哈希 双base 模底哈希 
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

struct Hash{
    using ll = long long;
    using pll = pair<ll, ll>;
    const int base1 = 233, base2 = 29;
    const int mod1 = 1e9 + 9, mod2 = 1e9 + 7;
    int n;
    vector<ll> b1, b2;
    vector<ll> h1, h2;
    Hash() {}
    Hash(const string& s){
        init(s);
    }
    void init(const string& s){
        n = s.size();
        b1.resize(n + 1), b2.resize(n + 1);
        h1.resize(n + 1), h2.resize(n + 1);
        b1[0] = b2[0] = 1;
        h1[0] = h2[0] = 0;
        for(int i = 1; i <= n; i ++ ){
            b1[i] = b1[i - 1] * base1 % mod1;
            b2[i] = b2[i - 1] * base2 % mod2;
            h1[i] = (h1[i - 1] * base1 % mod1 + s[i - 1]) % mod1;
            h2[i] = (h2[i - 1] * base2 % mod2 + s[i - 1]) % mod2;
        }
    }
    pll get_h(int l, int r){
    	ll res1 = (h1[r] - h1[l - 1] * b1[r - l + 1] % mod1 + mod1) % mod1;
    	ll res2 = (h2[r] - h2[l - 1] * b2[r - l + 1] % mod2 + mod2) % mod2;
        return pll{res1, res2}; 
    }
    bool same(int l1, int r1, int l2, int r2){
        return get_h(l1, r1) == get_h(l2, r2);
    }
    // 拼接两个不重叠子串（哈希拼接） s_{l1, r1} + s_{l2, r2}
    pll add(pll x, pll y){
    	return pll{(x.first + y.first) % mod1, (x.second + y.second) % mod2};
    }
    pll mul(pll x, ll k){
    	return pll{x.first * b1[k] % mod1, x.second * b2[k] % mod2};
    }
    pll concate(int l1, int r1, int l2, int r2){
        return add(mul(get_h(l2, r2), r1 - l1 + 1), get_h(l1, r1));
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