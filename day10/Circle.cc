#include <iostream>
#define PI 3.1415926
using std::cout;
using std::endl;
using std::cin;

class Circle
{
public:
    Circle()
        :_r(0)
    {
        cout << "Circle()" << endl; }
    Circle(double r)
        :_r(r)
    {   cout << "Circle(double r)" << endl; }
    double getArea();       //获取圆面积
    double getPerimeter();  //获取圆的周长
    void show();            //将圆的半径、周长、面积输出到屏幕

private:
    double _r;//半径
};

class Cylinder
:public Circle
{
public:
    Cylinder(double r, double h)
    :Circle(r)
    ,_h(h)
    {   cout << "Cylinder(double r, double h)" << endl; }
    
    double getVolume();
    void showVolume();

private:
    double _h;
};

double Circle::getArea()
{
    return PI * _r *_r;
}

double Circle::getPerimeter()
{
    return 2 * PI * _r;
}

void Circle::show()
{
    cout << "_r = " << _r << endl;
    cout << "Area = " << getArea() << endl;
    cout << "Perimeter = " << getPerimeter() << endl;

}

double Cylinder::getVolume()
{
   return getArea() * _h; 
}

void Cylinder::showVolume()
{
    cout << "volume =  " << getVolume() << endl;
}



int main(int argc, char** argv)
{
    Circle circle;
    Circle circle1(5);
    circle.show();
    circle1.show();
    Cylinder cylinder(5, 5);
    cylinder.showVolume();
    return 0;
}

