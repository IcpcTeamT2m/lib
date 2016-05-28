// 実行不可


// 宣言

#include <map>

map<型, 型> name;
map<string, int> name; //keyがstring型、値がint型

//例

name.insert(map<string, int>::value_type("wzken",10)); //key "wzken" に 10 を格納
name["wzken"] = 10; //上の例と同じ

int a = name["wzken"];//aに10が格納される

name.clear(); // 要素の全消去
name.empty(); // 空ならTrueを返す

//値を格納すると自動的にkeyの昇順で内部がソートされる
map<int,int> name2;
name2[1] = 2;
name2[5] = 5;
name2[2] = 10;

//内部の順番
/*
  key 1 : value  2
  key 2 : value 10
  key 5 : value  5
*/

//mapの中身を走査
for(auto i : name2){
  //key   = i.first
  //value = i.second
  cout << i.first << " " << i.second << endl;
}

//出力結果
/*
  1 2
  2 10
  5 5
*/





