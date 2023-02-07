//
// Utility.h
//
// Library: Common
// Package: Utility
// Module:  Utility
// 

#pragma once

#include "Common/Logger.h"

namespace Mmp
{

/**
 * @brief       初始化日志器
 * @param[in]   isNeedConsle : 是否需要控制台输出
 * @param[in]   isNeedFile   : 是否需要输出到文件
 * @param[in]   logFilePath  : 日志名
 * @param[in]   level        : 日志等级
 * @note        1 - logFilePath 仅当 isNeedFile 为 true 时生效, 且 isNeedFile 为 true 时 logFilePath 需要是一个合法路径
 *              2 - 可重入,但是仅第一次配置有效
 */
void InitLogger(bool isNeedConsle = true, bool isNeedFile = false, const std::string& logFilePath = "", Logger::Level level = Logger::Level::DEBUG);

};