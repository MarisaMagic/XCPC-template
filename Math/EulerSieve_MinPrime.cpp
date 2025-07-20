/**
 * 题目来源：
 * 题目简介：用最小质因子分解质因数 时间复杂度 O(\sqrt(N / logN))
**/
vector<int> primes;
int mn_p[N]; // 最小质因子

void euler_sieve(int n){
    for(int i = 2; i <= n; i ++ ){
        if(mn_p[i] == 0){ // 质数
            mn_p[i] = i;  // 最小质因子为本身
            primes.emplace_back(i);
        }
        for(auto p : primes){
            if(p * i > n) break;
            mn_p[i * p] = p; // 最小质因子
            if(p == mn_p[i]){ // i 被 p 筛过，i乘上其它质数一定会被p的倍数筛掉
                break; 
            } 
        }
    }
}

unordered_map<int, int> get_pri_fac(int x){
	unordered_map<int, int> res;
	while(x > 1){
		res[mn_p[x]] ++ ;
		x /= mn_p[x];
	}
	return res;
}