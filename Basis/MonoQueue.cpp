/**
 * 题目来源：https://www.luogu.com.cn/problem/P1886
 * 题目简介：单调队列 模板
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)

void marisa(){
	int n, k; cin >> n >> k;
	vector<int> a(n + 1);
	for(int i = 1; i <= n; i ++ ){
		cin >> a[i];
	} 
	deque<int> q;
	for(int i = 1; i <= n; i ++ ){
		while(q.size() && i - q.front() >= k){
			q.pop_front();
		}
		while(q.size() && a[q.back()] >= a[i]){
			q.pop_back();
		}
		q.push_back(i);
		if(i >= k) cout << a[q.front()] << " \n"[i == n];
	}
	q.clear();
	for(int i = 1; i <= n; i ++ ){
		while(q.size() && i - q.front() >= k){
			q.pop_front();
		}
		while(q.size() && a[q.back()] <= a[i]){
			q.pop_back();
		}
		q.push_back(i);
		if(i >= k) cout << a[q.front()] << " \n"[i == n];
	}
}

int main(){
	fastio;

	int T = 1; // cin >> T;
	while(T -- ) marisa();

	return 0;
}
