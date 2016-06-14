
//scc[i] 頂点iが属している強連結成分
vector<int> scc(vector<vector<int>> &g) {
	int n = g.size();
	vector<int> vs, cmp(n), f(n, 0);
	vector<vector<int>> rg(n);//逆グラフ
	rep(i, n)each(j, g[i]) {
		rg[j].push_back(i);
	}
	function<void(int)> dfs = [&](int v) {
		f[v] = 1;
		each(i, g[v]) {
			if (!f[i])dfs(i);
		}
		vs.push_back(v);
	};
	function<void(int, int)> rdfs = [&](int v, int k) {
		f[v] = 1;
		cmp[v] = k;
		each(i, rg[v]) {
			if (!f[i]) rdfs(i, k);
		}
	};
	rep(i, n) {
		if (!f[i])dfs(i);
	}
	fill(all(f), 0);
	int k = 0;
	for (int i = vs.size() - 1; i >= 0; i--) {
		if (!f[vs[i]])rdfs(vs[i], k++);
	}
	return cmp;
}

//scc_set[i] 強連結成分iが含んでいる頂点の集合
vector<set<int>> scc_set(vector<vector<int>> &g) {
	auto cmp = scc(g);
	int n = g.size();
	vector<set<int>> sv(n);
	int k = 0;
	rep(i, n) {
		sv[cmp[i]].insert(i);
		k = max(cmp[i] + 1, k);
	}
	sv.resize(k);
	return sv;
}
