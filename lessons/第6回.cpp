#include <iostream>
#include <string>

// 継承と多様性
// 書いててむずかったからちゃんと理解しよう！

// ---------------
// 基本的な継承
// ---------------

// 親クラス（基底クラス）
class Animal {
public:
    std::string name;

    // コンストラクタ
    Animal(const std::string &n) : name(n) {}

    void eat() {
        std::cout << name << " がご飯を食べます。\n";
    }
};

// 子クラス（派生クラス）
    // Animal を継承（: public Animal）
class Dog : public Animal { // 親の特性を持ちつつ独自のメソッドをもてる
public:
    
    // コンストラクタ（Animal(n)で上のコンストラクタに移動）
    Dog(const std::string &n) : Animal(n) {}

    void bark() {
        std::cout << name << " がワンと鳴きます！\n";
    }
};

int main1() {
    Dog d("ポチ");

    d.eat(); // 親のメソッドをそのまま使える
    d.bark(); // 子クラスのみのメソッド

    // 出力:
    // ポチ がご飯を食べます。
    // ポチ がワンと鳴きます！

    return 0;
}


// ---------------
// オーバーライド（仮想関数）
// ---------------

class Animal2 {
public:
    std::string name;

    Animal2(const std::string &n) : name(n) {}

    // virtual を付けると「仮想関数」= 派生クラスで上書き可能！
    virtual void speak() {
        std::cout << name << " が鳴きます。\n";
    }
};

class Cat : public Animal2 {
public:
    Cat(const std::string &n) : Animal2(n) {}

    // 親クラスの speak() を上書き（オーバーライド）
    void speak() override {
        std::cout << name << " がニャーと鳴きます。\n";
    }
};

class Dog2 : public Animal2 {
public:
    Dog2(const std::string &n) : Animal2(n) {}

    void speak() override {
        std::cout << name << " がワンワンと鳴きます。\n";
    }
};

int main2() {
    Cat c("タマ");
    Dog2 d("ポチ");

    c.speak(); // 出力: タマ がニャーと鳴きます。
    d.speak(); // 出力: ポチ がワンワンと鳴きます。

    return 0;
}

// ---------------
// ポリモーフィズム（多態性）
// ---------------

int main3() {
    // 基底クラスのポインタで派生クラスを扱う
    Animal2 *a1 = new Cat("ミケ");
    Animal2 *a2 = new Dog2("シロ");

    // どちらも speak() を呼んでいるが、中身は違う！
    a1 -> speak(); // 出力: ミケ がニャーと鳴きます。
    a2 -> speak(); // 出力: シロ がワンワンと鳴きます。

    delete a1;
    delete a2;
    return 0;
}

// ---------------
// 抽象クラス（純粋仮想関数）
// ---------------

// 「=0」を付けると純粋仮想関数 -> 抽象クラスになる。
// 抽象クラスのみだと使えない
class Shape {
public:
    virtual double area() const = 0; // 純粋仮想関数
    //命令がない = 派生クラスで定義してあげる
};

class Circle : public Shape {
private:
    double r;
public:
    Circle(double radius) : r(radius) {}
    double area() const override {
        return 3.14 * r * r;
    }
};

class Rectangle : public Shape {
private:
    double w,h;
public:
    Rectangle(double width, double height) : w(width) , h(height) {}
    double area() const override {
        return w * h;
    }
};

int main4() {
    Shape *s1 = new Circle(5.0);
    Shape *s2 = new Rectangle(3.0, 4.0);

    std::cout << "円の面積: " << s1 -> area() << "\n";      // 出力: 円の面積: 78.5
    std::cout << "長方形の面積: " << s2 -> area() << "\n";  // 出力: 長方形の面積: 12

    delete s1;
    delete s2;
    return 0;
}