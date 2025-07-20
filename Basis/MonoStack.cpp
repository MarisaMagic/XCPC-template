/**
 * 题目来源：https://www.luogu.com.cn/problem/P5788
 * 题目简介：单调栈 模板
 * 第 i 个元素之后第一个大于 a_i 的元素对应下标
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)

void marisa(){
	int n; cin >> n;
	vector<int> a(n + 1), ans(n + 1);
	for(int i = 1; i <= n; i ++ ) cin >> a[i];
	stack<int> stk;
	stk.push(0);
	a[0] = 1e9 + 10;
	for(int i = n; i; i -- ){
		while(stk.size() && a[stk.top()] <= a[i]){
			stk.pop();
		}
		ans[i] = stk.top();
		stk.push(i); 
	}
	for(int i = 1; i <= n; i ++ ){
		cout << ans[i] << " \n"[i == n]; 
	}
}

int main(){
	fastio;

	int T = 1; // cin >> T;
	while(T -- ) marisa();

	return 0;
}
