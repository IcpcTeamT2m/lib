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

//Œ^•ÏŠ·(int < == > string)
//------------------------------------------

//stringŒ^‚ğintŒ^‚É
int StrtoInt(string s) { int v; stringstream StringIn(s); StirngIn >> v; return v; }

// ”’l‚ğ‚ğstringŒ^‚É
template<class T> string toString(T x) { stringstream StringOut; StringOut << x; return StringOut.str(); }

//Œ^’è‹`
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

//ŒJ‚è•Ô‚µ
//------------------------------------------
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

//’è”
//--------------------------------------------
const double EPS = 1e-10;
const double PI = acos(-1.0);