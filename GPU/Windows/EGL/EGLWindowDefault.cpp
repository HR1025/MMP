#include "EGLWindowDefault.h"

namespace Mmp
{

EGLDisplay EGLWindowDefault::OnOpenDisplay()
{   
    // eglspec.1.5.pdf - 3.2 Initialization
    return eglGetDisplay(EGL_DEFAULT_DISPLAY);
}

EGLConfig  EGLWindowDefault::OnChooseEGLConfig()
{
    // Hint : 大多情况下选择第一个即可,默认情况下 EGLConfig 配置遵循一定规则的排序
    // eglspec.1.5.pdf - 3.4.1.2 Sorting of EGLConfigs 
    auto eglConfigs = GetAllEGLConfigs();

    return !eglConfigs.empty() ? eglConfigs[0] : nullptr;
}

} // namespace Mmp