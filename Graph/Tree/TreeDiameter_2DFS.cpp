/**
 * 题目来源：
 * 题目简介：两次dfs求树的直径
**/
int n, c, d[N];
vector<int> E[N];

void dfs(int u, int fa) {
    for (int v : E[u]) {
        if (v == fa) continue;
        d[v] = d[u] + 1;
        if (d[v] > d[c]) c = v; // 更新最远点
        dfs(v, u);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs(1, 0);
    d[c] = 0;
    dfs(c, 0); // 从最远点开始第二次dfs
    printf("%d\n", d[c]);
    return 0;
}