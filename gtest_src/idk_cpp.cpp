#include <gtest/gtest.h>
#include <vector>

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

void a() {
    static int a = 0;
    std::cout << "out:" << a << std::endl;
    {
        static int a = 4;
        a++;
        std::cout << "in:" << a << std::endl;
    }
    a++;
    std::cout << "out:" << a << std::endl;
}

TEST(CppSyntaxTest, StaticInScope) {
  a();
  a();
  a();
  a();
}

TEST(CppSyntaxTest, Autoiterator) {
  std::vector<int> v = {1,2,3,4};
  for (auto it = v.begin(); it != v.end(); ++it) {
      // if the current index is needed:
      auto i = std::distance(v.begin(), it); 

      // access element as *it

      // any code including continue, break, return
  }
}

#define 👉 ->

TEST(CppSyntaxTest, HandPointer) { 
  struct A {
    int a;
  };
  A* b = new A();
  b 👉 a = 4;
  std::cout << b 👉 a << std::endl;
  delete b;
}

TEST(CppSyntaxTest, VectorOfPointersRef) { 
  std::vector<int*> vp = {};
  std::vector<int> v = {1,2,3,4,5};
  for (auto& i : v) {
    vp.push_back(&i);
  }
  for (const auto& i : vp) {
    std::cout << *i<< std::endl;
  }
}

TEST(CppSyntaxTest, VectorOfPointers) { 
  std::vector<int*> vp = {};
  std::vector<int> v = {1,2,3,4,5};
  for (auto& i : v) {
    vp.push_back(&i);
  }
  for (const auto& i : vp) {
    std::cout << *i<< std::endl;
  }
}
