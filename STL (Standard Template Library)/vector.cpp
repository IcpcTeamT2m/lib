// 実行不可


// 宣言

#include <vector>

vector<char> v(配列数, 初期値); //配列数の全てに初期値を格納
vector<char> v(配列数); //配列数に変数を指定することが出来る


// 関数 例

int a;
a = v.size(); //vの配列数　//forのループに有用

v.push_back(5); // 配列の末尾に値5を追加 // 配列数が1増える

v.erase(v.begin());  //vの配列の始めから0番目を消去 //配列数が1減る
v.erase(v.begin() + 1);  //vの配列の始めから1番目を消去 //配列数が1減る

sort(v.begin(), v.end()); // 初めから末尾まで昇順へ並び替える
sort(v.begin(), v.begin() + 3); // 初めから3番目まで昇順へ並び替える

unique(v.begin(), v.end()); // 初めから末尾までの重複要素を消去する //配列の数は変更しない
x.erase(unique(v.begin(), v.end()), v.end()); // 初めから末尾までの重複要素を消去する // 配列の数を変更する


// サブルーチン 例

void sub(vector<char> &v) 
{
	//配列の変更がmain()にも適用される
}
int main()
{
	vector<char> v(10);
	sub(v);
}
