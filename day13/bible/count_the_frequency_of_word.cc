#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;

struct Word
{
    Word()
    :_str("")
    ,_count(0)
    {}

    string _str;
    int _count;

};

bool IsNumber(string str)
{

    stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d))
    {
        return false;
    }
    if(sin >> c)
    {
        return false;
    }

    return true;
}

int main()
{
    string path;
    cin >> path;

    ifstream ifs;
    ifs.open(path.c_str());
    if(!ifs)
    {
        cout << "ifstream open file error" << endl;
        return -1;
    }

    vector<Word> dictionary;

    string word;
    //输入流函数运算符默认以空格\换行符为分割符
    bool flag = false;
    while(ifs >> word)
    {
        flag = false;
        if(IsNumber(word))
        {
            continue;
        }
        for(auto& i:dictionary)
        {
            if(i._str == word)
            {
                i._count++;
                flag = true;
                break;
            }
        }
        if(!flag)
        {
            Word newWord;
            newWord._str = word;
            newWord._count = 1;
            dictionary.push_back(newWord);
        }
    }
    ifs.close();

    ofstream ofs("dictionary");
    if(!ofs)
    {
        cout << "ofstream open file error!" << endl;
        return -1;
    }
    for(auto& line : dictionary)
    {
        ofs << line._str << "   " << line._count << "\n";
    }
    ofs.close();


    return 0;
}

