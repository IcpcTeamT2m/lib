// 実行不可


// 宣言

#include <map>

map(型, 型) name;
map(string, int) name; //keyがstring型、値がint型


//例

name.insert(map<string, int>::value_type(10, "wzken")); //key 10 に "wzken" を格納

name.clear(); // 要素の全消去
name.empty(); // 空ならTrueを返す
