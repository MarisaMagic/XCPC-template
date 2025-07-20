
// ----- 实现 1 -----
int n, d = 0;
int d1[N], d2[N];
vector<int> E[N];

void dfs(int u, int fa) {
    d1[u] = d2[u] = 0;
    for (int v : E[u]) {
        if (v == fa) continue;
        dfs(v, u);
        int t = d1[v] + 1;
        if (t > d1[u])
          d2[u] = d1[u], d1[u] = t;
        else if (t > d2[u])
          d2[u] = t;
    }
    d = max(d, d1[u] + d2[u]);
}

// ----- 实现 2 -----
int n, d = 0;
int dp[N]; // 以 u 为根的子树中，从u出发的最长路径
// dp[u] = max(dp[v] + w(u, v)), v \in e[u]
// ans = max(dp[u] + dp[v] + w(u, v)), v \in e[u]
vector<int> E[N];

void dfs(int u, int fa) {
    for (int v : E[u]) {
        if (v == fa) continue;
        dfs(v, u);
        d = max(d, dp[u] + dp[v] + 1);
        dp[u] = max(dp[u], dp[v] + 1);
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
    printf("%d\n", d);
    return 0;
}