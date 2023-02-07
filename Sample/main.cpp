#include <memory>
#include <string>

#include "Sample/Common/Utility.h"
#include "TestSuit/LogTest.h"

#include "GPU/Windows/EGL/EGLWindowFactory.h"

using namespace Mmp;

int main()
{
    InitLogger();
    
    // LogTest();
    auto window = EGLWindowFactory::DefaultFactory().CreateEGLWindow("EGLWindowDefault");
    window->SetSurfaceType(GLSurfaceType::TEXTURE);
    window->Open();
    window->BindRenderThread(true);
    window->BindRenderThread(false);
    window->Close();

    return 0;
}