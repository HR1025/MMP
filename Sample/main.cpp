#include <memory>
#include <string>

#include "TestSuit/LogTest.h"

#include "GPU/Windows/EGL/EGLWindowFactory.h"

using namespace Mmp;

void InitLogger()
{
    Logger::LoggerSingleton().SetFilePath("./smaple.log");
    Logger::LoggerSingleton().Enable(Mmp::Logger::Direction::CONSLOE);
    Logger::LoggerSingleton().Enable(Mmp::Logger::Direction::FILE);
}

int main()
{
    InitLogger();

    // LogTest();
    auto window = EGLWindowFactory::DefaultFactory().CreateEGLWindow("EGLWindowDefault");
    window->Open();

    return 0;
}