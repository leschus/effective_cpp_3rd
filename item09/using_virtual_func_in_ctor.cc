// 在基类的构造函数中使用virtual成员函数

// 示例: 基类构造函数中调用virtual成员函数Log(), 意图借此达到对不同派生类型的创建
// 事件进行日志记录的目的. ---- 让我们看看该意图能否通过这种方式达成.

#include <iostream>
using namespace std;

class Base {
 public:
  Base() {
    Log();
  }
  virtual void Log() const = 0; // 纯虚函数, 由子类提供实现
};

class Apple : public Base {
 public:
  void Log() const {  // 子类提供Log()的实现.
    cout << "A new Apple\n"; // 我们误以为创建Apple对象时Base()会调用此版本的Log()
  }
};

class Banana : public Base {
 public:
  void Log() const { // 子类提供Log()的实现.
    cout << "A new Banana\n";// 我们误以为创建Banana对象时Base()会调用此版本的Log()
  }
};

int main() {
  Apple a;
  Banana b;
  return 0;
}

/*
链接出错.
原因: 我们自以为派生类对象(如a)在创建时, 构造函数中的virtual函数会使用派生类的
      版本. 但实际上, 在构造派生类的基类部分时, 该对象是被视作一个基类对象而非
      派生类对象的. 因此, 会调用基类的virtual函数版本. 在本例中, 基类Base中的
      Log()是纯虚函数, 没有提供实现, 因此在链接时由于找不到函数定义而报错.

这其实告诉我们, 通过在基类构造函数中调用virtual函数以期表现出多态性是行不通的.
上例中即使我们为Base的Log()纯虚函数提供了实现, 在创建对象a时, 调用的Log()也是基类
版本, 而非派生类Apple中的版本.
*/