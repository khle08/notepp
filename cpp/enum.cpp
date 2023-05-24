
#include <iostream>
#include <typeinfo>


#define print(x) std::cout << x << std::endl


enum State
{
    Checked = 21,  // This is used to define the beginning number
    Talented,      // The following obj value will be x += 1 sequentially
    Qualified,
    Disqualified,
};


class Room
{
public:
    int Teacher;
    int Student;
    State status;
};


int main()
{
    print("\n===== int =====");
    int x = 11;
    print(x << ", type: " << typeid(x).name());

    print("\n===== enum =====");
    State n = State::Checked;
    print(n << ", type: " << typeid(n).name());
    // where the type is 5State, which means <n><enum name>, ...
    // ... number of enum characters & the enum name

    n = State::Talented;
    print(n << ", type: " << typeid(n).name());

    n = State::Qualified;
    print(n << ", type: " << typeid(n).name());

    n = State::Disqualified;
    print(n << ", type: " << typeid(n).name());

    print("\n===== class =====");
    Room r = Room();
    print(r.Teacher << ", type: " << typeid(r).name());
    // where the type is 4Room, which means <n><class name>, ...
    // ... number of class characters & the class name

    return 0;
}

