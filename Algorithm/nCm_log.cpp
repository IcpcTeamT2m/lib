typedef long long ll;
const int mod = 1e9 + 7;
//nCmを n*(n-1)*(n-2)... / (1 * 2 * 3 ... )　の式で求める
//除算を行うために逆元を求める

ll extgcd(ll a, ll b, ll &x, ll &y) {
	ll d = a;
	if (b != 0) {
		d = extgcd(b, a % b, y, x);
		y -= (a / b) * x;
	}
	else {
		x = 1; y = 0;
	}
	return d;
}

ll mod_inverse(ll a, ll m) {
	ll x, y;
	extgcd(a, m, x, y);
	return (m + x % m) % m;
}

const int M = 200001;
ll fact[M];

ll mod_fact(ll n, ll p, ll &e) {
	e = 0;
	if (n == 0)return 1;
	ll res = mod_fact(n / p, p, e);
	e += n / p;

	if (n / p % 2 != 0)return res * (p - fact[n % p]) % p;
	return res * fact[n % p] % p;
}

ll mod_comb(ll n, ll k, ll p) {
	if (n < 0 || k < 0 || n < k)return 0;
	ll e1, e2, e3;
	ll a1 = mod_fact(n, p, e1), a2 = mod_fact(k, p, e2), a3 = mod_fact(n - k, p, e3);
	if (e1 > e2 + e3) return 0;
	return a1 * mod_inverse(a2 * a3 % p, p) % p;
}

int main()
{
	fact[0] = 0;
	fact[1] = 1;
	for (int i = 2; i < M; i++) {
		fact[i] = (fact[i - 1] * i) % mod;
	}

}
