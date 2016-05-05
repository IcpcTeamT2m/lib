/* segment tree
現在のノードをkとすると
子  (k - 1) /2;
親  (k * 2)+1,(k * 2)+2;

SegmentTree<int> sg(10, 0, [](int t0, int t1) { return t0 + t1; }); //総和を求めるSegmentTree
//SegmentTree<int> sg(10, 0, [](int t0, int t1) { return min(t0,t1); }); //最小値を求める場合

sg.update(1, 5);
cout << sg.query(0, 10) << endl;
*/
template<class T>
struct SegmentTree {
	int size;

	SegmentTree(int size, T i_val, function<T(T, T)> solve)
		: i_val(i_val)
		, solve(solve)
	{
		this->size = 1;
		while (this->size < size)this->size *= 2;
		data.resize(2 * this->size - 1, i_val);
	}

	//k番目の値(0-indexed)をaに変更
	void update(int k, T a) {
		k += size - 1;
		data[k] = a;
		while (k > 0) {
			k = (k - 1) / 2;
			data[k] = solve(data[k * 2 + 1], data[k * 2 + 2]);
		}
	}
	//[a,b]の値を返す
	T query(int a, int b) {
		return query(a, b + 1, 0, 0, size);
	}

private:
	vector<T> data;
	function<T(T, T)> solve;
	T i_val;
	//[a,b)の値を返す
	//セグメントツリー内部で呼ぶ関数
	T query(int a, int b, int k, int l, int r) {
		if (r <= a || b <= l) return i_val;
		if (a <= l && r <= b) { return data[k]; }
		else {
			T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
			T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
			return solve(vl, vr);
		}
	}
};