/**
 * 题目来源：https://www.luogu.com.cn/problem/P12413
 * 题目简介：三分模板
**/
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void marisa(){
	int n, w; cin >> n >> w;
	vector<int> a(n + 1);
	for(int i = 1; i <= n; i ++ ) cin >> a[i];
	sort(begin(a) + 1, end(a));

	auto check = [&](int mid){
		ll res = 1ll * mid * w;
		int cnt = mid;
		for(int i = 1; i <= n; i ++ ){
			res += max(0, a[i] - cnt);
			cnt ++ ;
		}
		return res;
	};

	int l = 0, r = 1e9;
	while(l < r){
		int lmid = l + (r - l) / 3;
		int rmid = r - (r - l) / 3;
		if(check(lmid) <= check(rmid)){
			r = rmid - 1;
		}else{
			l = lmid + 1;
		}
	}
	cout << min(check(l), check(r)) << "\n";
}

int main(){
    fastio;

    int T = 1; //cin >> T;
    while(T -- ) marisa();
    
    return 0;
}