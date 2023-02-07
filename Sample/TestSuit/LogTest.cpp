#include "LogTest.h"

#include <iostream>
#include <string>

#include "Common/LoggerInterface.h"
#include "Common/LogMessage.h"

namespace Mmp
{
void LogTest()
{
    auto customLog = [](uint32_t line, const std::string& fileName, LoggerInterface::Level level, const std::string& module, uint64_t tid, uint64_t pid, const std::string msg) -> void
    {
        std::cout << "custom log, line is: " << line << ", filename is: %s" << ", level is: " << static_cast<uint32_t>(level)
                  << ", module is: " << module << ", tid is: " << tid << ", msg is: " << msg << std::endl;
    };

    LoggerInterface::LoggerSingleton()->SetFilePath("./smaple.log");
    LoggerInterface::LoggerSingleton()->SetCallback(customLog);
    LoggerInterface::LoggerSingleton()->Enable(Mmp::LoggerInterface::Direction::CONSLOE);
    LoggerInterface::LoggerSingleton()->Enable(Mmp::LoggerInterface::Direction::FILE);
    LoggerInterface::LoggerSingleton()->Enable(Mmp::LoggerInterface::Direction::CUSTOM);

    // 通用日志输出
    MMP_LOG_TRACE << "Hello World";
    MMP_LOG_DEBUG << "Hello World";
    MMP_LOG_INFO  << "Hello World";
    MMP_LOG_WARN  << "Hello World";
    MMP_LOG_ERROR << "Hello World";
    MMP_LOG_FATAL << "Hello World";
    MMP_LOG_INFO;

    // 模块日志输出
    MMP_MLOG_TRACE("Common") << "Hello World";
    MMP_MLOG_DEBUG("Common") << "Hello World";
    MMP_MLOG_INFO("Common")  << "Hello World";
    MMP_MLOG_WARN("Common")  << "Hello World";
    MMP_MLOG_ERROR("Common") << "Hello World";
    MMP_MLOG_FATAL("Common") << "Hello World";
    MMP_MLOG_FATAL("Common");

    // 修改日志等级阈值
    Mmp::LoggerInterface::LoggerSingleton()->SetThreshold(Mmp::LoggerInterface::Level::TRACE);
    MMP_LOG_TRACE << "Hello World";
    MMP_LOG_DEBUG << "Hello World";
    MMP_LOG_INFO  << "Hello World";
    MMP_LOG_WARN  << "Hello World";
    MMP_LOG_ERROR << "Hello World";
    MMP_LOG_FATAL << "Hello World";
    MMP_LOG_INFO;
}
} // namespace Mmp

