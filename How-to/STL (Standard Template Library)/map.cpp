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

