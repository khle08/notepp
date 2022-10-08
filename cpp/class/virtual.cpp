#include <iostream>
#include <string>

#define print(x) std::cout << x << std::endl


class Entity
{
public:
    // a virtual function is a type of function that could be redefined in
    // the other class which inherits this class.
    virtual std::string GetName()
    {
        // if sth is returned or defined here, it means that there is a default
        // mechanism for all classes that inherit this class.
        return "Entity method";
    }

    // >>> interface <<< ///
    // on the other hand, we can also force the other class to redefine this
    // virtual method as their own unique version using the following code.
    // -> virtual std::string GetName() = 0;

    // but if the code is written this way, this class could no longer be able to
    // be instantiated along. In addition, if the class that inherits this function
    // also does not define the "pure virtual function", it will also not work.
};


// Play is the subclass of the "Entity" class defined above.
class Player: public Entity
{
private:
    std::string tempName;
public:
    Player(const std::string& name)
        : tempName(name) {}

    // create a new method with the same name as the method in Entity class.
    std::string GetName()
    {
        return tempName;
    }
};


class Printable
{
public:
    virtual std::string GetClassName() = 0; 
};


class A: public Printable
{
public:
    std::string GetClassName() override {return "A";}
};


void logInfo(Printable* obj)
{
    print(obj->GetClassName());
}


int main()
{
    // instantiate a class using "new" in heap memory.
    Entity* e = new Entity();
    print(e->GetName());

    Player* p = new Player("Hello");
    print(p->GetName());

    Entity* e2 = p;
    print(e2->GetName());

    logInfo(new A());
    return 0;
}