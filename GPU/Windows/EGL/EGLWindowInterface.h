//
// EGLWindowInterface.h
//
// Library: GPU
// Package: Windows
// Module:  EGL
// 

#pragma once

#include <cstdint>
#include <string>
#include <utility>

#include "EGLCommon.h"

namespace Mmp
{

class EGLWindowInterface
{
public:
    using Version = std::pair<uint32_t /* major */, uint32_t /* minor */>;
    virtual ~EGLWindowInterface() = default;
public:
    /**
     * @brief   开启
     * @return  是否成功
     */
    virtual bool Open() = 0;
    /**
     * @brief   关闭
     * @return  是否成功
     */
    virtual bool Close() = 0;
    /**
     * @brief  获取 GPU 产商信息
     */
    virtual const std::string GetVendor() = 0;
    /**
     * @brief 获取 Client API 的类型
     * @sa    GLMode
     */
    virtual GLMode GetGLMode() = 0;
    /**
     * @brief  获取版本
     */
    virtual const Version GetVersion() = 0;
};

} // namespace Mmp