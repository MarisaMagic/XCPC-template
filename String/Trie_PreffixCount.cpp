/**
 * 题目来源：https://www.luogu.com.cn/problem/P10470
 * 题目简介：询问 s_1, ... s_n 中有多少个是 t 的前缀
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int N = 1e5 + 10;
int son[N][26];    // 一维为节点编号 每个节点最多26种状态
int cnt[N];        // 统计编号结尾的字符串
int idx;           // 分配节点编号
string s;

void insert(const string& s){
    int p = 0;   // 从根节点开始
    for(const auto& ch : s){
        int c = ch - 'a';
        if(!son[p][c]) son[p][c] = ++ idx; // 不存在就分配一个编号
        p = son[p][c];
    }
    cnt[p] ++ ;    // 统计以编号p结尾的字符串
}

int query(const string& s){
    int p = 0;   // 从根节点开始
    int ans = 0; // 统计前缀个数
    for(const auto& ch : s){
        int c = ch - 'a';
        if(!son[p][c]){ // 走到头了，没有其余字符串可以作为前缀
            return ans;
        }
        p = son[p][c];
        ans += cnt[p]; // 以p为结尾的字符串是s前缀
    }
    return ans;
}

void marisa(){
    int n, q; cin >> n >> q;
    for(int i = 1; i <= n; i ++ ){
        string s; cin >> s;
        insert(s);
    }
    for(int i = 1; i <= q; i ++ ){
        string s; cin >> s;
        cout << query(s) << "\n";
    }
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}