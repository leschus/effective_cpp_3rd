# 条款06 若不想使用编译器自动生成的函数, 就该明确拒绝

如果你不打算实现copy构造函数和copy assignment操作符, 并且也不希望编译器为你自动生成它们的默认版本, 你可以将它们声明为private, 并且不提供定义.

```cpp
class Widget {
 public:
  ...
 private:
  ...
  Widget(const Widget&);              // 无需提供函数定义和形参名, 因为该函数根本不会被用到
  Widget& operator=(const Widget&);   // 同上
}
```

通过上述解决方案, 当外界企图调用Widget的copy构造函数或copy assignment操作符时, 将会导致编译错误. 当Widget类的成员函数或者friend函数也企图这么做时, 并不会导致编译错误, 但会引发链接错误! ---- 因为链接器找不到相应函数的定义.

如何将链接期错误转移到编译期(毕竟越早侦测出错误越好)?

答案是使用一个专门为了阻止copying动作而设计的基类, 下面是一个例子:
```cpp
class Uncopyable {
 protected:
  Uncopyable() {}                             // 允许派生对象构造和析构
  ~Uncopyable() {}
 private:
  Uncopyable(const Uncopyable&);
  Uncopyable& operator=(const Uncopyable&);   // 但是阻止copying
};
```

为阻止Widget对象被拷贝, 我们唯一需要做的就是继承Uncopyable:
```cpp
class Widget: private Uncopyable {
  ... //本类中无需再将copy构造函数和copy assignment操作符声明为private
};
```

> Boost提供了相同功能的基类, 名为`noncopyable`.

## 总结

* 为驳回编译器自动(暗自)提供的机能, 可将相应的成员函数声明为private并且不予实现. 继承像Uncopyable这样的基类也是一种做法.

> 注: 相较于本条款中的解决方案, C++11提供了"= delete"完成相同功能, 并且更简便. 鉴于本书写作时间为2005年, 当时C++还不支持"= delete", 所以没有提及这种做法. 通过本注释, 希望读者再次注意, 本书中介绍的各个条款并未涉及到C++11的新特性. Effective系列的介绍C++11及后续版本的特性的书籍是: *Effective Mordern C++*, 该书在Github上有热心人提供了中文翻译. =>[点击跳转到对应Github页面](https://github.com/kelthuzadx/EffectiveModernCppChinese)