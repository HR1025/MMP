#include "EGLWindow.h"

#include <cassert>

namespace Mmp
{

bool EGLWindow::Open()
{
    EGL_LOG_INFO << "Try Open EGL Window";
    
    OnOpenDisplay();

    if (eglInitialize(_eglDisplay, &_versionMajor, &_versionMinor) == EGL_NO_DISPLAY)
    {  
        eglTerminate(_eglDisplay);
        EGLint error = eglGetError();
        _eglDisplay = EGL_NO_DISPLAY;
        EGL_LOG_ERROR << "Unable to create EGL display, error is: " << EGLErrorToStr(error);
        return false;
    }

    EGL_LOG_INFO << "Open EGL Window Successfully";
}

bool EGLWindow::Close()
{
    EGL_LOG_INFO << "Try Close EGL Window";
    _eglConfig = EGL_BAD_CONFIG;
    if (_eglDisplay != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(_eglDisplay, NULL, NULL, EGL_NO_CONTEXT);
        if (_eglContext)
        {
            eglDestroyContext(_eglDisplay, _eglContext);
        }
        if (_eglSurface)
        {
            eglDestroySurface(_eglDisplay, _eglSurface);
        }
        _eglDisplay = EGL_NO_DISPLAY;
        _eglContext = EGL_NO_CONTEXT;
        _eglSurface = EGL_NO_SURFACE;
    }
    EGL_LOG_INFO << "Close EGL Window Successfully";
}

void EGLWindow::SwapInterval(int interval)
{
    EGL_LOG_INFO << "SwapInterval, interval is: " << interval;
    eglSwapInterval(_eglDisplay, interval);
}

const std::string EGLWindow::GetVendor()
{
    if (!_vendor.empty()) return _vendor;

    _vendor = std::string(eglQueryString(_eglDisplay, EGL_VENDOR));
    EGL_LOG_INFO << "GetVendor, vendor is: " << _vendor;
}

const EGLWindowInterface::Version EGLWindow::GetVersion()
{
    return {_versionMajor, _versionMinor};
}

EGLWindow::EGLWindow()
{
    _eglDisplay   = EGL_NO_DISPLAY;
    _eglSurface   = EGL_NO_SURFACE;
    _eglContext   = EGL_NO_CONTEXT;
    _versionMajor = 0;
    _versionMinor = 0;
}

std::vector<EGLConfig> EGLWindow::GetEGLConfigs()
{
    EGLint numConfigs;
    EGLBoolean result;
    std::vector<EGLConfig>  eglChonfigs;

    EGL_LOG_INFO << "Try Get All EGL Configs";

    result = eglGetConfigs(_eglDisplay, nullptr, 0, &numConfigs);
    if (result != EGL_TRUE || numConfigs)
    {
        EGL_LOG_ERROR << "eglGetConfigs fail, result is:" << EGLErrorToStr(result) << ", egl configs num is: " << numConfigs;
        assert(false);
        return eglChonfigs;
    }
    
    eglChonfigs.resize(numConfigs);
    result = eglGetConfigs(_eglDisplay, &eglChonfigs[0], numConfigs, &numConfigs);
    if (result != EGL_TRUE || numConfigs)
    {
        EGL_LOG_ERROR << "eglGetConfigs fail, result is:" << EGLErrorToStr(result) << ", egl configs num is: " << numConfigs;
        assert(false);
        return eglChonfigs;
    }

    EGL_LOG_INFO << "GetEGLConfigs, total EGL config nums is: " << numConfigs;
    
    return eglChonfigs;
}

} // namespace Mmp
