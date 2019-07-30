#include "myLog.h"
using std::endl;
int main()
{
    std::cout << "Hello world" << std::endl;
    cout << "hello,world"<<endl;

    logInfo("Message");    //或者   
    logError("Message");
    logWarn("Message");
    logDebug("Message");
    return 0;
}

