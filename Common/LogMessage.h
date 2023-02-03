//
// Logger.h
//
// Library: Common
// Package: Log
// Module:  LogMessage
// 

#pragma once

#include <cstdint>
#include <memory>
#include <sstream>
#include <string>

#include "Logger.h"

namespace Mmp
{

/**
 * @brief 日志信息
 * 
 */
class LogMessage final
{
public:
    LogMessage(Logger::Level level, const std::string& fileName, uint32_t line, const std::string& module);
    ~LogMessage();
public:
    template<typename T>
    LogMessage& operator<<(T t)
    {
        _ss << t;
        return *this;
    }
private:
    Logger::Level                    _level;
    std::string                      _fileName;
    uint32_t                         _line;
    std::string                      _module;
    std::stringstream                _ss;
};
} // namespace Mmp

#define MMP_LOG_TRACE(moudle)    Mmp::LogMessage(Mmp::Logger::Level::TRACE, __FILE__, __LINE__, moudle)
#define MMP_LOG_DEBUG(moudle)    Mmp::LogMessage(Mmp::Logger::Level::DEBUG, __FILE__, __LINE__, moudle)
#define MMP_LOG_INFO(moudle)     Mmp::LogMessage(Mmp::Logger::Level::INFO, __FILE__, __LINE__, moudle)
#define MMP_LOG_WARN(moudle)     Mmp::LogMessage(Mmp::Logger::Level::WARN, __FILE__, __LINE__, moudle)
#define MMP_LOG_ERROR(moudle)    Mmp::LogMessage(Mmp::Logger::Level::ERROR, __FILE__, __LINE__, moudle)
#define MMP_LOG_FATAL(moudle)    Mmp::LogMessage(Mmp::Logger::Level::FATAL, __FILE__, __LINE__, moudle)