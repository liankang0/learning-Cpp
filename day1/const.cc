#include <iostream>

int main()
{
    int number = 10;
    int number2 = 20;
    const int *pa = &number;//常量指针
 //   *pa = 20;//不能通过pa指针修改所知变量的值
    pa = &number2;// 可以改变pa的指向
    std::cout << "Hello world" << std::endl;
    std::cout << "number is " << number << std::endl;
    return 0;
}

