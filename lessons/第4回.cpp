#include <iostream>
#include <string>

// 第4回 関数

// 基本の関数
int add(int a, int b) {
    return a + b;   //ほっとんどかわらん
}

int main1() {
    int result = add(3,5);
    std::cout << "3 + 5 = " << result << "\n";

    //出力: 3 + 5 = 8
    return 0;
}

// 戻り値を持たない関数
void hello() {
    std::cout << "Hello Function!\n";
}

int main2() {
    hello();

    // 出力: Hello Function!
    return 0;
}

// 引数と戻り値
std::string greet(std::string name){
    return "Hello, " + name + "!";
}

int main3() {
    std::string msg = greet("Taro");
    std::cout << msg << "\n";

    // 出力: Hello, Taro!
    return 0;
}


// 関数のオーバーロード
// 同じ名前で型が違うものを定義できる(Cにはない便利機能)
int square(int x) {
    return x * x;
}
double square(double x) {
    return x * x;
}

int main4() {
    std::cout << square(5) << "\n";
    std::cout << square(3.14) << "\n";

    // 出力:
    // 25
    // 9.8596
    return 0;
}

// 参照渡し (Cでのポインタ渡しより直感的)
void swap_int(int &a, int &b) { // & が参照渡し
    int tmp = a;
    a = b;
    b = tmp;
}

int main5() {
    int x = 10,y = 20;

    swap_int(x,y);
    std::cout << "x=" << x << "y=" << y << "\n";

    // 出力: x=20 y=10
    return 0;
}

// const参照 
// 値をコピーせずに読み取り専用で渡せる (効率的かつ安全)
void print_message(const std::string &msg) {
        // std::string &msg -> コピーを作らずに元の値を直接扱う
        // const がつく -> 「読み取り専用」。関数の中でmsgを書き換えることはできない
        // => コピーは作らず効率的に値を受け取りつつ、関数の中で改変はしない。
        
        // だから msg = "change"; は変更できないmsgに代入してるからコンパイルエラーになる
        std::cout << msg << "\n";

}

int main6() {
    std::string str = "This is const reference";
    print_message(str);

    // 出力: This is const reference
    return 0;
}


