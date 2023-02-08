#include "WindowsEGLTest.h"

#ifdef USE_EGL
#include "GPU/Windows/EGL/EGLWindowFactory.h"
#include "Sample/Common/Utility.h"
#endif /* USE_EGL */

namespace Mmp
{

#ifdef USE_EGL
void WindowsEGLTest()
{
    InitLogger();
    auto window = EGLWindowFactory::DefaultFactory().CreateEGLWindow("EGLWindowDefault");
    window->SetSurfaceType(GLSurfaceType::TEXTURE);
    window->Open();
    window->BindRenderThread(true);
    window->BindRenderThread(false);
    window->Close();
}
#else
void WindowsEGLTest()
{

}
#endif /* USE_EGL */

} // namespace Mmp