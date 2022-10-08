#include "class.h"

#define print(x) std::cout << x << std::endl


int main(int argc, char const *argv[])
{
	// instantiate a class using "new" in heap memory.
	LandOwner* p_owner1 = new LandOwner();
	LandOwner* p_owner2 = new LandOwner("professional");
	LandOwner* p_owner3 = new LandOwner("Ben", "male", 500, 10);
	print(" ");

	p_owner1 -> ShowInfo();
	print(" ");

	p_owner2 -> ShowInfo();
	print(" ");

	p_owner3 -> ShowInfo();
	print(" ");

	// release memory from heap 堆内存
	delete p_owner1;
	delete p_owner2;
	delete p_owner3;
	return 0;
}