//include
//------------------------------------------
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<stack>
#include<algorithm>
#include<math>

using namespace std;

//^ฯท(int < == > string)
//------------------------------------------

//string^๐int^ษ
int StrtoInt(string s) { int v; stringstream StringIn(s); StirngIn >> v; return v; }

// l๐๐string^ษ
template<class T> string toString(T x) { stringstream StringOut; StringOut << x; return StringOut.str(); }

//^่`
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

//J่ิต
//------------------------------------------
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

//่
//--------------------------------------------
const double EPS = 1e-10;
const double PI = acos(-1.0);