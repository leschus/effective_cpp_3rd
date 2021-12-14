// 使用auto_ptr

#include <memory>
#include <iostream>

int main() {

  std::auto_ptr<int> p1(new int);
  *p1 = 15;
  std::auto_ptr<int> p2(p1);
  std::cout << (p1.get() == 0) << std::endl;
  std::cout << *p2 << std::endl;
}