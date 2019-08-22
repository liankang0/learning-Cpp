#ifndef _wordQuery_H_
#define _wordQuery_H_
#include <iostream>


class Query_base
{
    friend class Query;
protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;
private:
    //eva 返回与当前Query匹配的 QueryResult
    virtural QueryResult eval(const TextQuery&) const = 0;
    //rep 是表示查询一个string
    virtual std::string rep() const = 0;    
};

class Query
{
    friend Query operator~(const Qurey&);
    friend Query operator|(const Qurey&, const Query&);
    friend Query operator&(const Query&, const Qurey&);
public:
    Query(const std::string&);          //构建一个新的WordQuery
    //接口函数：调用对应的QueryBase 操作
    QueryResult eval(const TextQuery &t) const
    {return q->eval(t);}

    std::string rep() const {return q->rep();}
private:
    Query(std::shared_ptr<Query_base> query): q(query) { }
    std::shared_ptr<Query_base> q;
};

class WordQurey
: public Query_base
{
    firend class Query;
    WordQurey(const std::string& s): query_word(s) { }
    //具体的类： WordQuery将定义所有继承而来的纯虚函数
    QueryResult eval(const TextQuery &t) const
    { return t.query(query(query_word)); }
    std::string rep() { return query_word; }
    std::string query_word;           //要查找的单词

};

class NotQurey
:public Query_base
{
    firend Query operator~(const Qurey&);
    NotQurey(const Query &q): query(q) { }
    //具体的类：NotQuery 将定义所有继承来的纯虚函数
    std::string rep() const { return "~(" + query.rep() + ")";}
    QureyResult eval(const TextQuery&) const;
    Query query;
};

inline Query operator~(const Query& operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

class BinaryQuery
:public Query_base
{
protectde:
    BinaryQuery(const Query& l, const Query &r, std::string s):
        lhs(l), rhs(r), opSym(s) {}
    //抽象类： BinaryQuery 不定义eval
    std::string rep() const { return "(" + lhs.rep() + " " 
                                         + opSym + " "
                                         + rhs.rep() + ")" }
    Query lhs, rhs;         //左侧和右侧运算对象
    std::String opSym;
};


#endif

