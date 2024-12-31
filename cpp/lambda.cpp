
#include <iostream>
#include <functional>


// Template function accepting any callable as parameter
template <typename Callable>
void execute_task1(Callable task) {
    task();  // Call the passed lambda or function
}


// Function accepting a lambda with a specific signature: takes an int, returns void
void execute_task2(const std::function<void(int)>& task, int value) {
    task(value);  // Call the lambda or function with a parameter
}


int main() {
    auto myLambda1 = []() {
        std::cout << "Hello from Lambda!" << std::endl;
    };

    execute_task1(myLambda1);  // Pass the lambda to the function

    auto myLambda2 = [](int x) {
        std::cout << "Lambda received: " << x << std::endl;
    };

    execute_task2(myLambda2, 30);  // Pass the lambda to the function

    return 0;
}
