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


//--------------------------------------------------

//一次元ベクタ

//宣言のみ
vector<int>v;
//要素数のみ指定(５つ)
vector<int>v（5）;
//初期化の数値も指定(５つの要素を0で初期化)
vector<int> v(5, 0);



//二次元ベクター

//宣言のみ
vector<vector<int>>v;
//要素数のみ指定(５つの二次元ベクター)
vector<vector<int>> v(5);
//初期化あり(５つの要素を空の一次元ベクターで初期化)
vector<vector<int>> v(5, vector<int>());
//初期化の数値も指定(５つの要素を要素数8の各要素0の一次元ベクターで初期化)
vector<vector<int>> v(5, vector<int>(8,0));



//二次元ベクターのサイズの求め方

//vの行数
v.size();
//vのi行目の要素数
v[i].size();


//二次元ベクター初期化法 (下二つは同じ)

v.clear();
v = vector<vector<int>>();
//二次元ベクターの部分初期化法(i番目の一行を削除する。
//vの行が0~4でv[2].clear()を使うと、vは0,1,3,4の行数が残る。)
v[i].clear();


//二次元ベクターの使い方

//宣言のみの二次元ベクターを用いる場合
//利点: 二次元ベクターの要素数を先に指定しなくてもプログラムに動的に組み込めること
//欠点: やや扱いが複雑
vector<vector<int>>v;

rep(i, 5) {
        //vが完全に空なのでvにvector<int>()を追加しなければならない
		v.push_back(vector<int>());
		rep(j, 8) {
			v[i].push_back(i*j);
		}
	}
    
//初期化ありのの二次元ベクターを用いる場合
//利点: 扱いが容易
//欠点: 動的な扱いが難しい
vector<vector<int>> v(5, vector<int>());

rep(i, 5) {
		rep(j, 8) {
            //v.push_back(vector<int>())が不要
			v[i].push_back(i*j);
		}
	}
