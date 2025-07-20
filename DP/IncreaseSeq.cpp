/**
 * 题目来源：https://www.luogu.com.cn/problem/B3637
 * 题目简介：最长上升子序列 二分优化
**/
int dp[N]; // dp[i]: 长度为i的上升子序列的结尾，尽可能小
int a[N], n, len = 1;

int main(){
    cin >> n;
    for(int i = 1; i <= n; i ++ ) cin >> a[i];
    dp[len] = a[1];
    for(int i = 2; i <= n; i ++ ){
        if(dp[len] < a[i]){
            dp[ ++ len] = a[i];
        }else{
            int pos = LB(dp + 1, dp + len + 1, a[i]) - dp;
            dp[pos] = a[i];
        }
    }
    cout << len << "\n";

    return 0;
}