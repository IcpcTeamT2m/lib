//最大公約数
int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }
//最小公倍数
int lcm(int a, int b) { return a / gcd(a, b) * b; }

//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0005&lang=jp
