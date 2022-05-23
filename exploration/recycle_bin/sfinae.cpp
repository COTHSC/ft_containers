#include <iostream>
template<bool Condition, typename T = void>
struct enable_if
{
};
 
template<typename T>
struct enable_if<true, T>
{
    typedef T type;
};


template<typename T>
class MyClass
{
public:
    void f(T const& x);
    void f(T&& x,
          typename std::enable_if<!std::is_reference<T>::value,
          std::nullptr_t>::type = nullptr);
};

int main() {
    MyClass test;
    return 0;
}
