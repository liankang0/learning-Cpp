#include <iostream>
using std::cout;
using std::endl;

class Que
{
public:
    Que()
        :head(0),
        tail(0)
    {}
    void push(int);
    void pop();
    int front();
    int back();
    bool empty();
    bool full();

private:
    int mumber[10];
    int head;
    int tail;

};



bool Que::empty()
{   
    return (head - tail)?false:true;
}
bool Que::full()
{
    return (head - tail == 10)?true:false;
}
void Que::push(int val)
{
    if(!full())
    {
        mumber[head % 10] = val;
        head++;
    }
    else
    {
        cout << "队列满，入队失败" << endl;
    }
}
void Que::pop()
{
    if(!empty())
    {
        tail++;
    }
    else
    {
        cout << "队列空，出队失败" << endl;
    }
}

int Que::front()
{
    if(!empty())
    {
        return mumber[(head-1) % 10];
    }
    else
    {
        return -1;
    }
}
int Que::back()
{
    if(!empty())
    {
        return mumber[tail % 10];
    }
    else
    {
        return -1;
    }
}


int main()
{
    Que q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);
    q1.push(4);
    q1.push(5);
    q1.push(6);
    q1.push(7);
    q1.push(8);
    q1.push(9);
    q1.push(10);
    q1.push(11);
    cout << q1.front() << endl;
    cout << q1.back() << endl;
    q1.pop();
    q1.push(14);
    q1.push(15);
    cout << q1.back() << endl;
    return 0;
}

