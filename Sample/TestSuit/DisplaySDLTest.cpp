#include "DisplaySDLTest.h"

#ifdef USE_SDL
#include <thread>

#include "Sample/Common/Utility.h"
#include "Sample/Common/Display/SDL/DisplaySDL.h"
#endif /* USE_SDL */

namespace Mmp
{

#ifdef USE_SDL
void DisplaySDLTest()
{
    InitLogger();
    
    uint32_t* image = new uint32_t[1920*1080];

    DisplaySDL displaySDL;
    displaySDL.Init();
    displaySDL.Open(1920, 1080);

    // Hint : 从黑渐变值纯白
    for (uint16_t i=0; i<=0xFF; i++)
    {
        memset(image, i, sizeof(uint32_t)*1920*1080);
        displaySDL.UpdateWindow(image);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));

    displaySDL.Close();
    displaySDL.UnInit();

    delete[] image;

    return;
}
#else
void DisplaySDLTest()
{

}
#endif /* USE_SDL */

} // namespace Mmp