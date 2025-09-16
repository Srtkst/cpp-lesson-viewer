// ヘッダーファイルを参照
// <iostream> は標準入出力のライブラリ (Cでいうstdio.hに相当)
#include <iostream>
#include <string>

// std:: を毎回書くのが面倒なときは次のように書ける
// ただし実務では非推奨（競合の原因になる）
// using namespace std;

// HelloWorld
// Cと同じでmain関数から始まり、終わる
int main1() {
    std::cout << "Hello, C++ in VScode\n";
    // std::cout << "文字列"; で画面表示

    return 0;
}

// 変数・型・演算子
int main2() {
    int x;
    x = 3;

    int y = 5;
    int z;

    z = x + y;

    //ここら辺はほとんどかわらないね
    std::cout << z << "\n";
    std::cout << x - y << "\n";
    std::cout << x * y << "\n";
    std::cout << x / y << "\n";
    std::cout << x % y << "\n";

    double d = 3.14; //浮動小数点型
    char c = 'a';    //文字型（1文字）

    // ここからCと違う部分
    // 先ほどincludeしたライブラリ <string> が必須
    std::string message = "Hello";
    std::string message2 = " World!";

    std::cout << message + message2 << "\n";

    return 0;
}

// 代入演算子・インクリメント・const
int main3() {
    int a = 10;
    a += 5; // 代入演算子
    a++;    // 後置インクリメント
    ++a;    // 前置インクリメント

    //新メンバー
    //変更できない定数。値を変更できない
    const double tax = 1.08;
    std::cout << "税率: " << tax << "\n";

    return 0;
}

// 入力 (cin) と bool型
int main4() {
    int n;
    std::cout << "整数を入力してください: ";
    std::cin >> n; // scanfに相当（フォーマット指定子不要）
    std::cout << "入力された値: " << n << "\n";

    bool flag = true;
    std::cout << "boolの出力 (trueは1): " << flag << "\n";

    return 0;
}

// 型推論 auto と スコープ
int main5() {
    auto x = 42;      // int型と推論される
    auto pi = 3.14;   // double型
    auto msg = "Hi";  // const char*

    std::cout << x << " " << pi << " " << msg << "\n";

    int a = 5;
    {
        int a = 10; // ブロック内では別のa
        std::cout << "内側のa: " << a << "\n"; // 10
    }
    std::cout << "外側のa: " << a << "\n"; // 5

    return 0;
}
