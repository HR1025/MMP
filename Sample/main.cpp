#include <memory>
#include <string>

#include "Common/Logger.h"
#include "Common/LogMessage.h"

int main()
{
    Mmp::Logger::LoggerSingleton().SetFilePath("./smaple.log");
    Mmp::Logger::LoggerSingleton().Enable(Mmp::Logger::Direction::CONSLOE);
    Mmp::Logger::LoggerSingleton().Enable(Mmp::Logger::Direction::FILE);

    MMP_LOG_TRACE << "Hello World";
    MMP_LOG_DEBUG << "Hello World";
    MMP_LOG_INFO << "Hello World";
    MMP_LOG_WARN << "Hello World";
    MMP_LOG_ERROR << "Hello World";
    MMP_LOG_FATAL << "Hello World";

    return 0;
}