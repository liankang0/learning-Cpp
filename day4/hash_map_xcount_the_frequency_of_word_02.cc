#include <stdio.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::stringstream;
using std::ifstream;
using std::ofstream;

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
    //定义map
    std::map<string, int> dic;

    string path;
    cout << "请输入文件路径：" << endl;
    cin >> path;
    //以读方式打开文件
    ifstream ifs;//string类型转化为char*
    ifs.open(path.c_str());
    if(!ifs)
    {
        cout << "ofstream open file error!" << endl;
        return -1;
    }

    //读取字符串，使用get(char*, size_t, char),这样可以以任意字符分割的数据流
    //输入流运算符只能以默认的空格，换行，tap为分割符
    //这两种读取方式都会丢弃分割符
    string line, word;
    while(!ifs.eof())//到文件末尾返回true，否则返回false
    {
        getline(ifs,line);
        std::istringstream iss(line);
        while(!iss.eof())
        {
            iss>>word;
            if(!IsNumber(word))
            {
                dic[word]++;
            }
        }
    }
    ifs.close();

    ofstream ofs("dictionary");
    if(!ofs)
    {
        cout << "ofstream open file error!" << endl;
        return -1;
    }
    ofs << "total " << dic.size() << "words" << endl;
    for(auto& line : dic)
    {
        ofs << line.first << "     " << line.second << endl;
    }

    return 0;
}
