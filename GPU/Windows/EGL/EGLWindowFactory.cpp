#include "EGLWindowFactory.h"

#include <Poco/SingletonHolder.h>

#include "EGLWindowDefault.h"

namespace Mmp
{

namespace
{
    static Poco::SingletonHolder<EGLWindowFactory> sh;
}

EGLWindowFactory::EGLWindowFactory()
{
    RegisterBuiltins();
}

EGLWindowFactory::~EGLWindowFactory()
{

}

void EGLWindowFactory::RegisterEGLWindowClass(const std::string& className, EGLWindowInstantiator* instantiator)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _eglWindowFactory.RegisterClass(className, instantiator);
}

std::shared_ptr<EGLWindowInterface> EGLWindowFactory::CreateEGLWindow(const std::string& className)
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _eglWindowFactory.CreateInstance(className);
}

void EGLWindowFactory::RegisterBuiltins()
{
    std::lock_guard<std::mutex> lock(_mutex);
    _eglWindowFactory.RegisterClass("EGLWindowDefault", new Instantiator<EGLWindowDefault, EGLWindowInterface>);
}

EGLWindowFactory& EGLWindowFactory::DefaultFactory()
{
    return *sh.get();
}

} // namespace Mmp