//
// EGLWindow.h
//
// Library: GPU
// Package: Windows
// Module:  EGL
// 

#pragma once
#include <string>
#include <vector>

#include <EGL/egl.h>

#include "EGLWindowInterface.h"

namespace Mmp
{

class EGLWindow : public EGLWindowInterface
{
public:
    bool Open() override;
    bool Close() override;
    const std::string GetVendor() override; 
    const Version GetVersion() override;
public:
    EGLWindow();
private:
    /**
     * @brief 获取所有 EGL 可选配置
     * @sa    OnChooseEGLConfig
     */
    std::vector<EGLConfig> GetAllEGLConfigs();
private: /* EGLWindow Event */
    /**
     * @brief 获取 EGLDisplay
     */
    virtual EGLDisplay OnOpenDisplay() = 0;
    /**
     * @brief 选择 EGLConfig
     * @note  一个显示器可能支持多种输出配置,这些配置放置在 EGLConfig 中,
     *        派生类需要从中选取一个自己认为最合适的配置
     */
    virtual EGLConfig  OnChooseEGLConfig() = 0; 
private:
    EGLDisplay    _eglDisplay;
    EGLConfig     _eglConfig;
    EGLSurface    _eglSurface;
    EGLContext    _eglContext;
    std::string   _vendor;
    uint32_t      _versionMajor;
    uint32_t      _versionMinor;
};

} // namespace Mmp 