//
// Logger.h
//
// Library: Common
// Package: Log
// Module:  Logger
// 
#pragma once

#include <cstdint>
#include <string>
#include <map>
#include <functional>

#include <Poco/Channel.h>

namespace Mmp
{
/**
 * @brief    日志器
 * @note     非线程安全
 */
class Logger final
{
public:
    /**
     * @brief 日志传输方向
     */
    enum class Direction
    {
        CONSLOE,
        FILE,
        CUSTOM
    };
    /**
     * @brief 日志等级
     * @note  FATAL 在某些情况下会调用 assert 捕获
     */
    enum class Level
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };
    /**
     * @brief  日志回调
     * @param  line      : 行
     * @param  fileName  : 文件名
     * @param  module    : 模块标识
     * @param  tid       : 线程号
     * @param  pid       : 进程号
     * @param  msg       : 日志信息
     */
    using LogCallback = std::function<void(uint32_t line, const std::string& fileName, Level level, const std::string& module, uint64_t tid, uint64_t pid, const std::string msg)>;
public:
    Logger();
    /**
     * @brief 使能
     */
    void Enable(Direction direction);
    /**
     * @brief 关闭
     */
    void Disable(Direction direction);
    /**
     * @brief     日志输出
     * @param[in] line
     * @param[in] fileName
     * @param[in] level
     * @param[in] module
     * @param[in] msg  
     * @sa        LogCallback
     */
    void Log(uint32_t line, const std::string& fileName, Level level, const std::string& module, const std::string& msg);
    /**
     * @brief       设置日志文件路径
     * @param[in]   filePath
     * @note        针对于 Direction::FILE
     */
    void SetFilePath(const std::string& filePath);
    /**
     * @brief       设置日志回调
     * @param[in]   logCallback
     * @note        针对于 Direction::CUSTOM
     */
    void SetCallback(const LogCallback& logCallback);
    /**
     * @brief 单例获取
     */
    static Logger& LoggerSingleton();
private:
    std::map<Direction, bool /* isEnabled */>  _enbaledDirections;
    std::map<Direction, Poco::Channel::Ptr>    _channels;
    std::string                                _logFile;
    LogCallback                                _LogCallback;
};

} // namespace Mmp