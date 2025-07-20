#include<bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

struct KM { // 匈牙利算法求二分图最大匹配
    int n1, n2; // 一部点 和 二部点 的数量
    int num; // 时间戳
    int res; // 最大匹配数量
    vector<vector<int>> e;
    vector<int> match; // 每个点的匹配
    vector<int> dfn;
    KM() {}
    KM(int n1, int n2) {
        init(n1, n2);
    }
    void init(int n1, int n2){
        this -> n1 = n1;
        this -> n2 = n2;
        num = res = 0;
        e.assign(n1 + n2 + 1, {});
        match.assign(n1 + n2 + 1, 0);
        dfn.assign(n1 + n2 + 1, 0);
    }
    void add_edge(int u, int v){
        e[u].emplace_back(v + n1); // 注意 v 保证要为 二部点
    }
    bool dfs(int u){
        for(const auto& v : e[u]){
            if(dfn[v] != num){ // 没有被访问过
                dfn[v] = num;
                // v 没有匹配的一部点 或者 当前匹配的一部点可匹配另一个二部点 
                if(!match[v] || dfs(match[v])){ 
                    match[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    int get_res(){
        for(int i = 1; i <= n1; i ++ ){
            num ++ ;
            res += dfs(i);
        }
        return res;
    }
};

void marisa(){
    int n1, n2, m; cin >> n1 >> n2 >> m;
    KM km(n1, n2);
    for(int i = 1, u, v; i <= m; i ++ ){
        cin >> u >> v;
        km.add_edge(u, v);
    }
    cout << km.get_res() << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}