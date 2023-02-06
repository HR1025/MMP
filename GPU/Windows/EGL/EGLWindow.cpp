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
        // Hint : 默认认为版本为 3, 之后根据选择的 EGL config 选择合适的版本
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

    _eglConfig = OnChooseEGLConfig();
    CheckOpenGLESVersion();
    LogEGLConfig(_eglConfig);

    // Bind Client API
    switch (glMode)
    {
        case GLMode::OPENGL:      eglBindAPI(EGL_OPENGL_API); break;
        case GLMode::OPENGL_ES3:  eglBindAPI(EGL_OPENGL_ES_API); break;
        default: /* 直接判定为打开失败,并且退出, see also : GLMode */
            assert(false);
            
            return false;
        break;
    }
    EGL_LOG_INFO << "Bind EGL client API, gl mode is: " << glMode;

    // Create Context
    {
        // EGL_CONTEXT_MAJOR_VERSION
        //   OpenGL    : 适配 4.x 以上
        //   OpenGL ES : 适配 3.x 以上
        // 其余版本非主流版本,目前不在适配范围之内
        // see also : eglspec.1.5.pdf - 3.7.1.1 OpenGL and OpenGL ES Context Versions
        EGLint contextAttributes[] = {
            EGL_CONTEXT_MAJOR_VERSION, 0,
            EGL_NONE,
        };
        if (glMode == GLMode::OPENGL)
        {
            contextAttributes[1] = 4;
        }
        else if (glMode == GLMode::OPENGL_ES3)
        {
            contextAttributes[1] = 3;
        }
        else
        {
            // 冗余判断,实际上不可能进来
            assert(false);
        }
        _eglContext = eglCreateContext(_eglDisplay, _eglConfig, nullptr, contextAttributes);
        if (_eglContext == EGL_NO_CONTEXT)
        {
            EGLint error = eglGetError();
            EGL_LOG_ERROR << "Create EGL context fail, gl mode is: " << glMode << ", gl major version is: " << contextAttributes[1]
                          << ", error is: " << EGLErrorToStr(error);
            assert(false);
            Close();
            return false;
        }
        else
        {
            EGL_LOG_INFO << "Create EGL context successfully";
        }
    }

    // Create surface
    _eglSurface = OnCreateSurface();

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

bool EGLWindow::BindRenderThread(bool bind)
{
    bool res = false;
    if (bind)
    {
        assert(EGL_NO_DISPLAY != _eglDisplay);
        assert(EGL_NO_CONTEXT != _eglContext);
        if (eglMakeCurrent(_eglDisplay, _eglSurface, _eglSurface, _eglContext) != EGL_TRUE)
        {
            EGLint error = eglGetError();
            EGL_LOG_ERROR << "(bind) EGL make current fail, error is: " << EGLErrorToStr(error);
            res = false;
        }
        else
        {
            EGL_LOG_INFO << "(bind) EGL make current successfully";
            res = true;
        }
    }
    else
    {
        assert(EGL_NO_DISPLAY != _eglDisplay);
        eglMakeCurrent(_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        EGL_LOG_INFO << "(unbind) EGL make current";
        res = true;
    }
    return res;
}

void EGLWindow::SetSurfaceType(GLSurfaceType surfaceType)
{
    _surfaceType = surfaceType;
}

GLSurfaceType EGLWindow::GetSurfaceType()
{
    return _surfaceType;
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
    _surfaceType  = GLSurfaceType::WINDOWS;
}

void EGLWindow::CheckOpenGLESVersion()
{
    assert(_eglConfig != nullptr);
    assert(EGL_NO_DISPLAY != _eglDisplay);

    auto isOpenGLES = [this]() -> bool
    {
        switch (_glMode)
        {
            case GLMode::OPENGL_ES2: /* pass through */
            case GLMode::OPENGL_ES3: return true;
            default: return false;
        }
    };
    if (!isOpenGLES()) return;
    
    EGLint renderType;
    GLMode glMode;
    EGLBoolean res = eglGetConfigAttrib(_eglDisplay, _eglConfig, EGL_RENDERABLE_TYPE, &renderType);
    if (renderType & EGL_OPENGL_ES3_BIT)
    {
        glMode = GLMode::OPENGL_ES3;
    }
    else if (renderType & EGL_OPENGL_ES2_BIT)
    {
        glMode = GLMode::OPENGL_ES2;
    
    }
    else
    {
        glMode = GLMode::UNKNOWN;
        EGL_LOG_ERROR << "GL mode is: " << _glMode << ", but can not find a appropriate version from select EGLConfig "
                      << "(may be choose another EGLConfig can fix this problem )";
        assert(false);
    }
    EGL_LOG_INFO << "Get OpenGL ES version from select EGL config, origin GL mode is: " << _glMode << ", current GL mode is: " << glMode;
    _glMode = glMode;
}

void EGLWindow::LogEGLConfig(EGLConfig eglConfig)
{
    assert(EGL_NO_DISPLAY != _eglDisplay);
    
    EGL_LOG_INFO << "EGL config attribute info:";

    {
        int32_t redSize, blueSize, greenSize;
        eglGetConfigAttrib(_eglDisplay, eglConfig, EGL_RED_SIZE, &redSize);
        eglGetConfigAttrib(_eglDisplay, eglConfig, EGL_BLUE_SIZE, &blueSize);
        eglGetConfigAttrib(_eglDisplay, eglConfig, EGL_GREEN_SIZE, &greenSize);
        EGL_LOG_INFO << "  -- EGL_RED_SIZE is: " << redSize;
        EGL_LOG_INFO << "  -- EGL_BLUE_SIZE is: " << blueSize;
        EGL_LOG_INFO << "  -- EGL_GREEN_SIZE is: " << greenSize;
    }

    {
        int32_t aplha, depth;
        eglGetConfigAttrib(_eglDisplay, eglConfig, EGL_ALPHA_SIZE, &aplha);
        eglGetConfigAttrib(_eglDisplay, eglConfig, EGL_DEPTH_SIZE, &depth);
        EGL_LOG_INFO << "  -- EGL_ALPHA_SIZE is: " << aplha;
        EGL_LOG_INFO << "  -- EGL_DEPTH_SIZE is: " << depth;
    }
    // Hint : 有需要再补充
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
    if (result != EGL_TRUE || numConfigs == 0)
    {
        EGL_LOG_ERROR << "eglGetConfigs fail, result is:" << EGLErrorToStr(result) << ", egl configs num is: " << numConfigs;
        assert(false);
        return eglChonfigs;
    }
    
    eglChonfigs.resize(numConfigs);
    result = eglGetConfigs(_eglDisplay, &eglChonfigs[0], numConfigs, &numConfigs);
    if (result != EGL_TRUE || numConfigs == 0)
    {
        EGL_LOG_ERROR << "eglGetConfigs fail, result is:" << EGLErrorToStr(result) << ", egl configs num is: " << numConfigs;
        assert(false);
        return eglChonfigs;
    }

    EGL_LOG_INFO << "GetEGLConfigs, total EGL config nums is: " << numConfigs;
    
    return eglChonfigs;
}

} // namespace Mmp
