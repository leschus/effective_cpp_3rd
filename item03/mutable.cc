#include <iostream>
#include <string>
using namespace std;

class Person {
 public:
  Person(const string& s = "Unknown") : name(s), called_times(0) {}
  const string& getName() const;
  int get_called_times() const;
 private:
  string name;
  mutable int called_times;
};

const string& Person::getName() const {
  called_times++; // 虽然在const成员函数内, 但由于call_times被声明为mutable, 所以仍然可以修改它
  return name;
}

int Person::get_called_times() const {
  return called_times;
}

int main() {
  Person lisa("Lisa");
  lisa.getName();
  cout << lisa.get_called_times() << endl;
  lisa.getName();
  cout << lisa.get_called_times() << endl;
}