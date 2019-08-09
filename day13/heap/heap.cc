
// coding:utf-8

// **********************************************************
// * Author        : liankang
// * Email         : 349915905@qq.com
// * Create time   : 2019-08-07 15:58
// * Filename      : heap.cc
// * Description   : 
// **********************************************************
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

namespace mySort
{
template <typename T, typename Compare = std::less<T> >

template <typename T, typename Compare = std::less<T> >
void headSort(T* array, Compare cmp)
{
    int i;
    for(i = _vect.size()/2 -1; i >= 0; i --)
    {
        heapAdjust(i);
    }
    swap(_vect[0], _vect[_vect.size() -1]);
    for(i = _vect.size() -1; i > 1; i--)
    {
        heapAdjust(0);
        swap(_vect[0], _vect[i -1]);
    }
}

template <typename T, typename Compare = std::less<T> >
void HeapSort<T, Compare>::heapAdjust(int adjustPos)
{
    int dad = adjustPos;
    int son = dad * 2 + 1;
    while(son < _vect.size())
    {
        if(son + 1 < _vect.size() && Compare(_vect[son], _vect[son + 1]) < 0)
        {
            son++;
        }
        if(Compare(_vect[dad], _vect[son]) < 0)
        {
            swap(_vect[dad], _vect[son]);
            dad = son;
            son = dad * 2 + 1;
        }
        else
        {
            break;
        }

    }
}
}//namespace mySort
