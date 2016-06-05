const int M = 100;
typedef long double ld;
const int mod = 1e9 + 7;

ld C[M][M];

int main() {
	C[0][0] = 1;
	C[1][1] = C[1][0] = 0.5;
	for (int i = 2; i < M; i++)
	{
		for (int j = 0; j <= i; ++j)
		{
			ld l = j >= i ? 0 : C[i - 1][j];
			ld r = j > 0 ? C[i - 1][j - 1] : 0;
			C[i][j] = (l + r) / 2.0l;
		}
	}
}
