#include <iostream>
#include <string>

//第五回: クラスとオブジェクト

// ちょっと難しいけどできるだけ細かく説明するからついてきてね！


// クラスの定義
class Student {
public:
    std::string name;
    int age;

    //メンバ関数    
    void introduce() {
        std::cout << "私は" << name << "、" << age << "歳です。\n";
    }
};

int main1() {
    Student s1;
    s1.name = "太郎";
    s1.age = 20;
    s1.introduce();
    // 出力: 私は太郎、20歳です。

    return 0;
}

// コンストラクタの利用

class Animal {
public:
    std::string type;

    // コンストラクタ: 初期化リストを使って直接 type を初期化
        //初期化が一度だけされ、余計な代入が発生しない
        //Animal 変数の名前(~~~) の形で使える
    Animal(const std::string &t) {
        type = t;
        //ほかにも初期処理を追加できる
    }

    /*
    別の書き方として、
    Animal(const std::string &t) : type(t) {}　もある。    
    tの値をtypeに代入するよって意味
    */



    void speak() {
        std::cout << type << "が鳴きます。\n";
    }
};

int main2() {
    Animal dog("犬"); // コンストラクタが呼ばれる (typeに"犬"が代入)
    dog.speak();

    // 出力: 犬が鳴きます。
    return 0;
}


// カプセル化とconstメソッド
//  - balance を private にして外からいじれないようにする (カプセル化)
//  - show_balance() に const を追加して「状態変更なし」を保証

class BankAccount {
private:
    int balance; // private: クラス外から直接アクセスできない

public:
    // コンストラクタ: 初期残高を受け取る
    BankAccount(int initial) : balance(initial) {}

    void deposit(int amount) {
        if (amount < 0) return; // 異常値ガード
        balance += amount;      // 残高ふやす
    }

    void withdraw(int amount) {
        if (amount < 0) return; // 異常値ガード
        if (balance >= amount) {
            balance -= amount; // 引き出し成功
        } else {
            // 残高不足のときはエラーメッセージを表示
            std::cout << "残高不足です。\n";
        }
    }

    void show_balance() const {
        std::cout << "残高: " << balance << "円\n";
    }
};

int main3() {
    BankAccount account(1000); // 初期残高 1000 円
    account.deposit(500);      // 残高 1500 円
    account.show_balance();    // 出力: 残高: 1500円

    account.withdraw(2000);    // 残高不足だからエラー
    // 出力: 残高不足です。
    account.show_balance();    // 出力: 残高: 1500円

    return 0;
}

// this ポインタの使いどころ
//  - メソッド内のパラメータ名がメンバ名と同じ場合に this-> を使う

class Counter {
private:
    int count;

public:
    // コンストラクタで count を初期化
    Counter(int count) : count(count) {}

    // add の引数の名前をあえて同じ名前にした時
    void add(int count) {
        // ここでの count は引数。privateのメンバを指すには this->count を使う
        this->count += count;
    }

    // show は状態を読むのみなので const をつける
    void show() const {
        std::cout << "カウント: " << this->count << "\n";
    }
};

int main4() {
    Counter c(10); // 初期値 10
    c.add(5);      // メンバ count は 15 になる
    c.show();      // 出力: カウント: 15

    return 0;
}

// 複数オブジェクトの扱い・const メソッド
//  - 複数のインスタンスはそれぞれ独立したデータを持つ
//  - area() を const にすることで「面積計算は状態を変えない」ということを表明できる

class Rectangle {
public:
    int width, height;

    // コンストラクタ
    Rectangle(int w, int h) : width(w), height(h) {}

    // 面積を返す。　状態変更しないため const を付けるのがいい習慣
    int area() const {
        return width * height;
    }
};

int main5() {
    Rectangle r1(3, 4);
    Rectangle r2(5, 6);
    
    // r1 と r2 はそれぞれ別であり、それぞれにメモリが割り当てられている
    std::cout << "r1の面積: " << r1.area() << "\n"; // 出力: r1の面積: 12
    std::cout << "r2の面積: " << r2.area() << "\n"; // 出力: r2の面積: 30

    return 0;
}


// static メンバ変数（クラスごとに共有されるデータ）
//  - static メンバはクラス全体で1つのみ存在。データは共有される

class IDGenerator {
public:
    static int next_id; // 宣言（メモリ確保は下で行う）

    int id;

    // コンストラクタ
        // 新しく作るときに next_id をつかって id を割り当てて、next_id を増やす
    IDGenerator() : id(next_id++) {}
};

// static メンバの定義（必須）と初期化（クラスの外で行う）
int IDGenerator::next_id = 1;

int main6() {
    IDGenerator a,b,c;
    std::cout << "a.id=" << a.id << " b.id=" << b.id << " c.id=" << c.id << "\n";
    // 出力: a.id=1 b.id=2 c.id=3

    return 0;
}