#include "Utility.h"

#include <cassert>
#include <mutex>

#include "Common/LoggerInterface.h"
#include "Common/LogMessage.h"

namespace Mmp
{

static std::mutex isLoggerInitedMtx;
static bool isLoggerInited = false;

void InitLogger(bool isNeedConsle, bool isNeedFile, const std::string& logFilePath, LoggerInterface::Level level)
{
    std::lock_guard<std::mutex> lock(isLoggerInitedMtx);
    
    if (isLoggerInited) return;

    if (isNeedFile && logFilePath.empty()) assert(false);

    if (isNeedConsle)
    {
        LoggerInterface::LoggerSingleton()->Enable(Mmp::LoggerInterface::Direction::CONSLOE);
    }
    if (isNeedFile)
    {
        LoggerInterface::LoggerSingleton()->SetFilePath(logFilePath);
        LoggerInterface::LoggerSingleton()->Enable(Mmp::LoggerInterface::Direction::FILE);
    }
    LoggerInterface::LoggerSingleton()->SetThreshold(level);
    isLoggerInited = true;
}


} // namespace Mmp