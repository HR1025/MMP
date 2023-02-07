#include "DisplaySDL.h"

#include <SDL2/SDL.h>

namespace Mmp
{

bool DisplaySDL::Init()
{
    /**
     * @brief 检查 SDL 的编译时头文件和运行时库是否匹配
     */
    auto checkSDLVersionIsSame = []() -> bool
    {
        SDL_version compiled;
        SDL_version linked;
        SDL_VERSION(&compiled);
        SDL_GetVersion(&linked);
        SDL_LOG_INFO << "SDL version when complie is: (" << (int)compiled.major << "." << (int)compiled.minor << "." << (int)compiled.patch << ")";
        SDL_LOG_INFO << "SDL version when link is: (" << (int)linked.major << "." << (int)linked.minor << "." << (int)linked.patch << ")";
        return (compiled.major == linked.major && compiled.minor == linked.minor && compiled.patch == linked.patch);
    };
    
    if (!checkSDLVersionIsSame())
    {
        SDL_LOG_ERROR << "SDL version is not same when runing as when compiling";
        return false;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LOG_ERROR << "Failed to initialize SDL, error is: " << SDL_GetError();
        return false;
    }
    else
    {
        SDL_LOG_INFO << "Initialize SDL with SDL_INIT_VIDEO flag successfully";
    }
    
    return true;
}

} // namespace Mmp