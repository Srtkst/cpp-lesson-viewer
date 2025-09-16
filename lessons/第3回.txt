#include <iostream>
#include <vector>
#include <string>

// 第3回 配列とvector
// Cの配列を復習しつつ、C++のvectorを学ぶ

// Cの配列
int main1() {
    int a[5]; // 要素数5のint配列
    for (int i = 0; i < 5; i++){
        a[i] = i * 10;
    }

    for (int i = 0; i < 5; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";

    // 出力: 0 10 20 30 40
    return 0;
}

// C++の配列 (C++以降なら std::array もあるが今回は割愛)
int main2() {
    // 初期化を同時にできる
    int b[5] = {1,2,3,4,5};

    for (int i = 0; i < 5; i++) {
        std::cout << b[i] << " ";
    }
    std::cout << "\n";

    // 出力: 1 2 3 4 5
    return 0;
}

// vector (可変長配列)
// #include <vector> が必須
int main3() {
    std::vector<int> v; //要素数0でスタート

    // push_backで要素追加
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    // サイズは v.size()
    std::cout << "サイズ: " << v.size() << "\n";

    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";

    // 出力:
    // サイズ: 3
    // 10 20 30

    return 0;
}

// vectorの便利な初期化
int main4() {
    // 要素数5　すべてを0で初期化
    std::vector<int> v1(5, 0); // 0 0 0 0 0

    // リスト初期化 (C++11以降)
    std::vector<int> v2 = {1,2,3,4,5};

    for (int x : v2) { // v2の中身をひとつづつ出力
        std::cout << x << " ";
    }
    std::cout << "\n";

    // 出力: 1 2 3 4 5
    return 0;
}

// 文字列もvectorと相性がいい
int main5() {
    std::vector<std::string> words; // ちょっとややこしいけど

    words.push_back("C++");
    words.push_back("is");
    words.push_back("fun!");

    for (std::string s : words) {
        std::cout << s << " ";
    }
    std::cout << "\n";

    //出力: C++ is fun!
    return 0;
}