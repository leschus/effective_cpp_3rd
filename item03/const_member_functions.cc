#include <vector>
#include <iostream>
using namespace std;

class Widget {
 public:
  Widget() : nums(Size) {}
  Widget(const Widget& rhs) : nums(rhs.nums) {}
  bool update(std::size_t idx, int val); // 更新nums[idx]的值为val
  void print() const; // 打印nums
  int& operator[](std::size_t idx);
  const int& operator[](std::size_t idx) const;
 private:
  vector<int> nums;
  enum { Size = 5 };
};

bool Widget::update(std::size_t idx, int val) {
  if (idx < nums.size()) {
    nums[idx] = val;
    return true;
  }
  return false;
}

void Widget::print() const {
  for (vector<int>::const_iterator it = nums.begin(); it != nums.end(); it++) {
    cout << *it << " ";
  }
  cout << endl;
}

int& Widget::operator[](std::size_t idx) {
  return nums[idx];
}

const int& Widget::operator[](std::size_t idx) const {
  return nums[idx];
}

class CWidget {
 public:
  CWidget() {
    nums = new int(Size);
    for (int i = 0; i < Size; i++) {
      nums[i] = 0;
    }
  }
  // 下面的函数修改了nums的内容, 但却能够通过bitwise测试!
  int& operator[](std::size_t idx) const { nums[idx]++; return nums[idx]; }
 private:
  int *nums;
  enum { Size = 5 };
};

int main() {
  Widget w1;
  w1.update(0, 1);
  w1.print();
  const Widget w2(w1);
  w2.print();
  // w2.update(1, 1); // 不能对const对象调用非const成员函数

  Widget a;
  a[0] = 1;             // OK
  cout << a[0] << endl; // OK
  const Widget b;
  // b[0] = 1;             // ERROR
  cout << b[0] << endl; // OK
}