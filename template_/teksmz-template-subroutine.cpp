// 実行不可


// stringをintに変換
#include <string>
#include <sstream>
int Str2Num(string s)
{
	stringstream ss;
	ss << s;
	int num;
	ss >> num;
	return num;
}

// intをstringに変換
#include <string>
#include <sstream>
string Num2Str(int num)
{
	stringstream ss;
	ss << num;
	return ss.str();
}
