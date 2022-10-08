#include <iostream>
#include <string>

#define print(x) std::cout << x << std::endl

/*
 a class is a user defined "data-type" containing members and member functions.

 */
class Entity
{
public:
    float x, y;

    Entity(const float& x, const float& y): x(x), y(y) {}
    // Entity(const float& a, const float& b) {x = a, y = b}

    void Move(float xa, float ya)
    {
        x += xa;
        y += ya;
    }

private:
    int z1 = 50;
    int z2 = 60;
};


// Play is the subclass of the "Entity" class defined above.
class Player: public Entity
{
public:
    const char* Name;

    void PrintName()
    {
        print(Name);
    }
};


int main()
{
    // instantiate a class in stack memory (栈内存).
    Entity eStack(10, 11);
    eStack.Move(100, 200);
    // things in the class can only be accessed by "."
    print("Move to: " << eStack.x << " " << eStack.y);
    print(" ");

    // instantiate a class using "new" in heap memory (堆内存).
    Entity* eHeap = new Entity(3, 5);
    eHeap->Move(10, 20);
    // things in the class can only be accessed by "->"
    print("Move to: " << eHeap->x << " " << eHeap->y);
    print(" ");

    // private parameters can not be accessed.
    // error: ‘int Entity::z1’ is private
    // print("Private: " << eHeap->z1);

    // Player* p = new Player(1, 2);
    // print(p->Name);

    // data-type can be specified using template.
    Print<int>(5);

    return 0;
}