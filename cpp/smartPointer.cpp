// 一切解释都在 main 函数里，再一一对应到上方定义的不同类和函数中调用测试

// Smart Pointers 智能指针 - C++ Weekly EP3
// ref: https://www.youtube.com/watch?v=KQt3IjGdqL8&t=128s&ab_channel=HuaHua

#include <iostream>
#include <string>
#include <vector>

// this can only be used since C++14
#include <memory>    // For shared pointer

#define print(x) std::cout << x << std::endl


class Entity
{
public:
    Entity() {print("Entity created");}
    ~Entity() {print("Entity destroyed");}
};


void unique_exp1()
{
    print("\nunique_exp1 func started");
    {
        print("entering unique_exp1::scope1");
        std::unique_ptr<Entity> e1 = std::make_unique<Entity>();
        print("leaving unique_exp1::scope1");
    }   // "e1" will end in this line.
    print("unique_exp1 func ended\n");
}


void unique_foo(std::unique_ptr<Entity>)
{
    print("unique_foo func started");
    print("unique_foo func ended");
}


void unique_exp2()
{
    print("\nunique_exp2 func started");
    std::unique_ptr<Entity>e2 = std::make_unique<Entity>();
    unique_foo(std::move(e2));
    print("unique_foo func ended\n");
}


void shared_exp3()
{
    print("\nshared_exp3 func started");
    std::shared_ptr<Entity> e3 = std::make_shared<Entity>();
    print("e3 counter: " << e3.use_count());
    {
        print("entering shared_exp3::scope1");
        std::shared_ptr<Entity> e31 = e3;
        print("e3 counter: " << e3.use_count());
        print("e31 counter: " << e31.use_count());
        std::shared_ptr<Entity> e32 = std::move(e31);
        print("e3 counter: " << e3.use_count());
        print("e31 counter: " << e31.use_count());
        print("leaving shared_exp3::scope1");
    }
    print("e3 counter: " << e3.use_count());
    print("shared_exp3 func ended");
}


void weak_foo(std::weak_ptr<Entity> ew)
{
    if (std::shared_ptr<Entity> e = ew.lock()) {
        print("e counter: " << e.use_count());
        print("'weak_ptr' still alive");
    } else {
        print("'weak_ptr' was expired");
    }
}


void weak_exp4()
{
    print("\nweak_exp4 func started");
    std::weak_ptr<Entity> ew;
    {
        print("entering weak_exp4::scope1");
        std::shared_ptr<Entity> e1 = std::make_shared<Entity>();
        print("e1 counter: " << e1.use_count());
        ew = e1;  // shared_ptr can be assigned to weak_ptr directly.
        print("e1 counter: " << e1.use_count());
        weak_foo(ew);
        print("leaving weak_exp4::scope1");
    }
    weak_foo(ew);
    print("weak_exp4 func ended");
}


int main()
{
    print("\n========== shared_ptr [start] ==========");
    // 1. 共享所有权指针 - shared_ptr
    // 多个共享指针可以指向同一个对象，只有当最后一个指针的所有者被销毁的时候，关联对象
    // 才会被真正删除 (类似佛地魔的分灵体)，创建方式有三种分别如下：
    std::shared_ptr<std::string> pStr1 {new std::string("Tom")};     // Ok!
    // std::shared_ptr<std::string> pStr1(new std::string("Tom"));   // Ok!
    // std::shared_ptr<std::string> pStr1 = new std::string("Tom");  // Wrong!
    
    std::shared_ptr<std::string> pStr2;  // 空指针
    pStr2.reset(new std::string("Adom"));

    // 这个方法是最好的，因为只做了一次拷贝，速度最快
    std::shared_ptr<std::string> pStr3 = std::make_shared<std::string>("Bob");

    std::vector<std::shared_ptr<std::string>> container;
    container.push_back(pStr3);
    container.push_back(pStr2);
    container.push_back(pStr3);

    for (auto i: container) {
        print(*i);
    }

    // 修改这个指针对应的值，则 container 里的所有 pStr3 都会一起被修改，因为他们指向同一个地址
    *pStr3 = "Tomorrow";

    for (auto i: container) {
        print(*i);
    }
    // 但其实跑了之后发现这个范例是个废话，因为不用智能指针也能做到这件事 ...
    // 和一般指针的对比详情可以回顾 pointer.cpp

    print("========== shared_ptr  [end]  ==========\n");
    ////////////////////////////////////////////////////////////////////
    print("\n========== unique_ptr [start] ==========");

    // 2. 独占所有权指针 - unique_ptr
    // void bar(Entity* e) {
    //     // Who owns "e"?
    //     // How long is "e"'s life cycle?
    //     // Should I delete "e" at the end of this func?
    // }

    // void foo() {
    //     Entity* e = new Entity();
    //     e->DoSomething();
    //     bar(e);
    // }

    // 一旦 foo() 函数运行完，则 "e" 指针即泄漏，意味着再也找不回来他的地址，因为
    // 没有变量保存这块地址，也没有变量可以呼叫地址对应的值
    // foo();

    // 如果这种情况下使用智能指针则可完美解决此类问题
    // void bar(std::unique_ptr<Entity> e) {
    //     // "bar" func owns "e"?
    //     // "e" will be automatically destroyed at the end of this func?
    // }

    // void foo() {
    //     std::unique_ptr<Entity> e = std::make_unique<Entity>();
    //     std::unique_ptr<Entity> e2 = e;  // unique 的无法拷贝，要的话只能 move 所有权
    //     e->DoSomething();
    //     bar(std::move(e));  // movable, 修改所有权给到 bar 函数
    // }

    unique_exp1();
    unique_exp2();

    // 总结看来其实 unique_ptr 和 shared_ptr 其实用法一模一样，唯一区别在于它可以 copy
    std::shared_ptr<Entity> e21 = std::make_shared<Entity>();
    std::shared_ptr<Entity> e22 = e21;

    // 而此一区别是因为 shared_ptr 中有一个 counter 记录现在有几个东西共享了同一个 object
    // 如果使用上述 copy 的形式，则 counter += 1，不过也可以像 unique_ptr 一样使用
    // std::move() 来转移所有权，这时候 counter 就不会 +1

    shared_exp3();

    print("========== unique_ptr  [end]  ==========\n");
    ////////////////////////////////////////////////////////////////////
    print("\n========== weak_ptr [start] ==========");

    // 3. 没有所有权的指针 - weak_ptr
    // 如果要使用这个指针类型，需要先转成 shared_ptr，如果使用的时候还存在的话就用一下
    // 如果不存在的话就算了，不用也罢，初始化的方法也是得从 shared_ptr 开始，如下示例：
    std::shared_ptr<Entity> e4 = std::make_shared<Entity>();
    std::weak_ptr<Entity>   ew = e4;  // 切忌不能直接在这 std::make_shared
    // 需要先初始化一个 shared_ptr 变量，才能再赋值到 weak_ptr 中

    // 当要使用的时候，检查看一下是否还在，在的话就启动：
    if (std::shared_ptr<Entity> e41 = ew.lock()) {
        print("!!! still exist !!!");
        // e41->DoSomething();
    }

    weak_exp4();

    print("========== weak_ptr  [end]  ==========\n");
}

