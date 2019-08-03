#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::string;

class Person
{
public:
    Person(string name, int age)
    :_name(name)
    ,_age(age)
    {   cout << "Person(string name, int age)" << endl; }
    
    void display()
    {
        cout << "name = " << _name << endl;
        cout << "age = " << _age << endl;
    }

private:
    string _name;
    int _age;
};

class Employee
:public Person
{
public:
    Employee(string name, int age,string department, double salary)
    :Person(name, age)
    ,_department(department)
    ,_salary(salary)
    {
        cout << "Employee(string name, int age,string department, double salary)" << endl;
    }

    void display()
    {
        Person::display();
        cout << "department = " << _department << endl;
        cout << "salary = " << _salary << endl;
    }
    
    double getSalary()
    {
        return _salary;
    }
private:
    string _department;
    double _salary;
};



int main(int argc, char** argv)
{
    Employee employee1("xiaowang", 30, "01", 8000);
    Employee employee2("xiaojiu", 34, "04", 8400);
    Employee employee3("dawang", 50, "03", 8040);
    employee1.display();
    employee2.display();
    employee3.display();
    cout << "the avarge salary = " << (employee1.getSalary() + \
                        employee2.getSalary() + employee3.getSalary()) / 3 << endl;
    
    return 0;
}

