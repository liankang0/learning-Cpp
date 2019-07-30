#include "String.h"

#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

String::String()
:_pstr(new char[1]())
{
    
}

String::String(const char * pstr)
:_pstr(new char[strlen(pstr) + 1]())
{
   strcpy(_pstr, pstr);
}

String::String(const String & rhs)
:_pstr(new char[strlen(rhs._pstr) + 1]())
{
    strcpy(_pstr, rhs._pstr);
}

String & String::operator=(const String & rhs)
{
    if(this != &rhs)
    {
        cout << "String & operator=(const String & )" << endl;
        delete [] _pstr;

        _pstr = new char[strlen(rhs._pstr) + 1]();
        strcpy(_pstr, rhs._pstr);
    }
    return *this;
}

String::~String()
{
    if(_pstr)
    {
        delete [] _pstr;
    }
    cout << "~String()" << endl;

}

void String::print()
{
    if(_pstr)
    {
        cout << _pstr << endl;
    }
}
