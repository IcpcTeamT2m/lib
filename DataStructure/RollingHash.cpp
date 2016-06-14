const ull B = 100000007;

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
