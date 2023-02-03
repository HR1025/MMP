#include "LogMessage.h"

#include <Poco/Path.h>

namespace Mmp
{

LogMessage::LogMessage(Logger::Level level, const std::string& fileName, uint32_t line, const std::string& module)
{
    _level    = level;
    _fileName = Poco::Path(fileName).getFileName();
    _line     = line;
    _module   = module;
}

LogMessage::~LogMessage()
{
    Logger::LoggerSingleton().Log(_line, _fileName, _level, _module, _ss.str());
}

} // namespace Mmp