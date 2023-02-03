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
 */
class LogMessage final
{
public:
    /**
     * @param[in]  level    : 日志等级
     * @param[in]  fileName : 文件名 (通常指的是 __FILE__)
     * @param[in]  line     : 文件行 (通常指的是 __LINE__)
     * @param[in]  module   : 归属模块 (非必填)
     */
    LogMessage(Logger::Level level, const std::string& fileName, uint32_t line, const std::string& module = "");
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

#define MMP_LOG_TRACE    Mmp::LogMessage(Mmp::Logger::Level::TRACE, __FILE__, __LINE__)
#define MMP_LOG_DEBUG    Mmp::LogMessage(Mmp::Logger::Level::DEBUG, __FILE__, __LINE__)
#define MMP_LOG_INFO     Mmp::LogMessage(Mmp::Logger::Level::INFO, __FILE__, __LINE__)
#define MMP_LOG_WARN     Mmp::LogMessage(Mmp::Logger::Level::WARN, __FILE__, __LINE__)
#define MMP_LOG_ERROR    Mmp::LogMessage(Mmp::Logger::Level::ERROR, __FILE__, __LINE__)
#define MMP_LOG_FATAL    Mmp::LogMessage(Mmp::Logger::Level::FATAL, __FILE__, __LINE__)

#define MMP_MLOG_TRACE(moudle)    Mmp::LogMessage(Mmp::Logger::Level::TRACE, __FILE__, __LINE__, moudle)
#define MMP_MLOG_DEBUG(moudle)    Mmp::LogMessage(Mmp::Logger::Level::DEBUG, __FILE__, __LINE__, moudle)
#define MMP_MLOG_INFO(moudle)     Mmp::LogMessage(Mmp::Logger::Level::INFO, __FILE__, __LINE__, moudle)
#define MMP_MLOG_WARN(moudle)     Mmp::LogMessage(Mmp::Logger::Level::WARN, __FILE__, __LINE__, moudle)
#define MMP_MLOG_ERROR(moudle)    Mmp::LogMessage(Mmp::Logger::Level::ERROR, __FILE__, __LINE__, moudle)
#define MMP_MLOG_FATAL(moudle)    Mmp::LogMessage(Mmp::Logger::Level::FATAL, __FILE__, __LINE__, moudle)