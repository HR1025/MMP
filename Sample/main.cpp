#include <memory>
#include <string>
#include <thread>

#include "Sample/Common/Utility.h"
#include "Sample/TestSuit/TestSuit.h"
#include "Sample/Extension/media-server/ExMpegTest.h"

using namespace Mmp;

static std::string kTsPath = "xx/xx.ts"; 

int main()
{
    // LogTest();
    // AnyTest();
    // WindowsEGLTest();
    // DisplaySDLTest();
    MpegTsDemuxTest(kTsPath);

    return 0;
}