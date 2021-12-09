#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

const int One = 1; // 位于全局作用域的类外常量

namespace MyNS {
  const int Two = 2; // 位于名字空间作用域内的类外常量
}

static const int Three = 3; // 位于文件作用域的被static修饰的量

int add_something(int x) {
  static const int Four = 4; // 位于函数作用域的被static修饰的量
  x += Four;
  {
    static const int Five = 5; // 位于区块作用域的被static修饰的量
    x += Five;
  }
  return x;
}

class Sample {
 private:
  static const int Five = 5;  // 类作用域中的static数据成员
  const int Six = 6;          // 类作用域中的non-static数据成员
  vector<int> vec;
 public:
  Sample() : vec(Five) {
    // vec包含Five个元素, 每个元素的值为Six
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
      *it = Six;
    }
  }
  // 下面是一个const成员函数(后面会介绍), 不能在其内部有修改类数据成员的操作
  void print_vec() const {
    // 下面这个使用迭代器遍历vector中所有元素的操作, 只能够使用const_iterator完成.
    // 若使用iterator, 则编译器认为在const成员函数内使用iterator访问vector内的元素
    // 可能会修改元素的值(即使你并没有写这样的代码!),这与成员函数被约定为const相悖,
    // 因此编译无法通过.
    // 若使用声明为const的iterator, 同样有上面的问题, 并且下面代码中的表达式it++也
    // 会出错.
    for (vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++) {
      cout << *it << " ";
    }
    cout << endl;
  }
};

char greeting[] = "hello";
char *p = greeting;
const char* p1 = greeting;        // 指向常量内容的非常量指针
char* const p2 = greeting;        // 指向非常量内容的常量指针
const char* const p3 = greeting;  // 指向常量内容的常量指针

int main() {
  Sample s;
  s.print_vec();
}
