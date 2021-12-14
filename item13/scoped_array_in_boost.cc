// boost中的scoped_array

#include <iostream>
#include "boost/smart_ptr/scoped_array.hpp"

using namespace boost;
using std::cout;
using std::endl;

class Foo {
 public:
  explicit Foo(int x = 0) : x_(x) {}
  ~Foo() { cout << "Destructing a Foo with x_=" << x_ << endl; }
  void reset(int x) { x_ = x; }
 private:
  int x_;
};

int main() {
  scoped_array<Foo> foos(new Foo[5]);
  for (int i = 0; i < 5; i++) {
    foos[i].reset(i);
  }
}

/* Expected output:

Destructing a Foo with x_=4
Destructing a Foo with x_=3
Destructing a Foo with x_=2
Destructing a Foo with x_=1
Destructing a Foo with x_=0

*/