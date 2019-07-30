
// coding:utf-8

// **********************************************************
// * Author        : liankang
// * Email         : 349915905@qq.com
// * Create time   : 2019-07-30 00:02
// * Filename      : main.cc
// * Description   : 
// **********************************************************
#include "String.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int main(int argc, char** argv)
{
    String test1;
    String test2("hello");
    cout << "test2" << test2 << endl;
    String test3(test2);
    cout << "test3" << test3 << endl;
    test1 = test2;
    cout << "test1: " << test1 << endl;
    test1 += test2;
    cout << "test1: " << test1 << endl;
    test2 += " world";
    cout << "test2: " << test2 << endl;
    cout << "fist of test2: " << test2[0] << endl;
    cout << "out of range test2: " << test2[1000] << endl;
    cout << "size of test3: " << test3.size() << endl;
    cout << "test1 == test2:  " << int(test1 == test2) << endl;//bool不能直接输出？？
    cout << "test1 < test2:  " << int(test1 < test2) << endl;
    cout << "test1 + test2:  " << test1 + test2 << endl;
    cout << "test1 + world:  " << test1 + "world" << endl;
    
    return 0;
}

