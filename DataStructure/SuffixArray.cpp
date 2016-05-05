/*
    文字列に、他の文字列が含まれているかを高速に求めるデータ構造
    詳細は蟻本参照

	SuffixArray SA("tutimaloid");
	SA.contain("tuti");//true
	SA.contain("maloid");//true
	SA.contain("id");//true


	SA.contain("z");//false
	SA.contain("tuta");//false
	SA.contain("wzken");//false
    
*/
struct SuffixArray {
	int size;
	vector<int> suffixRank;
	vector<int> sa;
	string str;
	SuffixArray(string str) : str(str),size(str.size()), suffixRank(str.size()+1),sa(str.size()+1) {
		for (int i = 0; i <= size; i++) {
			sa[i] = i;
			suffixRank[i] = i < size ? str[i] : -1;
		}
		vector<int> temp(size + 1);
		for (int k = 1; k <= size; k *= 2) {
			auto compare = [&](int i, int j) {
				if (suffixRank[i] != suffixRank[j]) {
					return suffixRank[i] < suffixRank[j];
				}
				else {
					int ri = i + k <= size ? suffixRank[i + k] : -1;
					int rj = j + k <= size ? suffixRank[j + k] : -1;
					return ri < rj;
				}
			};
			sort(sa.begin(), sa.end(), compare);
			temp[sa[0]] = 0;
			for (int i = 1; i <= size; i++) {
				temp[sa[i]] = temp[sa[i - 1]] + (compare(sa[i - 1], sa[i]) ? 1 : 0);
			}
			suffixRank = temp;
		}
	}
	bool contain(string target) {
		int l = 0, r = size;
		while (r - l > 1) {
			int m = (r + l) / 2;
			if (str.compare(sa[m], target.size(), target) < 0) l = m;
			else r = m;
		}
		return str.compare(sa[r], target.size(), target) == 0;
	}
	vector<int> lcp() {
		vector<int> tmpRank(size + 1);
		for (int i = 0; i <= size; i++)tmpRank[sa[i]] = i;
		int h = 0;
		vector<int> lcp(size);
		lcp[0] = 0;
		for (int i = 0; i < size; i++) {
			int j = sa[tmpRank[i] - 1];
			if (h > 0)h--;
			for (; j + h < size &&i + h < size; h++) {
				if (str[j + h] != str[i + h])break;
			}
			lcp[tmpRank[i] - 1] = h;
		}
		return lcp;
	}
};