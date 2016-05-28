#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

#define rep(i,n)	for(int i = 0;i < n;i++)

//幾何
#include <complex>
typedef double D;		//座標値の型
typedef complex<D> P;	//Point
typedef pair<P, P> L;	//Line

const D EPS = 1e-9; //許容誤差
const D INF = 1e12;

//実数をX座標 虚数をY座標として扱う
#define X real()
#define Y imag()

//許容誤差を考慮した判定処理
#define LE(n,m) ((n) < (m) + EPS)	// n < m
#define GE(n,m) ((n) + EPS > (m))	// n > m
#define EQ(n,m) (abs((n)-(m)) < EPS)// n == m

#define S first  //始点
#define T second //終点
#define EX P(INF,INF) //例外

//Pの比較関数
bool operator < (const P& a, const P& b) {
	return a.X != b.X ? a.X < b.X : a.Y < b.Y;
}

//外積 cross(a,b) = |a||b|sinθ
double cross(P a, P b) {
	return (conj(a) * b).Y;
}
//内積 dot(a,b) = |a||b|cosθ
double dot(P a, P b) {
	return (conj(a) * b).X;
}
//点間のユークリッド距離
double dist(P a, P b) {
	return sqrt((a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y));
}
//線分(a,b)上にcが存在するか isPointOnLine
bool isPOL(P a, P b, P c) {
	return abs(a - c) + abs(c - b) < abs(a - b) + EPS;
}
//線分と線分の交点取得
P crosspointLL(P a1, P a2, P b1, P b2) {
	D d1 = cross(b2 - b1, b1 - a1);
	D d2 = cross(b2 - b1, a2 - a1);
	if (EQ(d2, 0)) {
		return EX; //平行
	}
	P ret = a1 + d1 / d2 * (a2 - a1);
	if (isPOL(b1, b2, ret) &&
		isPOL(a1, a2, ret)) {
		return ret;
	}
	else {
		return EX; //交点が線上にない
	}
}
