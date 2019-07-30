#include <string.h>
#include <stdlib.h>

#include <iostream>
using std::cout;
using std::endl;

class Student
{
public:
    Student(int id, const char* name)
    :_id(id)
    ,_name(new char[strlen(name) + 1]())
    {
        strcpy(_name, name);
        cout << "Student(int, char*)" << endl;
    }

    ~Student()
    {
        cout << "~Student()" << endl;
        if(_name)
        {
            delete [] _name;
            _name = NULL;
        }
    }

    void operator delete(void* p)
    {
        cout << "void* operator delete(void*)" << endl;
        free(p);
    }

    void print()
    {
        cout << "id : " << _id << "name:" << _name << endl;
    }

private:
    void* operator new(size_t sz)
    {
        cout << "void* operator new(size_t)" << endl;
        void* ret = malloc(sz);
        return ret;
    }
    int _id;
    char* _name;
};

int main()
{
    Student stu(100, "Rose");
    //Student* pstu = new Student(100, "Jackie");error
    stu.print();
    return 0;
}
