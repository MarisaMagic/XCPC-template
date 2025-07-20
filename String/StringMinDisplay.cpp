/* 字符串 最小表示法 */
string s, t;
int mn(string &s){
	int n = (int)s.size();
	s += s;
	int i, j, k;
	for(i = 0, j = 1, k; i <= n && j <= n; ){
		for(k = 0; k < n && s[i + k] == s[j + k]; k ++ );
		if(k == n) break;
		if(s[i + k] > s[j + k]){
			i += k + 1;
			if(i == j) i ++ ;
		}else{
			j += k + 1;
			if(i == j) j ++ ;
		}
	}
	return min(i, j);
}

int main(){
	cin >> s >> t;
	int slen = (int)s.size(), tlen = (int)t.size();
	int x = mn(s), y = mn(t);
	if(slen == tlen && s.substr(x, slen) == t.substr(y, tlen)){
		cout << "Yes" << endl;
	}
}