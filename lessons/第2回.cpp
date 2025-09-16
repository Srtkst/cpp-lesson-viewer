#include <iostream>
#include <string>

// 第2回 制御構文
// Cとほとんど同じだが、cinやstringと組み合わせやすいのがC++の強み

// if文
int main1() {
    int score;
    std::cout << "点数を入力してください: ";
    std::cin >> score;

    if (score >= 80) {
        std::cout << "合格です！\n";
    } else if (score >= 50) {
        std::cout << "あと少し！\n";
    } else {
        std::cout << "不合格...\n";
    }

    return 0;
}

// switch文
int main2() {
    int n;
    std::cout << "1〜3の数字を入力してください: ";
    std::cin >> n;

    switch (n) {
        case 1:
            std::cout << "one\n";
            break;
        case 2:
            std::cout << "two\n";
            break;
        case 3:
            std::cout << "three\n";
            break;
        default:
            std::cout << "それ以外です\n";
            break;
    }

    return 0;
}

// for文
int main3() {
    // 1から10までの和
    int sum = 0;
    for (int i = 1; i <= 10; i++) {
        sum += i;
    }
    std::cout << "1から10までの和は " << sum << "\n";

    return 0;
}

// while文
int main4() {
    int n;
    std::cout << "0が入力されるまで数を入力してください: ";
    std::cin >> n;

    while (n != 0) {
        std::cout << "入力値: " << n << "\n";
        std::cin >> n;
    }

    std::cout << "終了\n";
    return 0;
}

// do-while文
int main5() {
    std::string password;
    do {
        std::cout << "パスワードを入力してください: ";
        std::cin >> password;
    } while (password != "cpp");

    std::cout << "ログイン成功！\n";
    return 0;
}
