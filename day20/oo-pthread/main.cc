/*********************************************************************
 * @Author           : liankang
 * @Email            : 349915905@qq.com
 * @Date             : 2019-08-23 13:53
 * @Filename         : main.c
 * @Description      : 
 * ******************************************************************/
#include "Thread.h"

#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <memory> 
using std::cout;
using std::endl;
using std::unique_ptr;

class Mythread
: public Thread
{
	void run() override
	{
		::srand(::clock());
		while(1) {
			int number = ::rand() % 100;
			cout << ">> number = " << number << endl;
			::sleep(1);
		}
	}
};
 
int main(void)
{
	Mythread thread1;
	//Mythread thread2 = thread1;//error 禁止复制

	unique_ptr<Thread> thread(new Mythread());
	thread->start();//产生子线程
	thread->join();
	//::sleep(10);
	return 0;
}


