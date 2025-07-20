#include<bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
const int N = 1010;

int n1, n2, m;
vector<int> e[N];
int match[N], dfn[N], num;

bool find(int u){
    for(const auto &v : e[u]){
        if(dfn[v] != num){ // 没有被访问过
            dfn[v] = num;
            // v 没有匹配的一部点 或者 当前匹配的一部点可匹配另一个二部点 
            if(!match[v] || find(match[v])){ 
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

void marisa(){
    cin >> n1 >> n2 >> m;
    for(int i = 1, u, v; i <= m; i ++ ){
        cin >> u >> v;
        e[u].emplace_back(v + n1);
    }
    int ans = 0;
    for(int i = 1; i <= n1; i ++ ){
        num ++ ;
        ans += find(i);
    }
    cout << ans << "\n";
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}