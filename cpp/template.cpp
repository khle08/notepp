#include <iostream>
#include <string>

////////////////// these 2 functions have the same effect //////////////////////
#define print(x) std::cout << x << std::endl
template<typename T>
void Print(T x)
{
    std::cout << x << std::endl;
}
// ... but x can only be a value instead of something like: x << "str" << "else"
// template will only be called when the function is called. If there are some
// errors in a template function, it is still fine to compile code sometimes. 
////////////////////////////////////////////////////////////////////////////////

template <typename T, int N>
class Array
{
private:
    int m_Array[N];
public:
    int GetSize() const {return N;}
};

int main()
{
    // the parameter defined in template can also be sent to the function.
    Array<int, 10> arr;
    print(arr.GetSize());
    return 0;
}