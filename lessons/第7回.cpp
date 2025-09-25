#include <iostream>
#include <vector>
#include <algorithm> // sort, findなどのアルゴリズム
#include <string>

// --------------------
// 関数テンプレート
// --------------------
// 型に依存しない関数を定義できる
template <typename T>
T add(T a, T b) {
    return a + b;
}

int main1() {
    std::cout << add(3, 5) << "\n";       // int型 → 出力: 8
    std::cout << add(2.5, 4.1) << "\n";   // double型 → 出力: 6.6
    std::cout << add(std::string("Hello, "), std::string("World")) << "\n"; 
    // string型 → 出力: Hello, World
    return 0;
}

// --------------------
// クラステンプレート
// --------------------
// 汎用的なデータ構造を作れる
template <typename T>
class Box {
    T value;
public:
    Box(T v) : value(v) {}
    T get() const { return value; }
};

int main2() {
    Box<int> intBox(42);
    Box<std::string> strBox("テンプレート学習中");

    std::cout << intBox.get() << "\n";   // 出力: 42
    std::cout << strBox.get() << "\n";   // 出力: テンプレート学習中
    return 0;
}

// --------------------
// STL（Standard Template Library）
// --------------------
// 代表例: vector, sort
int main3() {
    std::vector<int> nums = {5, 2, 8, 1, 3};

    // sort（昇順ソート）
    std::sort(nums.begin(), nums.end());

    // 出力: 1 2 3 5 8
    for (int n : nums) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    // find（要素検索）
    auto it = std::find(nums.begin(), nums.end(), 3);
    if (it != nums.end()) {
        std::cout << "見つかった: " << *it << "\n"; // 出力: 見つかった: 3
    }
    return 0;
}

// --------------------
// STL: map（連想配列）
// --------------------
#include <map>

int main4() {
    std::map<std::string, int> scores;

    scores["Alice"] = 90;
    scores["Bob"] = 75;
    scores["Charlie"] = 82;

    // 出力:
    // Alice: 90
    // Bob: 75
    // Charlie: 82
    for (auto& kv : scores) {
        std::cout << kv.first << ": " << kv.second << "\n";
    }

    return 0;
}
