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
    DisplaySDLTest();

    return 0;
}