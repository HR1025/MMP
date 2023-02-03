#include "Logger.h"

#include <cassert>
#include <thread>

#include <Poco/Channel.h>
#include <Poco/Message.h>
#include <Poco/LoggingFactory.h>
#include <Poco/Instantiator.h>
#include <Poco/Thread.h>
#include <Poco/SingletonHolder.h>
#include <Poco/Timespan.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/ConsoleChannel.h>


namespace Poco
{
static Mmp::Logger::LogCallback gLogCallback;

class CustomChannel : public Channel
{
public:
    using Ptr = AutoPtr<CustomChannel>;
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
                break;
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

} // namespace Poco

namespace Mmp
{
static Poco::SingletonHolder<Logger> sh;

bool operator<(Logger::Level left, Logger::Level right)
{
    return static_cast<uint32_t>(left) < static_cast<uint32_t>(right);
}

bool operator>(Logger::Level left, Logger::Level right)
{
    return !(left < right);
}

bool operator<=(Logger::Level left, Logger::Level right)
{
    return (left < right) || (left == right);
}

bool operator>=(Logger::Level left, Logger::Level right)
{
    return (left > right) || (left == right);
}

static const std::string GetCurrentLogTime()
{
    return Poco::DateTimeFormatter::format(Poco::Timestamp(), "%Y-%m-%d %H:%M:%S", 8 /* 东八区 */);
}

static uint64_t GetTid()
{
    return Poco::Thread::currentOsTid();
}

static const std::string LevelToStr(Logger::Level level)
{
    std::string levelStr;
    switch (level)
    {
        case Logger::Level::TRACE:
            levelStr    = "TRACE";
            break;
        case Logger::Level::DEBUG:
            levelStr    = "DEBUG";
            break;
        case Logger::Level::INFO:
            levelStr    = "INFO ";
            break;
        case Logger::Level::WARN:
            levelStr    = "WARN ";
            break;
        case Logger::Level::ERROR:
            levelStr    = "ERROR";
            break;
        case Logger::Level::FATAL:
            levelStr    = "FATAL";
            break;
        default:
            assert(false);
            levelStr    = "INFO";
            break;
    }
    return levelStr;
}

static const Poco::Message::Priority LevelToPriority(Logger::Level level)
{
    Poco::Message::Priority priority;
    switch (level)
    {
        case Logger::Level::TRACE:
            priority = Poco::Message::Priority::PRIO_TRACE;
            break;
        case Logger::Level::DEBUG:
            priority = Poco::Message::Priority::PRIO_DEBUG;
            break;
        case Logger::Level::INFO:
            priority = Poco::Message::Priority::PRIO_INFORMATION;
            break;
        case Logger::Level::WARN:
            priority = Poco::Message::Priority::PRIO_WARNING;
            break;
        case Logger::Level::ERROR:
            priority = Poco::Message::Priority::PRIO_ERROR;
            break;
        case Logger::Level::FATAL:
            priority = Poco::Message::Priority::PRIO_FATAL;
            break;
        default:
            assert(false);
            priority = Poco::Message::Priority::PRIO_INFORMATION;
            break;
    }
    return priority;
}

void Logger::SetThreshold(Level threshold)
{
    _threshold = threshold;
}

Logger::Level Logger::GetThreshold()
{
    return _threshold;
}

Logger::Logger()
{
    _threshold = Level::INFO;
    // Hint : 默认赋值防止空指针崩溃
    Poco::gLogCallback = [](uint32_t line, const std::string& fileName, Level level, const std::string& module, uint32_t tid, uint32_t pid, const std::string msg) -> void
    {

    };
    Poco::LoggingFactory::defaultFactory().registerChannelClass("CustomChannel",  new Poco::Instantiator<Poco::CustomChannel, Poco::Channel>);
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
                _channels[Direction::CONSLOE]->setProperty("traceColor", "black");
                _channels[Direction::CONSLOE]->setProperty("informationColor", "blue");
                _channels[Direction::CONSLOE]->setProperty("warningColor", "brown");
                _channels[Direction::CONSLOE]->open();
                break;
            case Direction::FILE:
                assert(!_logFile.empty());
                _channels[Direction::FILE] = Poco::LoggingFactory::defaultFactory().createChannel("FileChannel");
                _channels[Direction::FILE]->setProperty("path", _logFile);
                _channels[Direction::FILE]->open();
                break;
            case Direction::CUSTOM:
                _channels[Direction::CUSTOM] = Poco::LoggingFactory::defaultFactory().createChannel("CustomChannel");
                _channels[Direction::CUSTOM]->open();
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

Logger& Logger::LoggerSingleton()
{
    return *sh.get();
}

void Logger::Log(uint32_t line, const std::string& fileName, Level level, const std::string& module, const std::string& msg)
{
    if (level < _threshold) return;

    auto GetFullMsg = [&](const std::string& msg) -> std::string
    {
        std::string fullMsg;
        if (!module.empty())
        {
            fullMsg = "[" + GetCurrentLogTime() + "][" + LevelToStr(level) + "][" + std::to_string(GetTid()) 
                                + "][" + module + "][" + fileName + ":" + std::to_string(line) + "] " + msg;
        }
        else
        {
            fullMsg = "[" + GetCurrentLogTime() + "][" + LevelToStr(level) + "][" + std::to_string(GetTid()) 
                                + "][" + fileName + ":" + std::to_string(line) + "] " + msg;     
        }
        return fullMsg;
    };

    Poco::Message::Priority priority = LevelToPriority(level);
    Poco::Message message(module, msg, priority, fileName.c_str(), line);
    message.setTid(GetTid());
    
    for(const auto& enbaledDirection : _enbaledDirections)
    {
        if (enbaledDirection.second)
        {
            if (enbaledDirection.first != Direction::CUSTOM)
            {
                Poco::Message fullMessage(module, "", priority, fileName.c_str(), line);
                fullMessage.setTid(GetTid());
                fullMessage.setText(GetFullMsg(msg));
                _channels[enbaledDirection.first]->log(fullMessage);
            }
            else
            {
                _channels[enbaledDirection.first]->log(message);
            }
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