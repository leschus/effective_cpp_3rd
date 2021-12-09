# 条款02 尽量以const, enum, inline替换#define

> 这个条款其实是在说: 尽量使用编译器而非预处理器.

## 使用const常量替换#define所定义的宏

不建议编写如下代码:
```cpp
#define PI 3.14
```
而是要使用const定义相关常量:
```cpp
const double kPi = 3.14;
```

对指针使用const时, 要注意指针本身和其所指向的内容都要为const. 例如:
```cpp
const char* const authorName = "Scott Meyers";
```

## class的专属常量

即给类的静态数据成员(static)添加常量属性(const):
```cpp
// widget.h
class Widget {
 private:
  static const int Zero = 0;  // static和const书写次序任意
  static const double Pi;     // 对于静态非整数类型常量, 不能在类内初始化
  ...
}
```
对于类的静态非整数类型常量, 不能在类内对其进行初始化, 而是要在实现文件中给出该常量的定义式并同时赋予初值:
```cpp
// widget.cc
const double Widget::Pi = 3.14;
```
对于类的静态整数类型常量, 可以在类内对其进行初始化, 因此不必要像Widget::Pi那样在实现文件中写一遍定义式. 一个例外是, 如果程序需要取该整数常量的地址, 则必须在实现文件中给出该常量的定义式. 当然, 如果该常量已在类内初始化, 则不需要(也不能够)再次对其赋初值.
```cpp
// widget.cc
const int Widget::Zero;
```
对于类的静态整数类型常量, 有一种替换方案: 使用enum. 理论依据是: 一个枚举类型的数值可以被当作int常量来使用. 由于**enum常量不能被取地址**, 因此当你不想让别人使用指针或引用指向你的某个常量时, 你可以使用enum而非const来定义这个常量.
```cpp
class Widget {
 private:
  ...
  enum { Length = 10 };
}
```

## 使用inline函数替换形似函数的宏

不要编写如下代码:
```cpp
#define MAX(a, b) ((a) > (b) ? (a) : (b))
```
而是使用inline函数实现该功能:
```cpp
template <typename T>
inline const T& max(const T& a, const T& b) {
  return a > b ? a : b;
}
```

## 总结

* 对于单纯常量, 最好使用const对象或enums替换#define.
* 对于形似函数的宏(macros), 最好改用inline函数替换#defines.