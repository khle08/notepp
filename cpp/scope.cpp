#include <iostream>
#include <typeinfo>
#include <string>
#include <cmath>

#define print(x) std::cout << x << std::endl

// for a static variable or function, the name can only be used in the file
static int private_var = 5;

enum Example
{
	A = -10, B, C
};

namespace space1
{
	enum Animal: char
	{
		// the value in "enum" must be an integer
		SHEEP,
		COW,
		DONKEY,
		FISH
	};

	int add(int a, int b)
	{
		return a + b;
	}
}

namespace space2
{
	// for a inline function, it means that whatever code defined in the function
	// will be copied to the place where the function is executed instead of just
	// calling the specific function saved in a memory.
	inline int add(int a, int b)
	{
		return (a + b) * 2;
	}
}

int main(int argc, char const *argv[])
{
	print(space1::SHEEP);
	print(space1::Animal::FISH);
	print("Example A,B,C val: " << A << " " << B << " " << C);

	// new assignment can be made but make sure that the value can only be
	// those included in "enum" such as A, B, or C.
	space1::Animal DOG = space1::FISH;
	print(DOG);
	Example val = B;
	print(val);
	// but mind that the new assigned variable does not belong to the space
	// or the name of "enum". It only represents itself.

	int ans1 = space1::add(1, 2);
	int ans2 = space2::add(1, 2);

	print(ans1);
	print(ans2);
	return 0;
}