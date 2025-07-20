/**
 * 题目来源：http://acm.hdu.edu.cn/showproblem.php?pid=4135
 * 题目简介：区间 [l, r] 中与 x 互质的数的个数
**/
vector<ll> get_pri_fac(ll x){
    vector<ll> res;
    for(ll i = 2; i * i <= x; i ++ ){
        if(x % i == 0){
            res.emplace_back(i);
            while(x % i == 0) x /= i;
        }
    }
    if(x > 1) res.emplace_back(x);
    return res;
}

// 1 ~ n 中和 x 互质的数的数量
ll coprime_cnt(ll n, ll x){ 
    auto p = get_pri_fac(x);
    ll sum = 0; // 和 x 不互质的数的数量
    for(ll i = 1; i < (1ll << p.size()); i ++ ){
        // 枚举选取质因子状态
        ll d = 1, cnt = 0; // 选取质因子的乘积、选取的数量
        for(int j = 0; j < p.size(); j ++ ){
            if(i & (1 << j)){
                d *= p[j];
                cnt ++ ;
            }
        }
        if(cnt & 1) sum += n / d; // 选取质因子数量为奇数，+
        else sum -= n / d; // 选取质因子数量为偶数，- (去除重复的)
    }
    return n - sum; // 减去不互质的数的数量就是互质的数的数量
}

// 区间 l ~ r 中和 x 互质的数的数量
ll range_coprime_cnt(ll l, ll r, ll x){
    return coprime_cnt(r, x) - coprime_cnt(l - 1, x);
}