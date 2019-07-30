#include "myLog.h"

#include <iostream>
myLog* myLog::_pLog = NULL;

myLog::myLog()
:rootCategory(log4cpp::Category::getRoot().getInstance("rootCategory"))
{
    //获取根Category，引用成员必须在成员初始化列表初始化
    try
    {
        log4cpp::PropertyConfigurator::configure("config");
    }
    catch(log4cpp::ConfigureFailure& f)
    {
        std::cerr << f.what() << '\n';
    }
    //根Category下添加子Category
}

myLog::~myLog()
{
    rootCategory.info("~myLog()");
    rootCategory.shutdown();
}

void myLog::destory()
{
    _pLog->rootCategory.info("myLog destory");
    delete _pLog;
    _pLog = NULL;
}

myLog* myLog::getInstance()
{
    if(NULL == _pLog)
    {
        _pLog = new myLog();
    }
    return _pLog;
}

//类对象的调用， 重新设置rootCategory的优先级
void myLog::setPriority(myPriority priority)
{
    switch(priority)
    {
        case FATAL:rootCategory.setPriority(log4cpp::Priority::FATAL); break;
        case ERROR:rootCategory.setPriority(log4cpp::Priority::ERROR);break;
        case WARN:rootCategory.setPriority(log4cpp::Priority::WARN);break;
        case INFO:rootCategory.setPriority(log4cpp::Priority::INFO);break;
        case DEBUG:rootCategory.setPriority(log4cpp::Priority::DEBUG);break;
        default:
                rootCategory.setPriority(log4cpp::Priority::DEBUG);break;
    }
}

void myLog::error(const char* msg)
{
    rootCategory.error(msg);
}

void myLog::warn(const char* msg)
{
    rootCategory.warn(msg);
}

void myLog::info(const char* msg)
{
    rootCategory.info(msg);
}

void myLog::fatal(const char* msg)
{
    rootCategory.fatal(msg);
}
void myLog::debug(const char* msg)
{
    rootCategory.debug(msg);
}
string int2string(int lineNumber)
{
    std::stringstream oss;
    oss << lineNumber;
    return oss.str();
}
