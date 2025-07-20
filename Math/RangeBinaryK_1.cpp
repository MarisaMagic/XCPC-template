// 0 ~ x 范围内二进制第 k 位为 1 的数的个数
inline ll f(ll x, int k){
    ll res = 0;
    if((x & (1ll << k)) == 0){ // 第 k 位为 0
        res = (x >> k) / 2; // 完整的 (x >> k) 组，每组中 (1 << k) 个数
        res <<= k; // 每组中 一半的 数第 k 位上为 1（先除 2 再左移 k，防止出错）
    }else{
        res = x >> (k + 1); // 完整的 (x >> (k + 1)) 组，每组 (1 << (k + 1)) 个数
        res <<= k; // 每组中 一半的 数第 k 位上为 1
        res += (x % (1ll << k)) + 1; // 加上剩余不足 (1 << k) 的贡献
    }
    return res;
}

inline ll range_cnt_k1(ll x, ll y, int k){
    return f(y, k) - f(x - 1, k);
}