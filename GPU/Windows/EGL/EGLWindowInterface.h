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

/**
 * @brief EGL 窗口通用接口定义
 */
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
     * @brief        将 window 绑定到渲染线程
     * @param[in]    bind : true 为绑定, false 为解绑
     * @note         此接口只能在渲染线程调用 (也就是 OpenGL 接口调用的线程),
     *               具体原因见 eglspec.1.5.pdf - 3.7.3 Binding Contexts and Drawables
     *               eglMakeCurrent binds ctx to the current rendering thread and to the draw and read surfaces.
     *               (实际原因与 OpenGL C/S 架构设计有很大关系, ctx 实际上是 OpenGL 调用时的隐式参数)
     */
    virtual bool BindRenderThread(bool bind) = 0;
    /**
     * @brief   设置 surface 类型
     * @sa      GLSurfaceType
     * @note    默认为 GLSurfaceType::WINDOWS
     */
    virtual void SetSurfaceType(GLSurfaceType surfaceType) = 0;
    /**
     * @brief   获取 surface 类型
     * @sa      GLSurfaceType
     */
    virtual GLSurfaceType GetSurfaceType() = 0;
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