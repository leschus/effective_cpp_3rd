# effective_cpp_3rd
*Effective C++: 改善程序于设计的55个具体做法: 第3版* / Scott Meyers著, 侯捷译.

## 1 让自己习惯C++

* [条款01: 视C++为一个语言联邦](item01/)
* [条款02: 尽量以const, enum, inline替换#define](item02/)
* [条款03: 尽量使用const](item03/)
* [条款04: 确保对象被使用前已先被初始化](item04/)

## 2. 构造/析构/赋值运算

* [条款05: 了解C++默默编写并调用哪些函数](item05/)
* [条款06: 若不想使用编译器自动生成的函数, 应当明确拒绝](item06/)
* [条款07: 为多态基类声明virtual析构函数](item07/)
* [条款08: 别让异常逃离析构函数](item08/)
* [条款09: 绝不在构造和析构过程中调用virtual函数](item09/)
* [条款10: 令operator=返回一个reference to *this](item10/)
* [条款11: 在operator=中处理"自我赋值"](item11/)
* [条款12: 复制对象时勿忘其每一个成分](item12/)

## 3. 资源管理

* [条款13: 以对象管理资源](item13/)
* [条款14: 在资源管理类中小心copying行为](item14/)
* [条款15: 在资源管理类中提供对原始资源的访问](item15/)
* [条款16: 成对使用new和delete时要采取相同形式](item16/)
* [条款17: 以独立语句将newed对象置入智能指针](item17/)

## 4. 设计与声明

* [条款18: 让接口容易被正确使用,  不易被误用](item18/)
* [条款19: 设计class犹如设计type](item19/)
* [条款20: 宁以pass-by-reference-to-const替换pass-by-value](item20/)
* [条款21: 必须返回对象时, 别妄想返回其reference](item21/)
* [条款22: 将成员变量声明为private](item22/)
* [条款23: 宁以non-member & non-friend替换member函数](item23/)
* [条款24: 若所有参数皆需类型转换, 请为此采用non-member函数](item24/)
* [条款25: 考虑写出一个不抛异常的swap函数](item25/)