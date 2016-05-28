#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>

using namespace std;

#define rep(i,n)	for(int i = 0;i < n;i++)

//幾何
#include <complex>
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

//Pの比較関数
bool operator < (const P& a, const P& b) {
	return a.X != b.X ? a.X < b.X : a.Y < b.Y;
}
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

//点と点の距離
D distPP(P a, P b) {
	return abs(a - b);
}
//直線と点の距離
D distLP(P a1, P a2, P p) {
	return abs(proj(a1, a2, p) - p);
}
//線分と点の距離
D distSP(P a1, P a2, P p) {
	P r = proj(a1, a2, p);
	if (cpSP(a1, a2, r) != EX) return abs(r - p);
	return min(abs(a1 - p), abs(a2 - p));
}
//直線と直線の距離
D distLL(P a1, P a2, P b1, P b2) {
	return cpLL(a1, a2, b1, b2) != EX ? 0 : distLP(a1, a2, b1);
}
//直線と線分の距離
D distLS(P a1, P a2, P b1, P b2) {
	return cpLS(a1, a2, b1, b2) != EX ? 0 : min(distLP(a1, a2, b1), distLP(a1, a2, b2));
}
//線分と線分の距離
D distSS(P a1, P a2, P b1, P b2) {
	if (cpSS(a1, a2, b1, b2) != EX) return 0;
	return min(min(distSP(a1, a2, b1), distSP(a1, a2, b2)),
		min(distSP(b1, b2, a1), distSP(b1, b2, a2)));
}

/* 円 */

//直線と円の距離
D distLC(P a1, P a2, P c, D r) {
	return max(distLP(a1, a2, c) - r, 0.0);
}
//線分と円の距離
D distSC(P a1, P a2, P c, D r) {
	D d1 = norm(c - a1), d2 = norm(c - a2);
	if (d1 < r * r ^ d2 < r * r)return 0; //円が線分を内包するとき距離0ならorに変える
	if (d1 < r * r & d2 < r * r)return r - sqrt(max(d1, d2));
	return max(distSP(a1, a2, c) - r, 0.0);
}
//円と円の距離
D distCC(P a, D ar, P b, D br) {
	D d = abs(a - b);
	return GE(d, abs(ar - br)) ? max(d - ar - br, 0.0) : abs(ar - br) - d;
}
//直線と円の交点
VP cpLC(P a1, P a2, P c, D r) {
	VP vp;
	P f = proj(a1, a2, c);
	if (!GE(r*r, norm(f - c)))return vp;
	P d = sqrt(max(r*r - norm(f - c), 0.0)) / abs(a2 - a1)*(a2 - a1);
	vp.push_back(f + d);
	if (!EQ(r*r, norm(f - c)))vp.push_back(f - d);
	return vp;
}
// 円と円の交点
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
