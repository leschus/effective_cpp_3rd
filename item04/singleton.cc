#include <iostream>

class Singleton {
 public:
  static Singleton* get() {
    if (!instance) {
      instance = new Singleton();
    }
    return instance;
  }
  static void restart() {
    if (instance) {
      delete instance;
    }
  }
  void tell() {
    std::cout << "This is Singleton." << std::endl;
  }
 private:
  // 禁止外部执行默认构造
  Singleton() {};   // 需要给出定义(虽然这里定义体为空), 因为第7行需要调用它
  // 禁止外部执行拷贝构造
  Singleton(const Singleton&);
  // 禁止外部执行赋值运算
  Singleton& operator=(const Singleton&);
 private:
  static Singleton *instance;
};

Singleton* Singleton::instance = 0;

int main() {
  Singleton::get()->tell();
  Singleton::restart();
}