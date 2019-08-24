/*********************************************************************
 * @Author           : liankang
 * @Email            : 349915905@qq.com
 * @Date             : 2019-08-23 11:14
 * @Filename         : Noncopyable.h
 * @Description      : 
 * ******************************************************************/
#ifndef _Noncopyable_H_
#define _Noncopyable_H_


class Noncopyable
{
protected:

    Noncopyable() {}
    ~Noncopyable() {}
    Noncopyable(const Noncopyable &)=delete;//c++11特性，禁用复制构造函数
	Noncopyable & operator=(const Noncopyable &)=delete;//c++11特性，禁用复制构造函数


};



#endif

