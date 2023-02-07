#include <memory>
#include <string>

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

    return 0;
}