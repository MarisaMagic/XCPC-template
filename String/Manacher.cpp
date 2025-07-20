/**
 * 题目来源：https://www.luogu.com.cn/problem/P3805
 * 题目简介：manacher模板
 * 求出每个位置为中心的最长回文子串，r[i] 为 i 最右边回文边界
 * 长度为 n 的字符串，在 n + 1 个空位中插入 '#' 统一处理
 * 以 i 为中心的最长回文串长度即 r[i] - 1
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

vector<int> manacher(const string& s){
    string t = "#";
    for(const auto& ch : s){
        t += ch;
        t += '#';
    }
    int n = t.size();
    vector<int> r(n); // i - r[i] + 1 ~ i + r[i] - 1 是一个回文子串
    // j 记录上一个回文子串的中心
    for(int i = 0, j = 0; i < n; i ++ ){ 
        // 2 * j - i 为 i 在 j 为中心的回文串中的翻转位置的小回文子串的中心
        if(2 * j - i >= 0 && j + r[j] > i){ 
            // 取翻转位置的 r 和到 j 边界距离的较小值
            r[i] = min(r[2 * j - i], j + r[j] - i); 
        }
        while(i - r[i] >= 0 && i + r[i] < n && t[i - r[i]] == t[i + r[i]]){
            r[i] ++ ; // 此部分暴力计算
        }
        if(i + r[i] > j + r[j]){ // 如果超出 j 边界，更新当前 j 为 i
            j = i;
        }
    }
    return r;
}

void marisa(){
    string s; cin >> s;
    auto r = manacher(s);
    int ans = 0;
    for(int i = 0; i < r.size(); i ++ ){
        ans = max(ans, r[i] - 1);
    }
    cout << ans << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}