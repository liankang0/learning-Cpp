#include "myLog.h"

#include <iostream>
myLog* myLog::_pLog = NULL;

myLog::myLog()
:rootCategory(log4cpp::Category::getRoot().getInstance("rootCategory"))
{
    //获取根Category，引用成员必须在成员初始化列表初始化
    
    //根Category下添加子Category
    log4cpp::OstreamAppender* osAppender = new log4cpp::OstreamAppender("osAppender", &cout);
    log4cpp::PatternLayout* pLayout1 = new log4cpp::PatternLayout();
    pLayout1->setConversionPattern("%d: %p %c %x: %m%n");
    osAppender->setLayout(pLayout1);
    rootCategory.addAppender(osAppender);
    rootCategory.setPriority(log4cpp::Priority::DEBUG);

    //log文件会一直记录，不采用回卷
    log4cpp::FileAppender* fileAppender = new log4cpp::FileAppender("fileAppender", "log");
    log4cpp::PatternLayout* pLayout2 = new log4cpp::PatternLayout();
    pLayout2->setConversionPattern("%d: %p %c %x: %m%n");
    fileAppender->setLayout(pLayout2);
    rootCategory.addAppender(fileAppender);
    rootCategory.setPriority(log4cpp::Priority::DEBUG);

    //设置回卷日志记录方式
    log4cpp::FileAppender* rollingfileAppender = new log4cpp::RollingFileAppender("rollingfileappender", "logrolling.log", 5*1024, 5);
    log4cpp::PatternLayout* pLayout3 = new log4cpp::PatternLayout();
    pLayout3->setConversionPattern("%d: %p %c %x: %m%n");
    rollingfileAppender->setLayout(pLayout3);
    rootCategory.addAppender(rollingfileAppender);
    rootCategory.setPriority(log4cpp::Priority::DEBUG);
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
