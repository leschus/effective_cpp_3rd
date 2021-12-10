// 测试virtual导致的对象内存的增加
#include <iostream>
using namespace std;

class Number {
 public:
  Number(float x = 0.0) : value(x) {}
 private:
  float value;
};

class VNumber {
 public:
  VNumber(float x = 0.0) : value(x) {}
  virtual ~VNumber() {}
 private:
  float value;
};

int main() {
  Number a;
  VNumber b;
  cout << sizeof(float) << endl;    // 4
  cout << sizeof(a) << endl;        // 4
  cout << sizeof(b) << endl;        // 16. value占4B, 由于内存对齐导致实际占用8B,
                                    // 另外vptr占用8B (因为在64位机器上).
}