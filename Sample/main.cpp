#include <memory>
#include <string>

#include "Common/Logger.h"
#include "Common/LogMessage.h"

int main()
{
    Mmp::Logger::LoggerSingleton().SetFilePath("./smaple.log");
    Mmp::Logger::LoggerSingleton().Enable(Mmp::Logger::Direction::CONSLOE);
    Mmp::Logger::LoggerSingleton().Enable(Mmp::Logger::Direction::FILE);

    MMP_LOG_TRACE("Sample") << "Hello World";
    MMP_LOG_DEBUG("Sample") << "Hello World";
    MMP_LOG_INFO("Sample") << "Hello World";
    MMP_LOG_WARN("Sample") << "Hello World";
    MMP_LOG_ERROR("Sample") << "Hello World";
    MMP_LOG_FATAL("Sample") << "Hello World";

    return 0;
}