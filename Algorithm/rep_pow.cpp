//繰り返し二乗法
//http://judge.u-aizu.ac.jp/onlinejudge/commentary.jsp?id=NTL_1_B
int rep_pow(int x, int n) {
  int res = 1;
  while (n > 0) {
    if (n & 1) res = res * x;
    x = x * x;
    n >>= 1;
  }
  return res; 
}
