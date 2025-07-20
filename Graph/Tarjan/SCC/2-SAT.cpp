/**
 * 题目来源：https://www.luogu.com.cn/problem/P4782
 * 题目简介：2-SAT 模板
 * n 个条件 x_1, x_2, ... , x_n
 * m 对矛盾关系 (a, b) ，每个关系中至少要有一个成立
 * 例如 a=1, b=1，-a -> b, -b -> a 
 * 即要么a不成立b成立，要么a成立b不成立
 * 是否能选出 n 个互相不矛盾的条件
**/
#include<bits/stdc++.h>
using namespace std;

#define ios ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
const int N = 1e6 + 10;
// a = 1, b = 1: -a -> b, -b -> a
// a = 0, b = 1: a -> b, -b -> -a
// a = 1, b = 0: -a -> -b, -a -> b
// a = 0, b = 0: a -> -b, b -> -a
// x 与 -x 在同一scc内，无解（c[x] == c[x+n]）
// 输出方案时可以通过变量在图中的拓扑序确定该变量的取值。
// 如果变量 x 的拓扑序在 -x 之后，那么取 x 值为真。
// 应用到 Tarjan 算法的缩点，即 x 所在 SCC 编号在 -x 之前时，取 x 为真。
// 因为 Tarjan 使用了栈，所以求得的 SCC 编号相当于反拓扑序。
int n, m;
vector<int> e[N << 1];
int low[N << 1], dfn[N << 1], num;
int st[N << 1], top;
bool in_st[N << 1];
int id[N << 1], scc_cnt;

void tarjan(int u){
    low[u] = dfn[u] = ++ num;
    st[ ++ top] = u, in_st[u] = true;
    for(auto &v : e[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }else if(in_st[v]) low[u] = min(low[u], dfn[v]);
    }

    if(dfn[u] == low[u]){
        scc_cnt ++ ;
        int v;
        do{
            v = st[top -- ], in_st[v] = false;
            id[v] = scc_cnt;
        }while(u ^ v);
    }
}

int main(){
    ios;

    cin >> n >> m;
    for(int i = 1, a, va, b, vb; i <= m; i ++ ){
        cin >> a >> va >> b >> vb;
        e[a + n * (va & 1)].emplace_back(b + n * (vb ^ 1));
        e[b + n * (vb & 1)].emplace_back(a + n * (va ^ 1));
    }

    for(int i = 1; i <= (n << 1); i ++ ) 
    	if(!dfn[i]) tarjan(i);

    for(int i = 1; i <= n; i ++ )
        if(id[i] == id[i + n]){
            cout << "IMPOSSIBLE" << "\n";
            return 0;
        }

    cout << "POSSIBLE" << "\n";
    for(int i = 1; i <= n; i ++ ){
    	cout << (id[i] < id[i + n]) << ' ';
    }

    return 0;
}