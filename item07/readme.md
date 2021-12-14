# 条款07: 为多态基类声明virtual析构函数

如果希望同一个方法基类和派生类中的行为不同, 即方法的行为取决于调用它的对象, 则需要用到"多态"机制.

公有继承下的多态的实现基于两点:
1. 在派生类中重新定义基类的方法(重写, override);
2. 使用virtual方法;

当使用基类指针指向基类对象或者派生类对象时, 通过指针调用virtual方法将呈现多态特性.
```cpp
class TimeKeeper {
 public:
  TimeKeeper();
  virtual ~TimeKeeper();
  ...
};

class AtomicClock : public TimeKeeper {...};    // 原子钟
class WaterClock : public TimeKeeper {...};     // 水钟
class WristClock : public TimeKeeper {...};     // 腕表
```

多态基类中可能会有各种各样名称的virtual成员函数, 但统一的是, 它们都必须得有一个virtual析构函数. 当需要使用基类的接口处理派生类的对象时, 可以用基类指针/引用指向派生类对象, 而由于virtual析构函数的存在, 在使用完这些指针/引用后, 其所指向的对象能够正确地被析构.

将成员函数声明为virtual会导致class对象的内存成本增加, 因为对象现在需要维护一个指向虚函数表vtbl的指针vptr. 虚函数表中保存了该对象所有的virtual函数的入口地址.

对于抽象基类, 其中常常没有任何功能性的函数(指除了基本的构造/析构之类的函数以外的成员函数), 这时候, 可以选析构函数作为pure virtual函数, 见下例.
```cpp
class AMOV {
 public:
  virtual ~AMOV() = 0;
};
```
需要为该pure virtual析构函数提供定义, 原因是派生类在执行析构时, 会自动调用其基类的析构函数, 而如果抽象基类中的析构函数没有提供定义, 则会导致链接错误(找不到符号定义).
```cpp
AMOV::~AMOV() {}      // 函数体里啥都不做, 仅仅是提供一份定义.
```

并非所有用作基类的类都需要声明virtual析构函数, 因为设计这些基类的意图可能并不是想要"经由基类的接口处理派生类对象", 例如条款6中的Uncopyable和标准程序库中的input_iterator_tag(条款47).

## 总结

* 带多态性质的基类应当声明一个virtual析构函数. 如果class中包含任何virtual函数, 那么请务必保证其中一个virtual函数是析构函数.
* classes的设计目的如果不是作为基类使用, 或者虽然是作为基类, 但并不具备多态性, 则不应该声明virtual析构函数.