
// coding:utf-8

// **********************************************************
// * Author        : liankang
// * Email         : 349915905@qq.com
// * Create time   : 2019-07-30 00:00
// * Filename      : String.cc
// * Description   : 
// **********************************************************
#include "String.h"

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::cin;
using std::vector;
String::String()
{
    _pstr = new char[MAXSIZE];
}

String::String(const char* pstr)
    :_pstr(new char[strlen(pstr) + 1])
{
    strcpy(_pstr, pstr);    
}

String::String(const String& rhs)
    :_pstr(new char[strlen(rhs._pstr) + 1])
{
    strcpy(_pstr, rhs._pstr);
}

String::~String()
{
    delete []_pstr;
}
//三部曲：自复制、释放空间、深拷贝
String& String::operator=(const String& lhs)
{
    if(*this != lhs)
    {
        delete [] _pstr;
        _pstr  = new char[strlen(lhs._pstr) + 1];
    }
    strcpy(_pstr, lhs._pstr);
    return *this;
}

//重用上面的赋值=、类型转换的构造函数
String& String::operator=(const char* str)
{
    *this = String(str);
    return *this;
}

String& String::operator+=(const String& lhs)
{
    if(sizeof(_pstr) - strlen(_pstr) < strlen(lhs._pstr))
    {
        char tmp[strlen(_pstr) + 1];
        strcpy(tmp, _pstr);
        _pstr = new char[strlen(_pstr) + strlen(lhs._pstr) + 1];
        strcpy(_pstr, tmp);
        strcat(_pstr, lhs._pstr);
    }
    else
    {
        strcat(_pstr, lhs._pstr);
    }
    return *this;
}
//应该充分应用上面已经重载的运算符
String& String::operator+=(const char* str)
{
    return *this += String(str);
//    if(sizeof(_pstr) - strlen(_pstr) < strlen(str))
//    {
//        char tmp[strlen(_pstr) + 1];
//        strcpy(tmp, _pstr);
//        _pstr = new char[strlen(_pstr) + strlen(str) + 1];
//        strcpy(_pstr, tmp);
//        strcat(_pstr, str);
//    }
//    else
//    {
//        strcat(_pstr, str);
//    }
//    return *this;
        
}

char String::operator[](std::size_t index)
{
    if(index < strlen(_pstr))
    {
        return _pstr[index];
    }
    else
    {
        static char nullchar = '\0';
        return nullchar;
    }
}
//和没有const的区别, 这里可能传入const， 所以传出也应该是const
const char String::operator[](std::size_t index) const
{
        return _pstr[index];
}

std::size_t String::size() const
{
    return strlen(_pstr);
}
const char* String::c_str() const
{
    return _pstr;
}

bool operator==(const String& lhs1, const String& lhs2)
{
    if(strcmp(lhs1._pstr, lhs2._pstr))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool operator!=(const String& lhs1, const String& lhs2)
{
    if(!strcmp(lhs1._pstr, lhs2._pstr))
    {
        return false;
    }
    else
    {
        return true;
    }
}


bool operator<(const String & lhs1, const String& lhs2)
{
    if(0 > strcmp(lhs1._pstr, lhs2._pstr))
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool operator>(const String & lhs1, const String & lhs2)
{
    if(0 < strcmp(lhs1._pstr, lhs2._pstr))
    {
        return true;
    }
    else
    {
        return false;
    }
}
    
bool operator<=(const String & lhs1, const String & lhs2)
{
    if(0 >= strcmp(lhs1._pstr, lhs2._pstr))
    {
        return true;
    }
    else
    {
        return false;
    }
    
}
bool operator>=(const String & lhs1, const String & lhs2)
{
    if(0 <= strcmp(lhs1._pstr, lhs2._pstr))
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

std::ostream &operator<<(std::ostream &os, const String &s)
{
    os << s._pstr;
    return os;
}
//使用vector解决无法知道is流里面内容的大小， 流get() 方法使用
std::istream &operator>>(std::istream &is, String &s)
{
    vector<char> buff;
    buff.reserve(65535);

    char ch;
    while((ch = is.get()) != '\n')
    {
        buff.push_back(ch);
    }
    
    s = &buff[0];

    return is;
}

String operator+(const String & lhs1, const String & lhs2)
{
    String tmp;
    tmp += lhs1;
    tmp += lhs2;
    return tmp;
}

String operator+(const String & lhs1, const char * pstr)
{
    String tmp;
    tmp += lhs1;
    tmp += pstr;
    return tmp;
}
    
String operator+(const char * pstr, const String & lhs)
{
    String tmp;
    tmp += pstr;
    tmp += lhs;
    return tmp;
}
