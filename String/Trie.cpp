/**
 * 题目来源：https://www.acwing.com/problem/content/description/837/
 * 题目简介：01trie 字典树模板
**/
#include<iostream>
#include<string>
using namespace std;

const int N = 1e5 + 10;
int son[N][26];    // 一维为节点编号 每个节点最多26种状态
int cnt[N];        // 统计编号结尾的字符串
int idx;           // 分配节点编号
string s;

void insert(const string& s){
    int p = 0;   // 从根节点开始
    for(const auto& ch : s){
        int c = ch - 'a';
        if(!son[p][c]) son[p][c] = ++ idx;   // 不存在就分配一个编号
        p = son[p][c];
    }
    cnt[p] ++ ;    // 统计以编号p结尾的字符串
}

int query(const string& s){
    int p = 0;   // 从根节点开始
    for(const auto& ch : s){
        int c = ch - 'a';
        if(!son[p][c]) return 0;   // 不存在
        p = son[p][c];
    }
    return cnt[p];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n; cin >> n;
    while(n -- ){
        char op; cin >> op >> s;
        if(op == 'I') insert(s);
        else cout << query(s) << endl;
    }
}