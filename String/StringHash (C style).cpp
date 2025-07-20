#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

const int N = 1e5 + 10;
const int mod = 1e9 + 9;

ll h[N], b[N];

void pre_hash(const string& s){
    const int base = 233;
    int n = s.size();
    b[0] = 1;
    h[0] = 0;
    for(int i = 1; i <= n; i ++ ){
        b[i] = b[i - 1] * base % mod;
        h[i] = (h[i - 1] * base % mod + s[i - 1]) % mod; 
    }
}

inline ll query(const int& l, const int& r){
    return (h[r] - h[l - 1] * b[r - l + 1] % mod + mod) % mod;
}

void marisa(){
    int n, q; cin >> n >> q;
    string s; cin >> s;

    pre_hash(s);

    for(int i = 0, l1, r1, l2, r2; i < q; i ++ ){
        cin >> l1 >> r1 >> l2 >> r2;
        cout << (query(l1, r1) == query(l2, r2) ? "Yes" : "No") << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}