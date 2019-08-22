#include <iostream>

using std::cout;
using std::endl;
using std::cin;

class Figure
{
public:
    virtual void display() const = 0;
    virtual double area() const = 0;

    virtual ~Figure()
    {   
        cout << "~Figure()" << endl;
    }

};

void display(Figure* fig)
{
    fig->display();
    cout << "的面积是：" << fig->area() << endl;
}






int main(int argc, char** argv)
{
    
    return 0;
}

