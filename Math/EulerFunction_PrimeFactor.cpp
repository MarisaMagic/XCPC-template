#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false), cin.tie(0)
using ll = long long;

// 欧拉函数 phi(n): 小于等于n的与n互质的数的数量
// phi(1) = 1

// 质因数分解求单个数的欧拉函数
int euler_phi(int n){
	int ans = n;
	for(int i = 2; i * i <= n; i ++ ){
		if(n % i == 0){
			ans = ans / i * (i - 1);
			while(n % i == 0){
				n /= i;
			}
		}
	}
	if(n > 1) ans = ans / n * (n - 1);
	return ans;
}

void marisa(){
    
}

int main(){
    fastio;

    int T = 1; // cin >> T;
    while(T -- ) marisa();
    
    return 0;
}