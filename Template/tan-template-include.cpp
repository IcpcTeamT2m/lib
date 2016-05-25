//include
//------------------------------------------
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<stack>
#include<queue>
#include<algorithm>

using namespace std;

//型変換(int < == > string)
//------------------------------------------

//string型をint型に
int StrtoInt(string s) { int v; stringstream StringIn(s); StringIn >> v; return v; }

// 数値ををstring型に
template<class T> string toString(T x) { stringstream StringOut; StringOut << x; return StringOut.str(); }

//型定義
//------------------------------------------
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int, int> PII;

//container util
//------------------------------------------
#define ALL(a)  (a).begin(),(a).end()
#define RALL(a) (a).rbegin(), (a).rend()
#define PB push_back
#define MP make_pair
#define SZ(a) int((a).size())
#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); ++i)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define SORT(c) sort((c).begin(),(c).end())

//繰り返し
//------------------------------------------
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

//定数
//--------------------------------------------
const double EPS = 1e-10;
const double PI = acos(-1.0);