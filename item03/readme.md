# 条款03 尽可能使用const

const指定一个语义约束(即某个对象"不该被改动"), 而编译器会强制实施这个约束.

下面罗列了const的使用场景.

## 1. 定义在classes外的global或namespace作用域内的常量.
```cpp
// samples.cc
const int One = 1; // 位于全局作用域的类外常量

namespace MyNS {
  const int Two = 2; // 位于名字空间作用域内的类外常量
}
```

## 2. 文件/函数/区块(block)作用域中被声明为static的对象.
```cpp
// samples.cc
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
```

## 3. classes内部的static或non-static数据成员.
```cpp
// samples.cc
class Sample {
 private:
  static const int Five = 5;  // 类作用域中的static数据成员
  const int Six = 6;          // 类作用域中的non-static数据成员
  ...
};
```

## 4. 指针.
*前的const用于指明指针指向的内容是常量(即不可修改指针所指的内容), *后的const用于指明指针是常量指针(即不可修改指针本身).
```cpp
// samples.cc
char greeting[] = "hello";
char *p = greeting;
const char* p1 = greeting;        // 指向常量内容的非常量指针
char* const p2 = greeting;        // 指向非常量内容的常量指针
const char* const p3 = greeting;  // 指向常量内容的常量指针
```

### STL中声明为const的iterator与const_iterator的区别

STL中的迭代器是根据指针塑模出来的, 所以迭代器的作用就像T*指针.

声明为const的迭代器就好像声明了一个T* const指针, 即该指针本身不可以被改变, 但是指针所指向的内容是可以修改的. 如果你希望迭代其所指向的内容不可以被修改, 则应该使用const_iterator, 它相当于一个const T*指针.
```cpp
// samples.cc
class Sample {
 private:
  ...
  vector<int> vec;
  ...
 public:
  ...
  // 下面是一个const成员函数(后面会介绍), 不能在其内部有修改类数据成员的操作
  void print_vec() const {
    // 下面这个使用迭代器遍历vector中所有元素的操作, 只能够使用const_iterator完成.
    // 若使用iterator, 则编译器认为在const成员函数内使用iterator访问vector内的元素可能会
    // 修改元素的值(即使你并没有写这样的代码!),
    // 这与成员函数被约定为const相悖, 因此编译无法通过.
    // 若使用声明为const的iterator, 同样有上面的问题, 并且下面代码中的表达式it++也会出错.
    for (vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++) {
      cout << *it << " ";
    }
    cout << endl;
  }
}
```

## 5. 在函数声明式中修饰函数各个参数/返回值/函数自身(如果是成员函数).

声明为const的函数参数, 其实就可以当作一个声明为const的局部变量去理解, 没有新的要注意的点.

将函数的返回值声明为const, 可以使得编译器能捕捉一些隐晦的编程错误, 见下例.
```cpp
// 一个有理数类
class Rational {...};
// 重载*运算符实现两个有理数的乘法运算
const Rational operator*(const Rational& lhs, const Rational& rhs);

int main() {
  Rational a, b, c;
  ...
  if (a * b = c) { // 这里将==漏写成了=, 由于我们将operator*返回类型声明为const, 我们将在
                   // 编译阶段就捕捉到这一错误.
    ...
  }
}
```

### const成员函数
将const实施于成员函数, 基于以下两个理由:
1. 使class接口更易于理解. 即通过观察成员函数是否为const, 可以得知哪些成员函数可以改动对象数据类容而哪些不能.
2. 使"操作const对象"成为可能.
```cpp
// const_member_functions.cc
class Widget {
 public:
  ...
  // 更新nums[idx]的值为val
  bool update(std::size_t idx, int val) {...};
  // 打印nums
  void print() const {...}
 private:
  vector<int> nums;
};

int main() {
  Widget w1;
  w1.update(0, 1);    // OK
  w1.print();         // OK
  const Widget w2;
  w2.update(0, 1);    // ERROR, 不能对const对象调用其非const方法
  w2.print();         // OK, print()是const方法
}
```
需要认识到, 两个成员函数即使只有常量性不同, 这样的重载也是允许的. 例如, 我们对于[]运算符可以实现一个const版本和一个非const版本.
前者只用于读取数据, 后者可以在读取的同时进行写入. 这时候, 如果有一个该类的const对象a和一个非const对象b, 则a[i]和b[i]将分别调用const版本和非const版本的[]运算符函数.
```cpp
// const_member_functions.cc
class Widget {
 public:
  ...
  // 重载[]运算符函数的非const版本
  int& operator[](std::size_t idx) { return nums[idx]; };
  // 重载[]运算符函数的const版本
  const int& operator[](std::size_t idx) const { return nums[idx]; };
 private:
  vector<int> nums;
}

int main() {
  Widget a;
  a[0] = 1;             // OK, 调用operator[]的非const版本, 返回结果既可读取又可更改
  cout << a[0] << endl; // OK, 同上
  const Widget b;
  b[0] = 1;             // ERROR, 调用operator[]的const版本, 返回结果只能读取不能更改
  cout << b[0] << endl; // OK, 同上
}
```

#### **bitwise constness**和**logical constness**:

bitwise const阵营的人认为, 只要成员函数不修改对象的任何成员变量(除static成员), 就可以被称作是const, 也就是它不会修改对象内的任何一个bit. 这种论点容易侦测违反点, 因此被编译器所采用.

但是, 某些能够通过bitwise测试的成员函数实际上不具备十足的const特质. 例如, 如果某对象有一个指针类型的成员, 它的一个声明为const的成员函数不修改指针本身, 但却修改指针所指向的值, 这种情况是能够通过bitwise测试的. 但很明显, 这不符合我们设置const成员函数的初衷.

由此, 导出了所谓的logical const阵营. 其支持者认为, 一个const数据成员应当被允许修改它所处理对象内的部分bits, 但前提是不能被客户端侦测出. 这需要用到mutable关键字. mutable用于释放掉non-static成员变量的bitwise constness约束, 从而在声明为const的成员函数内部, 被mutable修饰的成员可以被修改.
```cpp
// mutable.cc
class Person {
 public:
  ...
  const string& getName() const {
    called_times++; // 即使处于const成员函数内, mutable所修饰的成员变量仍可以被修改
    return name;
  }
  ...
 private:
  string name;
  mutable int called_times; // 用于统计getName()函数的被调用次数
}
```

#### 在const和non-const成员函数中避免重复

Widget类中的const版本和非const版本的operator[]重载函数除了常量性不同, 其它内容均相同. 当这样的一对函数的函数体较复杂时, 将会产生大段的重复代码. 为了避免代码重复以及随之产生的编译时间/维护/代码膨胀等问题, 可以将两个函数中的重复部分代码移至另一个成员函数中(通常是个private)并令这两个函数均调用它. 但这仍然存在代码重复, 例如函数调用和两次return语句.

真正的避免重复的做法是, 只实现这对函数所要实现的机能一次, 但使用它两次. 即const版本和非const版本中的一个确确实实地实现其功能, 而另一个只是简单地调用前者以提供相同的功能. 这将引发两个问题:

1. 选择哪个版本用于实现功能从而另一个版本可以直接调用它来实现相同功能, 或者选任意一个都行?
2. 另一个版本在调用实现了具体功能的版本时, 需要做什么以修改其常量性?

问题1的答案是: 只能选择const版本来实现具体功能, 非const版本则通过调用const版本来提供相同功能. 反过来则行不通.

问题2的答案是: 使用static_cast<const ClassName&>将一开始为reference to object的*this转型为reference to const object. 然后再对转型的结果调用其const版本的成员函数, 并将返回的const常量结果用const_cast来移除其常量性.

```cpp
class Widget {
 public:
  ...
  const int& operator[](std::size_t idx) {
    // 本示例很简单, 实现operator[]的功能只需要一个return语句即可
    return nums[idx];
  }
  int & operator[](std::size_t idx) {
    return const_cast<int&>(
      static_cast<const Widget&>(*this)[idx]
    );
  }
 ...
}
```

## 总结

* 将某些东西声明为const可以帮助编译器侦测出错误用法. const可被施加于任意作用域内的对象/函数参数/函数返回类型/成员函数本身.
* 编译器强制实施bitwise constness. 但你编写程序时应该使用逻辑上的常量性(logical constness).
* 当const和non-const成员函数有着实质等价的实现时, 另non-const版本调用const版本可避免代码重复.