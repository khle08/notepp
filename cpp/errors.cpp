#include <iostream>

#define print(x) std::cout << x << std::endl


class bar
{
public:
    bar()
    {
    	print("bar() called");
    }

    ~bar()
    {
    	print("~bar() called");

    }
};


class foo
{
public:
    foo()
        : b(new bar())
    {
    	print("foo() called");
        throw "throw something";
    }

    ~foo()
    {
        delete b;
        print("~foo() called");
    }

private:
    bar *b;
};


int main()
{
	// foo *f = new foo();
    try {
    	print("heap: new foo");
        foo *f = new foo();
    } catch (const char *e) {
    	print("heap exception: " << e);
    }

    try {
    	print("stack: foo");
        foo f;
    } catch (const char *e) {
    	print("stack exception: " << e);
    }

    return 0;
}