
//unionfindにサイズ以外の値を持たせる場合
struct UnionFind {
	vector<int> to;
	vector<int> data;
	UnionFind(int size) : to(size, -1),data(size, -1) { }
	
	//集合xに集合yを足すイメージ(data[root(x | y)] = data[root(x)]になる感じ)
	bool unionSet(int x, int y) {
		x = root(x); y = root(y);
		int rootData = data[root(x)];
		if (x != y) {
			if (to[y] < to[x]) swap(x, y);
			to[x] += to[y]; to[y] = x;
		}
		setData(x, rootData);
		return x != y;
	}
	bool findSet(int x, int y) {
		return root(x) == root(y);
	}
	int root(int x) {
		return to[x] < 0 ? x : to[x] = root(to[x]);
	}
	int size(int x) {
		return -to[root(x)];
	}

	int findData(int x) {
		return data[root(x)];
	}
	void setData(int x, int d) {
		data[root(x)] = d;
	}
};
