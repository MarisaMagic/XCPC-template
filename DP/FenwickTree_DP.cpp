/**
 * 题目来源：https://atcoder.jp/contests/abc369/tasks/abc369_f
 * 题目简介：树状数组优化DP
 * 给定若干个 (x, y)，x,y <= 2e5，每次可以向下或向右移动
 * 求最多经过多少个点
 * dp[i] = max dp[j] + 1, x[j] <= x[i], y[j] <= y[i]
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int N = 2e5 + 10;
pii tr[N]; // tr[i]: 所有点中，y为i的最大的dp状态

void add(int x, const pii& p){
    for(int i = x; i < N; i += i & -i){
        tr[i] = max(tr[i], p);
    }
}

pii query(int x){ // 所有纵坐标小于等于x的最大的dp状态
    pii res = {-1, 0};
    for(int i = x; i; i -= i & -i){
        res = max(res, tr[i]);
    }
    return res;
}

void marisa(){
    int n, m, k; cin >> n >> m >> k;
    vector<pii> p(k + 2);
    for(int i = 1, x, y; i <= k; i ++ ){
        cin >> x >> y;
        p[i] = {x, y};
    }
    p[0] = {1, 1};
    p[k + 1] = {n, m};
    sort(begin(p) + 1, end(p)); // 按照横坐标升序排序

    for(int i = 1; i < N; i ++ ){
        tr[i] = {-1, 0};
    }

    vector<pii> dp(k + 2);
    add(1, dp[0]);
    for(int i = 1; i <= k + 1; i ++ ){
        const auto& [x, y] = p[i];
        auto pre = query(y); // 前面小于等于x,小于等于y的最大dp状态
        dp[i] = pre;
        dp[i].first ++ ; 
        add(y, {dp[i].first, i});
    }
    cout << dp[k + 1].first - 1 << "\n";

    string ans = ""; // 回溯得到答案
    for(int i = k + 1; i; i = dp[i].second){
        int j = dp[i].second;
        for(int d = 1; d <= p[i].first - p[j].first; d ++ ){
            ans += 'D';
        }
        for(int d = 1; d <= p[i].second - p[j].second; d ++ ){
            ans += 'R';
        }
    }
    reverse(begin(ans), end(ans));
    cout << ans;
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}