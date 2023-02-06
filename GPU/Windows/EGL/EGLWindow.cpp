#include "EGLWindow.h"

#include <cassert>

#include <Poco/StringTokenizer.h>

namespace Mmp
{

/**
 * @sa     es_spec_3.2.pdf - 3.3 EGL Queries [EGL_CLIENT_APIS]
 * @note   clientApis 实际上可能包含多个可选项以空格分割, 优先级设置为 OPENGL > OPENGL_ES > OPENVG
 */
GLMode EglClientApisToGLMode(const std::string& clientApis)
{
    if (clientApis.find("OpenGL") != std::string::npos)
    {
        return GLMode::OPENGL;
    }
    else if (clientApis.find("OpenGL_ES") != std::string::npos)
    {
        // Hint : 默认认为版本为 3, 初始化失败时考虑退滚至 2 ?
        return GLMode::OPENGL_ES3;
    }
    else if (clientApis.find("OpenVG") != std::string::npos)
    {
        return GLMode::OPENVG;
    }
    else
    {
        // FIXME : EGL 不应该会走到这里来
        assert(false);
        return GLMode::UNKNOWN;
    }
}

bool EGLWindow::Open()
{
    EGL_LOG_INFO << "Try Open EGL Window";
    
    _eglDisplay = OnOpenDisplay();

    if (eglInitialize(_eglDisplay, reinterpret_cast<EGLint *>(&_versionMajor), reinterpret_cast<EGLint *>(&_versionMinor)) == EGL_FALSE)
    {  
        eglTerminate(_eglDisplay);
        EGLint error = eglGetError();
        _eglDisplay = EGL_NO_DISPLAY;
        EGL_LOG_ERROR << "Unable to create EGL display, error is: " << EGLErrorToStr(error);
        return false;
    }

    std::string vendor = GetVendor();
    GLMode glMode = GetGLMode();

    EGL_LOG_INFO << "Print EGL baisc Info:";
    EGL_LOG_INFO << "-- EGL vendor is: " << vendor;
    EGL_LOG_INFO << "-- EGL version is: " << _versionMajor << "." << _versionMinor;
    EGL_LOG_INFO << "-- EGL Client API is: " << glMode;
    {
        // Hint : EGL extension 不做保存,仅仅打印出来用于跟踪 EGL 的特性 (例如是否支持 surface less render)
        std::string eglExtensions = std::string(eglQueryString(_eglDisplay, EGL_EXTENSIONS));
        auto eglEtension = Poco::StringTokenizer(eglExtensions, " ", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
        size_t eglExtensionNum = eglEtension.count();
        EGL_LOG_INFO << "-- EGL extensions are shown below:";
        for (size_t i=0; i<eglExtensionNum; i++)
        {
            EGL_LOG_INFO << "  -- (" << i+1 << ") " << eglEtension[i];
        }
    }

    EGL_LOG_INFO << "Open EGL Window Successfully";
    return true;
}

bool EGLWindow::Close()
{
    EGL_LOG_INFO << "Try Close EGL Window";
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
        Reset();
    }
    EGL_LOG_INFO << "Close EGL Window Successfully";
    return true;
}

const std::string EGLWindow::GetVendor()
{
    assert(EGL_NO_DISPLAY != _eglDisplay);
    if (!_vendor.empty()) return _vendor;
    _vendor = std::string(eglQueryString(_eglDisplay, EGL_VENDOR));
    return _vendor;
}

GLMode EGLWindow::GetGLMode()
{
    assert(EGL_NO_DISPLAY != _eglDisplay);
    if (_glMode == GLMode::UNKNOWN)
    {
        _glMode = EglClientApisToGLMode(std::string(eglQueryString(_eglDisplay, EGL_CLIENT_APIS)));
    }
    return _glMode;
}

const EGLWindowInterface::Version EGLWindow::GetVersion()
{
    assert(EGL_NO_DISPLAY != _eglDisplay);
    return {_versionMajor, _versionMinor};
}

void EGLWindow::Reset()
{
    _eglDisplay   = EGL_NO_DISPLAY;
    _eglSurface   = EGL_NO_SURFACE;
    _eglContext   = EGL_NO_CONTEXT;
    _glMode       = GLMode::UNKNOWN;
    _versionMajor = 0;
    _versionMinor = 0;
    _eglConfig    = nullptr;
}

EGLWindow::EGLWindow()
{
    Reset();
}

std::vector<EGLConfig> EGLWindow::GetAllEGLConfigs()
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
