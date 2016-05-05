
//素数判定
bool isPrime(ll n){
	if (n == 1)return false;
	for (int i = 2; i * i <= n; i++){
		if (n % i == 0){
			return false;
		}
	}
	return true;
}

//[0,n]まで素数表を返す
vector<bool> makePrimeTable(int n){
    //エラトステネスの篩を用いて素数表を作成    
    //era[i] iが素数ならtrue
    vector<bool> era(n+1, true);

	//0と1を素数として扱ったほうが良い場合に注意	
	era[0] = false;
	era[1] = false;

	for (int i = 2; i <= n; i++){
		if (era[i]){
            for (int j = i * 2; j <= n; j += i){
			    era[j] = 0;
            }
        }
	}
}

//素因数分解
map<ll, int> primeFactor(ll n){
	map<ll, int> res;
	for (ll i = 2; i * i <= n; i++){
		while (n % i == 0){
			++res[i];
			n /= i;
		}
	}
	if (n != 1)res[n] = 1;
	return res;
}