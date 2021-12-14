// 测试boost中的scoped_ptr

#include "boost/smart_ptr/scoped_ptr.hpp"

int main() {
  boost::scoped_ptr<int> p1(new int);
  *p1 = 15;
  // boost::scoped_ptr<int> p2(p1);  // 不同于auto_ptr, scoped_ptr不允许copy构造
  boost::scoped_ptr<int> p3;
  // p3 = p1;    // 同样地, scoped_ptr也不允许copy assignment操作
  // scoped_ptr的这种机制从源头上避免了auto_ptr的问题: 即拷贝构造或赋值运算之后
  // 导致用于拷贝/赋值的智能指针不再有效(指向0).
}