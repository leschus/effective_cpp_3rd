#include <iostream>
using namespace std;

class Person {
 public:
  virtual ~Person() { cout << "Person d'tor." << endl; }
  virtual void say() { cout << "I'm human." << endl; }
};

class Student : public Person {
 public:
  void say() { cout << "I'm a student." << endl; }
  ~Student() { cout << "Student d'tor." << endl; }
};


int main() {
  { // 通过基类指针指向基类和派生类对象
    Person *p1 = new Person();
    Person *p2 = new Student();
    p1->say();
    p2->say();
    delete p1;
    delete p2;
  }
  cout << endl;
  { // 通过基类引用指向基类和派生类对象
    Person per;
    Student stu;
    Person &r1 = per;
    Person &r2 = stu;
    r1.say();
    r2.say();
  }
  return 0;
}