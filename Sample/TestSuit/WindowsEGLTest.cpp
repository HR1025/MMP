#include "WindowsEGLTest.h"

#include "GPU/Windows/EGL/EGLWindowFactory.h"

#include "Sample/Common/Utility.h"

namespace Mmp
{

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

} // namespace Mmp