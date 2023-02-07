#include "Utility.h"

#include <cassert>
#include <mutex>

#include "Common/Logger.h"
#include "Common/LogMessage.h"

namespace Mmp
{

static std::mutex isLoggerInitedMtx;
static bool isLoggerInited = false;

void InitLogger(bool isNeedConsle, bool isNeedFile, const std::string& logFilePath, Logger::Level level)
{
    std::lock_guard<std::mutex> lock(isLoggerInitedMtx);
    
    if (isLoggerInited) return;

    if (isNeedFile && logFilePath.empty()) assert(false);

    if (isNeedConsle)
    {
        Logger::LoggerSingleton().Enable(Mmp::Logger::Direction::CONSLOE);
    }
    if (isNeedFile)
    {
        Logger::LoggerSingleton().SetFilePath(logFilePath);
        Logger::LoggerSingleton().Enable(Mmp::Logger::Direction::FILE);
    }
    Logger::LoggerSingleton().SetThreshold(level);
    isLoggerInited = true;
}


} // namespace Mmp