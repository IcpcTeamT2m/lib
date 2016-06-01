const MAX_V = 100;

struct edge { int to, cap, rev; };
vector<edge> G[MAX_V];
bool used[MAX_V];

void clear() {
	rep(i, MAX_V) {
		G[i].clear();
		used[i] = false;
	}
}

void add_edge(int from, int to, int cap) {
	G[from].push_back(edge{ to, cap, int(G[to].size()) });
	G[to].push_back(edge{ from, 0, int(G[from].size()) - 1 });
}

int dfs(int v, int t, int f) {
	if (v == t)return f;
	used[v] = true;
	rep(i, G[v].size()) {
		edge &e = G[v][i];
		if (!used[e.to] && e.cap > 0) {
			int d = dfs(e.to, t, min(f, e.cap));
			if (d > 0) {
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}
int max_flow(int s, int t) {
	int flow = 0;
	for (;;) {
		clr(used);
		int f = dfs(s, t, INF);
		if (f == 0)return flow;
		flow += f;
	}
}
