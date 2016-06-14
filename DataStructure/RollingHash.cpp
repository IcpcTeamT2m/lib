const ull B = 100000007;

//bにaが含まれているか
bool contain(string a, string b) {
	int al = a.size(), bl = b.size();
	if (al > bl)return false;
	ull t = 1;
	for (int i = 0; i < al; i++) t *= B;
	ull ah = 0, bh = 0;
	for (int i = 0; i < al; i++) ah = ah * B + a[i];
	for (int i = 0; i < al; i++) bh = bh * B + b[i];

	for (int i = 0; i + al <= bl; i++) {
		if (ah == bh) return true;
		if (i + al < bl) bh = bh * B + b[i + al] - b[i] * t;
	}
	return false;
}

int overlap(string a, string b) {
	int al = a.size(), bl = b.size();
	int ans = 0;
	ull ah = 0, bh = 0, t = 1;
	for (int i = 1; i <= min(al, bl); i++) {
		ah = ah + a[al - i] * t;
		bh = bh * B + b[i - 1];
		if (ah == bh) ans = i;
		t *= B;
	}
	return ans;
}

struct RHS {
	int n;
	string s;
	vector<ull> hs; //ハッシュの累積和
	vector<ull> bp; //bの累乗の結果を記録する(オーバーフローを考慮)
	const ull b = 1e9 + 7;
	//初期化
	RHS(string s) : n(s.size()), s(s), hs(n+1) , bp(n+1){
		bp[0] = 1;
		rep(i, n) {
			bp[i + 1] = bp[i] * b;
			hs[i + 1] = hs[i] * b + s[i];
		}
	}
	//s[l,r]のハッシュ値を返す
	ull subhash(int l, int r) {
		return hs[r+1] - hs[l] * bp[r+1 - l];
	}
};

