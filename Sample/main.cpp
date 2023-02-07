#include <memory>
#include <string>
#include <thread>

#include "Sample/Common/Utility.h"
#include "Sample/TestSuit/TestSuit.h"

#include "Sample/Common/Display/SDL/DisplaySDL.h"

using namespace Mmp;

int main()
{
    // LogTest();
    // WindowsEGLTest();

    InitLogger();
    DisplaySDL displaySDL;
    displaySDL.Init();
    displaySDL.Open(1920, 1080);
    std::this_thread::sleep_for(std::chrono::seconds(10));
    displaySDL.Close();
    displaySDL.UnInit();

    return 0;
}