class Widget {
 private:
  static const int Zero = 0;
  static const double Pi /* = 3.14 */; // 类的静态非整数类型常量不能在类内初始化
  enum { Ten = 10 };
 public:
  static void print_value();
  static void print_address();
};

template <typename T>
inline const T& max(const T& a, const T& b) {
  return a > b ? a : b;
}