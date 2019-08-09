
// coding:utf-8

// **********************************************************
// * Author        : liankang
// * Email         : 349915905@qq.com
// * Create time   : 2019-08-07 23:21
// * Filename      : word_ladder.cc
// * Description   : 
// **********************************************************
//总结： 1.pair读取方式 pair<int, int> p = make_pair(1, 2);
//                   int ret = std::get<0>(p);   ret的值应该为1;                        
//      2.make_pair(key, value)  
//              make_pair<key, value>//error
//      3.map和undered_map 都可以用迭代器顺序访问auto it = map.begin();  ......
//      4.replace 可以替换字符串中的某一个字符，还可以替换容器的某一个元素。。。。。。
#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <deque>
#include <vector>
#include <utility>
#include <array>

using std::array;
using std::pair;
using std::vector;
using std::deque;
using std::set;
using std::unordered_map;
using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::make_pair;

class Solution {
public:
    
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) 
    {
         _curWord = beginWord;
        _wordSize = beginWord.length();
        tranWordList(wordList, beginWord);
        int index = 0;
        int layer = 0;
        _tranDeque.push_back(make_pair(_curWord, layer));
        
        while(index < _tranDeque.size())//遍历的下标大于等于 _tranDeque。size() 结束
        {    //如果curword的层数不小于layer，就要++layer
            if(_tranDeque[index].second >= layer)
            {
                ++layer;
            }
            _curWord = std::get<0>(_tranDeque[index++]);//遍历完一个单词，遍历下一个单词
            for(int i = 0; i < _wordSize; ++i)//遍历_curWord的所有派生词
            {
                //遍历wordList所有词
                for(int j = 0; j < wordList.size(); ++j)
                {   //判断有没有相同的派生词，如果有,就把原词放入deque中
                    for(int k = 0; k < _wordSize; ++k)
                    {
                        if( _tranWordList[_curWord][i] == _tranWordList[wordList[j]][k])
                        {   
                            //判断是否已经存在这个deque中
                            if(!existDeque(wordList[j]))
                            {   
                                _tranDeque.push_back(make_pair(wordList[j], layer));
                                //当找到要插入的相邻的单词就是endword时返回层数
                                if(wordList[j] == endWord)
                                {
                                    return layer + 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        return 0;
    }
    bool existDeque(const string&);
    void tranWordList(vector<string>& wordList, string& beginWord);
private:
    unordered_map<string, vector<string>> _tranWordList;
    deque<pair<string, int>> _tranDeque;
    int _wordSize;
    string _curWord;
    
};

bool Solution::existDeque(const string& curWord)
{
    for(int i = 0; i < _tranDeque.size(); ++i)
    {
        if(std::get<0>(_tranDeque[i]) == curWord)
        {
            return true;
        }
    } 
    return false;
}
void Solution::tranWordList(vector<string>& wordList, string& beginWord)
{
    
    for(int i = 0; i < wordList.size(); i++)
    {
        
        for(int j = 0; j < wordList[i].length(); j++)
        {
            string tmp = wordList[i];
            tmp.replace(j , 1, "*");
            _tranWordList[wordList[i]].push_back(tmp);
        }
    }
    for(int j = 0; j < beginWord.length(); j++)
    {
        string tmp = beginWord;
        tmp.replace(j , 1, "*");
        _tranWordList[beginWord].push_back(tmp);
    }
}

int main()
{
    vector<string> wordList = {{"hot"},{"dot"},{"dog"},{"lot"},{"log"},{"cog"}};
    string beginWord = "hit";
    string endWord = "cog";
    Solution solution;
    int ret = solution.ladderLength(beginWord, endWord, wordList);
    cout << "ret = " << ret << endl;
    return 0;
}

