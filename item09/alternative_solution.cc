// 鉴于在基类构造函数中使用virtual函数这一路子行不通, 那么该如何实现我们在
// using_virtual_func_in_ctor.cc中预期实现的功能呢?

// 即, 如何通过在构造函数中调用非virtual函数的方式来实现一种模拟的"多态性"?

#include <iostream>
#include <string>
using namespace std;

class Base {
 public:
  Base(const string& loginfo) {
    Log(loginfo);
  }
  void Log(const string &s) { // Log()现在是非virtual函数
    cout << s << endl;
  }
};

class Apple : public Base {
 public:
  Apple() : Base("A new Apple") {}  // 从派生类自下而上地将信息传递给基类构造函数
};

class Banana : public Base {
 public:
  Banana() : Base("A new Banana") {} // 从派生类自下而上地将信息传递给基类构造函数
};

int main() {
  Apple a;
  Banana b;
  return 0;
}

/*
程序输出:
A new Apple
A new Banana

符合预期.

如果需要通过Log()输出的信息较复杂, 不像本例一样可以直接用字符串字面值表示出来, 则
可以实现一个private成员函数(例如命名为CreateLogString())专门来整合这个信息成一个
字符串, 再将该函数返回结果作为Base()的参数传递到基类.
*/