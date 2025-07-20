/**
 * 题目来源：https://www.luogu.com.cn/problem/P3384
 * 题目简介：树链剖分模板
**/
int h[N], e[M], ne[M], idx;
int a[N], tmp[N];
int sum[N << 2], lazy[N << 2];  // segment tree
int son[N]; // 重儿子编号
int id[N];  // 新编号
int fa[N];  // 父节点
int dep[N]; // 节点深度
int siz[N]; // 子树大小
int top[N]; // 当前链的顶端
int num;    // dfn序
int n, m, root, mod;

void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

//------------------------线段树----------------------------
void pushup(int u){
    sum[u] = (sum[u << 1] + sum[u << 1 | 1]) % mod;
}

void pushdown(int u, int l, int r){
    if(lazy[u]){
        int mid = l + r >> 1;
        lazy[u << 1] += lazy[u], sum[u << 1] = (sum[u << 1] + lazy[u] * (mid - l + 1)) % mod;
        lazy[u << 1 | 1] += lazy[u], sum[u << 1 | 1] = (sum[u << 1 | 1] + lazy[u] * (r - mid)) % mod;
        lazy[u] = 0;
    }
}

void build(int u, int l, int r){
    if(l == r){ sum[u] = tmp[l] % mod; return; }
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

int query(int u, int l, int r, int ql, int qr){
    if(ql <= l && r <= qr) return sum[u];
    pushdown(u, l, r);
    int mid = l + r >> 1, res = 0;
    if(ql <= mid) res = (res + query(u << 1, l, mid, ql, qr)) % mod;
    if(qr > mid) res = (res + query(u << 1 | 1, mid + 1, r, ql, qr)) % mod;
    return res;
}

void update(int u, int l, int r, int ql, int qr, int d){
    if(ql <= l && r <= qr) { lazy[u] += d, sum[u] = (sum[u] + d * (r - l + 1)) % mod; return; }
    pushdown(u, l, r);
    int mid = l + r >> 1;
    if(ql <= mid) update(u << 1, l, mid, ql, qr, d);
    if(qr > mid) update(u << 1 | 1, mid + 1, r, ql, qr, d);
    pushup(u);
}
//-----------------------------------------------------------

// 询问区间和
int qRange(int x, int y){
    int ans = 0, res;
    while(top[x] ^ top[y]){   // 两个点不在同一条链上
        if(dep[top[x]] < dep[top[y]]) swap(x, y);   // 将x点改为深度更深的点
        res = query(1, 1, n, id[top[x]], id[x]);// x到x的顶端 区间点权和
        ans = (ans + res) % mod;
        x = fa[top[x]];    // 跳到链顶端的父节点
    }
    // 最后两个点处于同一链上
    if(dep[x] > dep[y]) swap(x, y);
    res = query(1, 1, n, id[x], id[y]); // 加上两个点之间的区间点权和
    ans = (ans + res) % mod;
    return ans;
}

// 更新区间
void updRange(int x, int y, int d){
    while(top[x] ^ top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        update(1, 1, n, id[top[x]], id[x], d % mod);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    update(1, 1, n, id[x], id[y], d % mod);
}

// 询问子树点权和
int qSon(int x){
    return query(1, 1, n, id[x], id[x] + siz[x] - 1);  // 子树区间的右端点为id[x] + siz[x] - 1
}

// 更新整个子树
void updSon(int x, int d){
    update(1, 1, n, id[x], id[x] + siz[x] - 1, d % mod);
}


void dfs1(int u, int f, int depth){
    dep[u] = depth;  // 标记节点深度
    fa[u] = f;       // 记录父节点
    siz[u] = 1;      // 维护子树大小 （包括根节点）
    int mxson = -1;   // 记录重儿子数量
    for(int i = h[u]; ~i; i = ne[i]){
        int v = e[i];
        if(v == f) continue;
        dfs1(v, u, depth + 1);
        siz[u] += siz[v];     // 自底向上
        if(siz[v] > mxson) son[u] = v, mxson = siz[v];
    }
}

void dfs2(int u, int topf){
    id[u] = ++ num;      // 新编号 dfn序
    tmp[num] = a[u];     // 点权赋值到新的编号
    top[u] = topf;       // 所在顶端
    if(!son[u]) return;  // 没有儿子直接return
    dfs2(son[u], topf);  // 先处理重儿子
    for(int i = h[u]; ~i; i = ne[i]){
        int v = e[i];
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v, v);   // 对于每一个轻儿子都有一条从它自己开始的链 
    }
}

int main(){
    ios;

    int T = 1; //cin >> T;
    while(T -- ){
        memset(h, -1, sizeof h);
        cin >> n >> m >> root >> mod;
        for(int i = 1; i <= n; i ++ ) cin >> a[i];
        for(int i = 1, u, v; i < n; i ++ ) cin >> u >> v, add(u, v), add(v, u);
        
        dfs1(root, -1, 1);
        dfs2(root, root);

        build(1, 1, n);

        while(m -- ){
            int op, x, y, z;
            cin >> op;
            if(op == 1){
                cin >> x >> y >> z;
                updRange(x, y, z); // x -> y 上所有节点 +z
            }else if(op == 2){
                cin >> x >> y;
                cout << qRange(x, y) << endl; // x -> y 所有的节点权值和
            }else if(op == 3){
                cin >> x >> y;
                updSon(x, y); // x 为根子树内所有节点 +z
            }else{
                cin >> x;
                cout << qSon(x) << endl; // x 为根子树内所有节点权值和
            }
        }
    }

    return 0;
}