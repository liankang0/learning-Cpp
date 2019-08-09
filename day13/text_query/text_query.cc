#include <stdio.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <map>
#include <set>

using std::set;
using std::unordered_map;
using std::map;
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::stringstream;
using std::ifstream;
using std::ofstream;
//处理文本，把除了字母以外的所有字符转化为空格
int tranText(string fileName)
{
    //以读方式打开文件
    ifstream ifs;
    ifs.open(fileName.c_str());//string类型转化为char*
    if(!ifs)
    {
        cout << "ifstream open file error!" << endl;
        return -1;
    }

    //创建一个文件副本，接收转化后的文件
    std::fstream fs;
    string fileName_1 = fileName + "_1";
    fs.open(fileName_1.c_str(), std::ios::out);
    if(!fs)
    {
        cout << "fstream open file error!" << endl;
        return -1;
    }
    string line;
    char word;
    while(!ifs.eof())//到文件末尾返回true，否则返回false
    {
        getline(ifs,line);
        std::istringstream iss(line);
        while(!iss.eof())
        {
            iss.get(word);
            //不是字母
            if(word < 65 || word > 90 && word < 97 || word > 122)
            {
                word = 32;//置为空格
            }
            fs << word;
        }
        fs << endl;
    }
    ifs.close();
    fs.close();
    return 0;

}

class TextQuery
{
public:
    TextQuery()
    :_dict()
    ,_wordLine()
    ,_lines()
    {}

    int readFile(const string fileName);
    void query(const string& word);
    void printLineAndWordLine(const string& word);
private:
    unordered_map<int, string> _lines;
    map< string, set<int> > _wordLine;
    map<string, int> _dict;
};


int TextQuery::readFile(const string fileName)
{
    //以读方式打开文件
    ifstream ifs;
    ifs.open(fileName.c_str());//string类型转化为char*
    if(!ifs)
    {
        cout << "ifstream open file error!" << endl;
        return -1;
    }
    int lineNumber = 0;
    string line, word;
    while(!ifs.eof())//到文件末尾返回true，否则返回false
    {
        ++lineNumber;
        getline(ifs,line);
        _lines[lineNumber] = line;
        std::istringstream iss(line);
        while(!iss.eof())
        {
            iss>>word;
                _dict[word]++;
                _wordLine[word].insert(lineNumber);
        }
    }
    ifs.close();
    return 0;
}

void TextQuery::query(const string& word)
{   
    //使用find，查询不到时返回一个末尾迭代器，输出的值为随机值？？？这个怎么解决？？？
    //解决方法：判断返回的是否为end()迭代器
    //cout << word << " occurs " << _dict.find(word)->second << " times." << endl;
    //使用下标法查询，查不到时会改变内存中的_dict的内容，创建一个新的key，value为 '0',在这里不影响结果
    //，但是查询次数越多，内存中的_dict就会越大
    auto it = _dict.find(word);
    if(it == _dict.end())
    {
        cout << word << " occurs 0 times." << endl;
    }
    else
    {
    cout << word << " occurs " << it->second << " times." << endl;
    printLineAndWordLine(word);
    }
}

void TextQuery::printLineAndWordLine(const string& word)
{
    for(auto it : _wordLine[word])
    {
        cout << "     " << "(line" << it << ")    " << _lines[it] << endl;
    }
}

int main()
{
    string path;
    cout << "请输入文件路径：" << endl;
    cin >> path;
    tranText(path);
    string path_1 = path + "_1";
    //创建对象
    TextQuery textQuery;
    textQuery.readFile(path_1);
    string word;
    while(cout << "请输入查询的单词" << endl, cin >> word)
    {
        textQuery.query(word);
    }

    return 0;
}
