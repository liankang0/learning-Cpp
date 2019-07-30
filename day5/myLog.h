#ifndef _MYLOG_H_
#define _MYLOG_H_

#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <string>
#include <sstream>

using std::cout;
using std::cin;
using std::string;
//using namespace log4cpp; //为了程序可读性好，下面都自己写
enum myPriority
{
    EMERG,
    FATAL,
    ALERT,
    CRIT,
    ERROR,
    WARN,
    NOTICE,
    INFO,
    DEBUG
};
class myLog
{
public:
    static myLog* getInstance();
    static void destory();
    void setPriority(myPriority priority);
    void fatal(const char* msg);
    void error(const char* msg);
    void warn(const char* msg);
    void info(const char* msg);
    void debug(const char* msg);

private:
    static myLog* _pLog;
    log4cpp::Category& rootCategory;
private:
    myLog();
    ~myLog();
};

string int2string(int lineNumber);
#define catMsg(msg) string(msg).append(" {fileName:")\
    .append(__FILE__).append(" functionName:")\
    .append(__func__).append(" lineNumber:")\
    .append(int2string(__LINE__)).append("}").c_str()
//单例类，只有一个对象
static myLog* log = myLog::getInstance();
#define logSetpriority(priority) log->setPriority(priority)
#define logError(msg) log->error(catMsg(msg))
#define logWarn(msg) log->warn(catMsg(msg))
#define logInfo(msg) log->info(catMsg(msg))
#define logDebug(msg) log->debug(catMsg(msg))
#define logFatal(msg) log->fatal(catMsg(msg))
#define logDestroy() myLog::destroy()

#endif
