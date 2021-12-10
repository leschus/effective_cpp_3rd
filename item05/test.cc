#include <string>
using namespace std;

class Widget {
 public:
  Widget(string& name, double price) : name_(name), price_(price) {}
 private:
  string &name_;        // 存在数据成员为引用类型
  const double price_;  // 存在数据成员为const
};


class A {
 private:
  A& operator=(const A&); // 基类的copy assignment操作符被声明为private
  A(const A&);            // 基类的copy构造函数被声明为private
};

class B : public A {
};

int main() {
  string name1("candy");
  string name2("sugar");
  Widget w1(name1, 11.3);
  Widget w2(name2, 7.5);
  Widget w3(w1);  // copy c'tor
  // w2 = w3;        // copy assignment, ERROR

  B b1, b2;
  // B b3(b1);       // copy c'tor
  // b2 = b1;        // copy assignment, ERROR
}