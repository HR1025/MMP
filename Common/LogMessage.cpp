#include "LogMessage.h"

#include <Poco/Path.h>

namespace Mmp
{

LogMessage::LogMessage(Logger::Level level, const std::string& fileName, uint32_t line, const std::string& module)
{
    _level    = level;
    if (_level >= Logger::LoggerSingleton().GetThreshold())
    {
        _fileName = Poco::Path(fileName).getFileName();
        _line     = line;
        _module   = module;
    }

}

LogMessage::~LogMessage()
{
    if (_level >= Logger::LoggerSingleton().GetThreshold())
    {
        Logger::LoggerSingleton().Log(_line, _fileName, _level, _module, _ss.str());
    }
}

} // namespace Mmp