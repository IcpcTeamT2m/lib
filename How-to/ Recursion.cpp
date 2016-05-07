//実行不可

/*

  再帰についてのHow-to
  
  競プロにおける再帰の利用対象
    ・深さ優先探索の実装
    ・動的計画法(DP)の実装の一つ,メモ化再帰の実装

  再帰でないと書くのが難しい(または不可能)処理は複数あり、
  競技プログラミングでは必須レベルです.
  
*/

//基本 (フィボナッチ数列の導出)
/*
フィボナッチ数列は、以下のような漸化式で表される数列です

  F(0) = 0
  F(1) = 1
  F(i) = F(i - 1)+F(i - 2) (i >= 2)

*/

//i番目のフィボナッチ数を求める
int F(int i){
  if(i == 0)return 0; //i == 0なら定義から0を返す
  if(i == 1)return 1; //i == 1なら定義から1を返す
  return F(i - 1) + F(i - 2); //定義からF(i - 1) + F(i - 2)を返す
}
