#pragma once

class String
{
public:
    String();
    String(const char* pstr);
    String(const String & rhs);
    String & operator=(const String & rhs);
    ~String();
     
    void print();

private:
    char* _pstr;
};


