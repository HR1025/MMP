//
// EGLWindowFactory.h
//
// Library: GPU
// Package: Windows
// Module:  EGL
// 

#pragma once
#include <mutex>

#include "Common/Instantiator.h"
#include "Common/DynamicFactory.h"
#include "EGLWindowInterface.h"

namespace Mmp
{

/**
 * @brief EGL 窗口工厂
 */
class EGLWindowFactory
{
public:
    using EGLWindowInstantiator = AbstractInstantiator<EGLWindowInterface>;
public:
    EGLWindowFactory();
    ~EGLWindowFactory();
    /**
     * @brief      注册 EGL 窗口注册器到工厂
     * @param[in]  className
     * @param[in]  instantiator
     * @note       EGLWindowInstantiator 需通过 new 的方式进行创建
     */
    void RegisterEGLWindowClass(const std::string& className, EGLWindowInstantiator* instantiator);
    /**
     * @brief 创建 EGL 窗口
     * @note  预注册 EGL 窗口创建器
     *        - EGLWindowDefault
     */
    std::shared_ptr<EGLWindowInterface> CreateEGLWindow(const std::string& className);
    /**
     * @brief 获取 EGL 窗口工厂默认单例
     */
    static EGLWindowFactory& DefaultFactory();
private:
    void RegisterBuiltins();
private:
    std::mutex _mutex;
    DynamicFactory<EGLWindowInterface> _eglWindowFactory;
};

} // namespace Mmp