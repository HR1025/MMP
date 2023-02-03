#include "Logger.h"

#include <cassert>

#include <Poco/Channel.h>
#include <Poco/Message.h>
#include <Poco/LoggingFactory.h>
#include <Poco/Instantiator.h>

namespace Poco
{
static Mmp::Logger::LogCallback gLogCallback;

class CustomChannel : public Channel
{
public:
    void log(const Message& msg) override
    {
        Mmp::Logger::Level level;
        switch (msg.getPriority())
        {
            case Message::Priority::PRIO_FATAL:
                level = Mmp::Logger::Level::FATAL;
                break;
            case Message::Priority::PRIO_ERROR:
                level = Mmp::Logger::Level::ERROR;
                break;
            case Message::Priority::PRIO_WARNING:
                level = Mmp::Logger::Level::WARN;
                break;
            case Message::Priority::PRIO_INFORMATION:
                level = Mmp::Logger::Level::INFO;
                break;
            case Message::Priority::PRIO_DEBUG:
                level = Mmp::Logger::Level::DEBUG;
                break;
            case Message::Priority::PRIO_TRACE:
                level = Mmp::Logger::Level::TRACE;
            default:
                assert(false);
                level = Mmp::Logger::Level::INFO;
                break;
        }
        gLogCallback(msg.getSourceLine(), msg.getSourceFile(), level, msg.getSource(),
                    msg.getTid(), msg.getTid(), msg.getText()
        );
    }    
};

class CustomChannelInstantiator : public Poco::LoggingFactory::ChannelInstantiator
{
    CustomChannel* createInstance() const override
    {
        return new CustomChannel();
    }
};

} // namespace Poco

namespace Mmp
{
Logger::Logger()
{
    // Hint : 默认赋值防止空指针崩溃
    Poco::gLogCallback = [](uint32_t line, const std::string& fileName, Level level, const std::string& module, uint32_t tid, uint32_t pid, const std::string msg) -> void
    {

    };
    Poco::LoggingFactory::defaultFactory().registerChannelClass("CustomChannel", new Poco::CustomChannelInstantiator());
}
}

namespace Mmp
{
void Logger::Enable(Direction direction)
{
    if (_enbaledDirections.count(direction) == 0 || _enbaledDirections[direction] == false)
    {
        switch (direction)
        {
            case Direction::CONSLOE:
                _channels[Direction::CONSLOE] = Poco::LoggingFactory::defaultFactory().createChannel("ColorConsoleChannel");
                _channels[Direction::CONSLOE]->open();
                break;
            case Direction::FILE:
                assert(!_logFile.empty());
                _channels[Direction::FILE] = Poco::LoggingFactory::defaultFactory().createChannel("FileChannel");
                _channels[Direction::FILE]->setProperty("path", _logFile);
                _channels[Direction::FILE]->open();
                break;
            case Direction::CUSTOM:
                _channels[Direction::FILE] = Poco::LoggingFactory::defaultFactory().createChannel("CustomChannel");
                _channels[Direction::FILE]->open();
                break;
            default:
                break;
        }
        _enbaledDirections[direction] = true;
    }
}

void Logger::Disable(Direction direction)
{
    if (_enbaledDirections.count(direction) == 0 || _enbaledDirections[direction] == false)
    {
        return;
    }
    _channels[direction]->close();
    _channels[direction] = nullptr;
    _enbaledDirections[direction] = false;
}

void Logger::Log(uint32_t line, const std::string& fileName, Level level, const std::string& module, const std::string& msg)
{
    Poco::Message::Priority priority;
    switch (level)
    {
        case Level::TRACE:
            priority = Poco::Message::Priority::PRIO_TRACE;
            break;
        case Level::DEBUG:
            priority = Poco::Message::Priority::PRIO_DEBUG;
            break;
        case Level::INFO:
            priority = Poco::Message::Priority::PRIO_INFORMATION;
            break;
        case Level::WARN:
            priority = Poco::Message::Priority::PRIO_WARNING;
            break;
        case Level::ERROR:
            priority = Poco::Message::Priority::PRIO_ERROR;
            break;
        case Level::FATAL:
            priority = Poco::Message::Priority::PRIO_FATAL;
            break;
        default:
            assert(false);
            priority = Poco::Message::Priority::PRIO_INFORMATION;
            break;
    }
    Poco::Message message(module, msg, priority, fileName.c_str(), line);


    for(const auto& enbaledDirection : _enbaledDirections)
    {
        if (enbaledDirection.second)
        {
            _channels[enbaledDirection.first]->log(message);
        }
    }
}

void Logger::SetFilePath(const std::string& filePath)
{
    _logFile = filePath;
}

void Logger::SetCallback(const LogCallback& logCallback)
{
    Poco::gLogCallback = logCallback;
}

} // namespace Mmp