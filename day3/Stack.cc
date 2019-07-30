#include <iostream>
using std::cout;
using std::endl;

class Stack
{
public:
    Stack()
        :lenth(0)
    {}


    void push(int);
    void pop();
    int top();
    bool empty();
    bool full();

private:
    int mumber[10];
    int lenth;
};

void Stack::push(int val)
{
    if(!full())
    {
        mumber[lenth] = val;
        lenth++;  
    }
    else
    {
        cout << "栈满了，不能入栈" << endl;
    }
}

void Stack::pop()
{
    if(!empty())
    {
        lenth--;
    }
    else
    {
        cout <<  "栈空，不能出栈" << endl;
    }
}

int Stack::top()
{
    if(!empty())
    {
        return mumber[lenth-1];
    }
    else
    {
        cout <<  "栈空，不能读取栈顶元素" << endl;
        return -1;
    }
}

bool Stack::empty()
{
    return lenth?false:true;
}

bool Stack::full()
{
    return (lenth == 9)?true:false;
}

int main()
{
    Stack s1;
    s1.push(10);
    s1.push(12);
    s1.push(14);
    cout << s1.top() << endl;
    s1.pop();
    cout << s1.top() << endl;
    return 0;
}

