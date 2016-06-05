/* segment tree 2D

	SegmentTree2D<int> sg(h, w, 0, [](int t0, int t1) { return t0 + t1; });
	rep(y, h)rep(x, w) {
		sg.update(y, x, d[y][x]);
	}
	cout << sg.query(0, 0, 0, 5) << endl;
*/
template<class T>
struct SegmentTreeBase {
	int size;
	vector<T> data;
	T i_val;
	SegmentTreeBase(int size, T i_val)
		: i_val(i_val)
	{
		this->size = 1;
		while (this->size < size)this->size *= 2;
		data.resize(2 * this->size - 1, i_val);
	}
};
template<class T>
struct SegmentTree1D : public SegmentTreeBase<T> {
	function<T(T, T)> solve;
	SegmentTree1D(int size, T i_val, function<T(T, T)> solve)
		: SegmentTreeBase(size, i_val)
		, solve(solve)
	{}
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
		return segquery(a, b + 1, 0, 0, size);
	}
private:
	//[a,b)の値を返す
	//セグメントツリー内部で呼ぶ関数
	T segquery(int a, int b, int k, int l, int r) {
		if (r <= a || b <= l)return i_val;
		if (a <= l && r <= b) { return data[k]; }
		else {
			int vl = segquery(a, b, k * 2 + 1, l, (l + r) / 2);
			int vr = segquery(a, b, k * 2 + 2, (l + r) / 2, r);
			return solve(vl, vr);
		}
	}
};
template<class T>
struct SegmentTree2D : public SegmentTreeBase<SegmentTree1D<T>> {
	SegmentTree2D(int H, int W, T i_val, function<T(T, T)> solve)
		: SegmentTreeBase(H, SegmentTree1D<T>(W, i_val, solve))
	{}
	//(y,x)の値をaに変更
	void update(int y, int x, T a) {
		y += size - 1;
		data[y].update(x, a);
		while (y > 0) {
			y = (y - 1) / 2;
			data[y].update(x, solve(data[y * 2 + 1], data[y * 2 + 2], x, x));
		}
	}
	//(y0,x0)(y1,x0)(y0,x1)(y1,x1)の範囲の値を返す
	T query(int y0, int x0, int y1, int x1) {
		return segquery(y0, x0, y1 + 1, x1 + 1, 0, 0, size);
	}
private:
	T solve(SegmentTree1D<T> &t0, SegmentTree1D<T> &t1, int x0, int x1) {
		return data[0].solve(t0.query(x0, x1), t1.query(x0, x1));
	}
	//(y0,x0)(y1-1,x0)(y0,x1-1)(y1-1,x1-1)の範囲の値を返す
	//セグメントツリー内部で呼ぶ関数
	T segquery(int y0, int x0, int y1, int x1, int k, int l, int r) {
		if (r <= y0 || y1 <= l) return data[0].i_val;
		if (y0 <= l && r <= y1) { return data[k].query(x0, x1 - 1); }
		else {
			T vl = segquery(y0, x0, y1, x1, k * 2 + 1, l, (l + r) / 2);
			T vr = segquery(y0, x0, y1, x1, k * 2 + 2, (l + r) / 2, r);
			return data[0].solve(vl, vr);
		}
	}
};
