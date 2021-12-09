#include <iostream>
#include "widget.h"

using std::cout;
using std::endl;

// 类的静态非整数类型常量不能再类内初始化, 而是在实现文件中给出定义式并赋予初值.
const double Widget::Pi = 3.14;

// 类的静态整数类型常量虽然可以在类内初始化, 但如果程序中要用到该常量的地址(例如
// 在函数print_address()中), 则必须在实现文件中给出该常量的定义式. 当然, 如果已经
// 在类内给出初值, 则定义式内可不能再度赋初值.
const int Widget::Zero;

void Widget::print_value() {
  cout << Zero << endl;
  cout << Pi << endl;
  cout << Ten << endl;
}

void Widget::print_address() {
  cout << &Zero << endl;
  cout << &Pi << endl;
  // cout << &Ten << endl;  // 不能够对enum常量执行取地址操作
}

int main() {
  Widget::print_value();
  Widget::print_address();
  cout << max(1, 2) << endl;
}