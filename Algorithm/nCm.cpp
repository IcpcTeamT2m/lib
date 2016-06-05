
const int M = 100;
typedef long long ll;
const int mod = 1e9 + 7;

int main() {
	ll C[M][M];

	C[0][0] = C[1][1] = C[1][0] = 1;
	for (int i = 2; i < M; i++)
	{
		for (int j = 0; j <= i; ++j)
		{
			ll l = j >= i ? 0 : C[i - 1][j];
			ll r = j > 0 ? C[i - 1][j - 1] : 0;
			C[i][j] = (l + r) % mod;
		}
	}

}
