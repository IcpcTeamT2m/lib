#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>

using namespace std;

#define rep(i,n)	for(int i = 0;i < n;i++)
#define all(n)	n.begin(),n.end()

//幾何
#include <complex>
#include <math.h>

typedef double D;	//座標値の型
typedef complex<D> P;	//Point
typedef pair<P, P> L;	//Line
typedef vector<P> VP;	//Polygon

const D EPS = 1e-9; //許容誤差
const D INF = 1e12;

//実数をX座標 虚数をY座標として扱う
#define X real()
#define Y imag()

//許容誤差を考慮した判定処理
#define LE(n,m) ((n) < (m) + EPS)	// n < m
#define GE(n,m) ((n) + EPS > (m))	// n > m
#define EQ(n,m) (abs((n)-(m)) < EPS)	// n == m

#define S first  //始点
#define T second //終点
#define EX P(INF,INF) //例外

//外積 cs(a,b) = cross(a,b) = |a||b|sinθ
D cs(P a, P b) {
	return (conj(a) * b).Y;
}
//内積 dt(a,b) = dot(a,b) = |a||b|cosθ
D dt(P a, P b) {
	return (conj(a) * b).X;
}
//点pの直線aへの射影点
P proj(P a1, P a2, P p) {
	return a1 + dt(a2 - a1, p - a1) / norm(a2 - a1) * (a2 - a1);
}
// 点pの直線aへの反射点を返す
P reflec(P a1, P a2, P p) {
	return 2.0 * proj(a1, a2, p) - p;
}

//点の進行方向 counter clock wise
int ccw(P a, P b, P c) {
	b -= a; c -= a;
	if (cs(b, c) > +EPS)return +1;		//逆時計回り
	if (cs(b, c) < -EPS)return -1;		//時計回り
	if (dt(b, c) < -EPS)return +2;		//c--a--bで平行
	if (norm(b) < norm(c))return -2;	//a--b--cで平行 or a == b
	return 0;							//a--c--bで平行 or a == c or b == c
}
//線分(a,b)上にcが存在するか isPointOnLine
bool isPOL(P a, P b, P c) {
	return abs(a - c) + abs(c - b) < abs(a - b) + EPS;
}

/* 交点取得 */

//直線と点の交点取得 CrossPointLinePoint
P cpLP(P a1, P a2, P b) {
	if (EQ(cs(a2 - a1, b - a1), 0))return b;
	return EX;
}
//線分と点の交点取得 CrossPointSegmentPoint
P cpSP(P a1, P a2, P b) {
	if (isPOL(a1, a2, b))return b;
	return EX;
}
//直線と直線の交点取得 CrossPointLineLine
P cpLL(P a1, P a2, P b1, P b2) {
	D d1 = cs(b2 - b1, b1 - a1);
	D d2 = cs(b2 - b1, a2 - a1);
	if (EQ(d2, 0))return EX; //平行
							 //交点計算
	return a1 + d1 / d2 * (a2 - a1);
}
//直線と線分の交点取得 CrossPointLineSegment
P cpLS(P a1, P a2, P b1, P b2) {
	P r = cpLL(a1, a2, b1, b2);
	if (isPOL(b1, b2, r))return r; //線分a1,a2上にrがあるか
	return EX; //交点が線上にない
}
//線分と線分の交点取得 CrossPointSegmentSegment
P cpSS(P a1, P a2, P b1, P b2) {
	P r = cpLL(a1, a2, b1, b2);
	if (isPOL(a1, a2, r) && isPOL(b1, b2, r)) return r;
	return EX; //交点が線上にない
}

/* ユークリッド距離 */

//点と点の距離 distPointPoint
D distPP(P a, P b) {
	return abs(a - b);
}
//直線と点の距離 distLintPoint
D distLP(P a1, P a2, P p) {
	return abs(proj(a1, a2, p) - p);
}
//線分と点の距離 distSegmentPoint
D distSP(P a1, P a2, P p) {
	P r = proj(a1, a2, p);
	if (cpSP(a1, a2, r) != EX) return abs(r - p);
	return min(abs(a1 - p), abs(a2 - p));
}
//直線と直線の距離 distLineLine
D distLL(P a1, P a2, P b1, P b2) {
	return cpLL(a1, a2, b1, b2) != EX ? 0 : distLP(a1, a2, b1);
}
//直線と線分の距離 distLineSegment
D distLS(P a1, P a2, P b1, P b2) {
	return cpLS(a1, a2, b1, b2) != EX ? 0 : min(distLP(a1, a2, b1), distLP(a1, a2, b2));
}
//線分と線分の距離 distSegmentSegment
D distSS(P a1, P a2, P b1, P b2) {
	if (cpSS(a1, a2, b1, b2) != EX) return 0;
	return min(min(distSP(a1, a2, b1), distSP(a1, a2, b2)),
		min(distSP(b1, b2, a1), distSP(b1, b2, a2)));
}

/* 円 */

//直線と円の距離 distLineCircle
D distLC(P a1, P a2, P c, D r) {
	return max(distLP(a1, a2, c) - r, 0.0);
}
//線分と円の距離 distSegmentCircle
D distSC(P a1, P a2, P c, D r) {
	D d1 = norm(c - a1), d2 = norm(c - a2);
	if (d1 < r * r ^ d2 < r * r)return 0; //円が線分を内包するとき距離0ならorに変える
	if (d1 < r * r & d2 < r * r)return r - sqrt(max(d1, d2));
	return max(distSP(a1, a2, c) - r, 0.0);
}
//円と円の距離 distCircleCircle
D distCC(P a, D ar, P b, D br) {
	D d = abs(a - b);
	return GE(d, abs(ar - br)) ? max(d - ar - br, 0.0) : abs(ar - br) - d;
}
//直線と円の交点 crosspointLineCircle
VP cpLC(P a1, P a2, P c, D r) {
	VP vp;
	P f = proj(a1, a2, c);
	if (!GE(r*r, norm(f - c)))return vp;
	P d = sqrt(max(r*r - norm(f - c), 0.0)) / abs(a2 - a1)*(a2 - a1);
	vp.push_back(f + d);
	if (!EQ(r*r, norm(f - c)))vp.push_back(f - d);
	return vp;
}
// 円と円の交点 crosspointCircleCircle
VP cpCC(P a, D ar, P b, D br) {
	VP ps;
	P c = b - a;
	D d = abs(c);
	D l = (norm(c) + ar*ar - br*br) / (2 * d);
	if (EQ(d, 0) || ar < abs(l)) return ps;

	P n = c * P(0, sqrt(ar*ar - l*l) / d);
	P cp = a + l / d * c;
	ps.push_back(cp + n);
	if (!EQ(norm(n), 0)) ps.push_back(cp - n);
	return ps;
}

//点pから円aへの接線の接点 tangentPoints
VP tgP(P a, D ar, P p) {
	VP ps;
	D s = ar / abs(p - a);
	if (!LE(s, 1))return ps;
	D t = acos(-1) / 2.0 - asin(min(s, 1.0));
	ps.push_back(a + (p - a) * polar(s, t));
	if (!EQ(s, 1)) {
		ps.push_back(a + (p - a) * polar(s, -t));
	}
	return ps;
}

// 2円の共通接線。返される各直線に含まれる頂点は円との接点となる tangentLines
vector<L> tgL(P a, D ar, P b, D br) {
	vector<L> ls;
	D d = abs(b - a);
	rep(i, 2) {
		D s = (ar - (1 - i * 2)*br) / d;
		if (!LE(s*s, 1)) break;
		D c = sqrt(max(1 - s*s, 0.0));
		rep(j, 2) {
			P n = (b - a) * P(s, (1 - j * 2)*c) / d;
			ls.push_back(L(a + ar*n, b + (1 - i * 2)*br*n));
			if (c < EPS) break;  // 重複する接線を無視（重複していいならこの行不要）
		}
	}
	return ls;
}

// 三角形の外心。点a,b,cは同一線上にあってはならない circumcenter
P cmc(P a, P b, P c) {
	a = (a - c)*0.5;
	b = (b - c)*0.5;
	return c + cpLL(a, a*P(1, 1), b, b*P(1, 1));
}

// 点aと点bを通り、半径がrの円の中心を返す circlesPointsRadius
VP cpr(P a, P b, D r) {
	VP cs;
	P h = (b - a)*0.5;
	D d = abs(h);
	if (d == 0 || d > r) return cs;	// 必要なら !LE(d,r) として円1つになる側へ丸める
	D N = sqrt(r*r - d*d);			// 必要なら max(r*r - d*d, 0) とする
	P n = h * P(0, 1) * (N / d);
	cs.push_back(a + h + n);
	if (N > 0) cs.push_back(a + h - n);
	return cs;
}

// 点aと点bを通り、直線lに接する円の中心 circlesPointsTangent
VP cpt(P a, P b, P l1, P l2) {
	P n = (l2 - l1) * P(0, 1);
	P m = (b - a) * P(0, 0.5);
	D c = dt((a + b)*0.5 - l1, n),
		qa = norm(n)*norm(m) - dt(n, m)*dt(n, m),
		qb = -c * dt(n, m),
		qc = norm(n)*norm(m) - c*c,
		qd = qb*qb - qa*qc;  // qa*k^2 + 2*qb*k + qc = 0
	VP cs;
	if (qd < -EPS) return cs;
	if (EQ(qa, 0)) {
		if (!EQ(qb, 0)) cs.push_back((a + b)*0.5 - m * (qc / qb / 2));
		return cs;
	}
	D t = -qb / qa;
	cs.push_back((a + b)*0.5 + m * (t + sqrt(max(qd, 0.0)) / qa));
	if (qd > EPS) cs.push_back((a + b)*0.5 + m * (t - sqrt(max(qd, 0.0)) / qa));
	return cs;
}

// 点集合を含む最小の円の中心 minEnclosingCircle
P mec(const VP& ps) {
	P c;
	double m = 0.5;
	rep(i, 39) {  // 2^(-39-1) \approx 0.9e-12
		rep(t, 50) {
			D ma = 0;
			int k = 0;
			rep(j, ps.size()) if (ma < norm(ps[j] - c)) {
				ma = norm(ps[j] - c);
				k = j;
			}
			c += (ps[k] - c) * m;
		}
		m /= 2;
	}
	return c;
}

/* 多角形 */

//Pの比較関数
bool operator < (const P& a, const P& b) {
	return a.X != b.X ? a.X < b.X : a.Y < b.Y;
}

//凸包 convexHull
VP cvh(VP ps) { // 元の点集合がソートされていいならVP&に
	int n = ps.size(), k = 0;
	sort(ps.begin(), ps.end());
	VP ch(2 * n);
	for (int i = 0; i < n; ch[k++] = ps[i++]) // lower-hull
		while (k >= 2 && ccw(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;	// 余計な点も含むなら == -1 とする
	for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = ps[i--])			// upper-hull
		while (k >= t && ccw(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;
	ch.resize(k - 1);
	return ch;
}

// 凸判定。縮退を認めないならccwの判定部分を != 1 とする isCcwConvex
bool iscv(const VP& ps) {
	int n = ps.size();
	rep(i, n) if (ccw(ps[i], ps[(i + 1) % n], ps[(i + 2) % n]) == -1) return false;
	return true;
}

// 凸多角形の内部判定　O(n) inConvex
// 点が領域内部なら1、境界上なら2、外部なら0を返す
int incv(P p, const VP& ps) {
	int n = ps.size();
	int dir = ccw(ps[0], ps[1], p);
	rep(i, n) {
		int ccwc = ccw(ps[i], ps[(i + 1) % n], p);
		if (!ccwc) return 2;  // 線分上に存在
		if (ccwc != dir) return 0;
	}
	return 1;
}

// 凸多角形の内部判定　O(logn) inCcwConvex
// 点が領域内部なら1、境界上なら2、外部なら0を返す
int incv(const VP& ps, P p) {
	int n = ps.size();
	P g = (ps[0] + ps[n / 3] + ps[n * 2 / 3]) / 3.0;
	if (g == p) return 1;
	P gp = p - g;

	int l = 0, r = n;
	while (l + 1 < r) {
		int m = (l + r) / 2;
		P gl = ps[l] - g;
		P gm = ps[m] - g;
		if (cs(gl, gm) > 0) {
			if (cs(gl, gp) >= 0 && cs(gm, gp) <= 0) r = m;
			else l = m;
		}
		else {
			if (cs(gl, gp) <= 0 && cs(gm, gp) >= 0) l = m;
			else r = m;
		}
	}
	r %= n;
	D cr = cs(ps[l] - p, ps[r] - p);
	return EQ(cr, 0) ? 2 : cr < 0 ? 0 : 1;
}

// 多角形の内部判定 inPolygon
// 点が領域内部なら1、境界上なら2、外部なら0を返す
int inpg(const VP& ps, P p) {
	int n = ps.size();
	int in = 0;
	rep(i, n) {
		P a = ps[i] - p;
		P b = ps[(i + 1) % n] - p;
		if (EQ(cs(a, b), 0) && LE(dt(a, b), 0)) return 2;
		if (a.Y > b.Y) swap(a, b);
		if ((a.Y*b.Y < 0 || (a.Y*b.Y < EPS && b.Y > EPS)) && LE(cs(a, b), 0)) in = !in;
	}
	return in;
}

// 凸多角形クリッピング convexCut
VP cvcut(const VP& ps, P a, P b) {
	int n = ps.size();
	VP r;
	rep(i, n) {
		int cc = ccw(a, b, ps[i]);
		if (cc != -1) r.push_back(ps[i]);
		int cn = ccw(a, b, ps[(i + 1) % n]);
		if (cc * cn == -1) r.push_back(cpLL(a, b, ps[i], ps[(i + 1) % n]));
	}
	return r;
}

// 凸多角形の直径（最遠点対）convexDiameter
pair<int, int> cvdm(const VP& ps) {
	int n = ps.size();
	int i = min_element(all(ps)) - ps.begin();
	int j = max_element(all(ps)) - ps.begin();
	int mi, mj;
	D md = 0;
	rep(k, 2 * n) {
		if (md < norm(ps[i] - ps[j])) {
			md = norm(ps[i] - ps[j]);
			mi = i;
			mj = j;
		}
		if (cs(ps[i] - ps[(i + 1) % n], ps[(j + 1) % n] - ps[j]) <= 0) j = (j + 1) % n;
		else i = (i + 1) % n;
	}
	return make_pair(mi, mj);
}

// 多角形の符号付面積
D area(const VP& ps) {
	D a = 0;
	rep(i, ps.size()) a += cs(ps[i], ps[(i + 1) % ps.size()]);
	return a / 2;
}

// 多角形の幾何学的重心 centroid
P ctd(const VP& ps) {
	int n = ps.size();
	D s = 0;
	P c;
	rep(i, n) {
		D a = cs(ps[i], ps[(i + 1) % n]);
		s += a;
		c += (ps[i] + ps[(i + 1) % n]) * a;
	}
	return 1 / s / 3 * c;
}

// ボロノイ領域 voronoiCell
VP vrc(P p, const VP& ps, const VP& o) {
	VP cl = o;
	rep(i, ps.size()) {
		if (EQ(norm(ps[i] - p), 0)) continue;
		P h = (p + ps[i])*0.5;
		cl = cvcut(cl, h, h + (ps[i] - h)*P(0, 1));
	}
	return cl;
}

/* 幾何グラフ */

struct Edge {
	int f, t;
	D c;
	Edge(int from, int to, D cost) : f(from), t(to), c(cost) {}
};
struct Graph {
	int n;
	vector<vector<Edge>> E;
	Graph(int n) : n(n), E(n) {}
	void addEdge(Edge e) {
		E[e.f].push_back(e);
		E[e.t].push_back(Edge(e.t, e.f, e.c));
	}
};

// 線分アレンジメント（線分の位置関係からグラフを作成）segmentArrangement
Graph sar(const vector<L>& segs, VP& ps) {
	int n = segs.size();
	rep(i, n) {
		ps.push_back(segs[i].first);
		ps.push_back(segs[i].second);
		rep(j, i) {
			if (cpSS(segs[i].first, segs[i].second, segs[j].first, segs[j].second) != EX) {
				ps.push_back(cpLL(segs[i].first, segs[i].second, segs[j].first, segs[j].second));
			}
		}
	}
	sort(ps.begin(), ps.end());
	ps.erase(unique(ps.begin(), ps.end()), ps.end());

	int m = ps.size();
	Graph gr(m);
	vector<pair<D, int> > list;
	rep(i, n) {
		list.clear();
		rep(j, m) {
			if (cpSP(segs[i].first, segs[i].second, ps[j]) != EX) {
				list.push_back(make_pair(norm(segs[i].first - ps[j]), j));
			}
		}
		sort(list.begin(), list.end());
		rep(j, list.size() - 1) {
			int a = list[j].second;
			int b = list[j + 1].second;
			gr.addEdge(Edge(a, b, abs(ps[a] - ps[b])));
		}
	}
	return gr;
}

// 可視グラフ（点集合から見える位置へ辺を張ったグラフ）visibilityGraph
Graph vbg(const VP& ps, const vector<VP>& objs) {
	int n = ps.size();
	Graph gr(n);
	rep(i, n) rep(j, i) {
		P a = ps[i], b = ps[j];
		if (!EQ(norm(a - b), 0)) rep(k, objs.size()) {
			const VP& obj = objs[k];
			int inStA = incv(a, obj);
			int inStB = incv(b, obj);
			if ((inStA ^ inStB) % 2 || inStA * inStB != 1 && incv((a + b)*0.5, obj) == 1) goto skip;
			rep(l, obj.size()) {
				P cur = obj[l];
				P next = obj[(l + 1) % obj.size()];
				if (cpSS(a, b, cur, next) != EX && cpSP(cur, next, a) == EX && cpSP(cur, next, b) == EX) goto skip;
			}
		}
		gr.addEdge(Edge(i, j, abs(a - b)));
	skip: {}
	}
	return gr;
}


/* その他 */

// 重複する線分を併合する mergeSegments
vector<L> mgs(vector<L> sg) {
	int n = sg.size();
	rep(i, n) if (sg[i].second < sg[i].first) swap(sg[i].second, sg[i].first);

	rep(i, n) rep(j, i) {
		L &l1 = sg[i], &l2 = sg[j];
		if (EQ(cs(l1.second - l1.first, l2.second - l2.first), 0)
			&& cpLP(l1.first, l1.second, l2.first) != EX
			&& ccw(l1.first, l1.second, l2.second) != 2
			&& ccw(l2.first, l2.second, l1.second) != 2) {
			sg[j] = L(min(l1.first, l2.first), max(l1.second, l2.second));
			sg[i--] = sg[--n];
			break;
		}
	}
	sg.resize(n);
	return sg;
}


// 余弦定理
// △ABC において、a = BC, b = CA, c = AB としたとき
// a^2 = b^2 + c^2 ? 2bc cos ∠CAB

// ヘロンの公式
// 3辺の長さがa,b,cである三角形の面積T
// T = sqrt{ s(s-a)(s-b)(s-c) }, s = (a+b+c)/2

// ピックの定理
// 多角形の頂点が全て格子点上にあり、内部に穴がないとき
// S = i + b/2 - 1 (S:多角形の面積, i: 多角形の内部にある格子点の数, b: 辺上の格子点の数)
