#include <gtest/gtest.h>

class A {
  public:
    static int a;
};

int A::a;

class B : public A {};

TEST(CppSyntaxTest, StaticInheritance) {
  A::a = 14;
  ASSERT_TRUE(B::a == 14);
  A::a = 666;
  ASSERT_TRUE(B::a == 666);
}

template<typename T>
class X {
  public:
    T a;
    X() = default;
    X(T a) : a(a) {}

    template<typename B>
    X<T> operator+(X<B> &other) {
      return X(this->a + other.a);
    }
    template<typename B>
    X<T> operator*(B other) {
      return X(this->a * other);
    }
};

using T1 = X<int>;
using T2 = X<float>;

TEST(CppSyntaxTest, TemplateFunctionsTest) {
  T1 a = T1();
  T2 b = T2();
  a + b;
  a * 1;
}
