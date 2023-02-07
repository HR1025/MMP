#include "DisplaySDL.h"

#include <cassert>
#include <memory.h>

namespace Mmp
{

DisplaySDL::DisplaySDL()
{
    _displayWidth   = 0;
    _displayHeight  = 0;
    _displayRefresh = 0;
    _windowWidth    = 0;
    _windowHeight   = 0;
    _window         = nullptr;
    _render         = nullptr;
    _texture        = nullptr;
    _frameBuffer    = nullptr;
}

void DisplaySDL::SetTitle(const std::string& title)
{
    _title = title;
}

std::string DisplaySDL::GetTitle()
{
    return _title;
}

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
    
    /**
     * @brief 获取主屏幕相关信息
     */
    auto getMajorDisplayInfo = [this]() -> bool
    {
        SDL_DisplayMode displayMode;
        if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0)
        {
            return false;
        }
        _displayWidth   = displayMode.w;
        _displayHeight  = displayMode.h;
        _displayRefresh = displayMode.refresh_rate;
        SDL_LOG_INFO << "Major Displya info : (" << _displayWidth << "," << _displayHeight << ")x" << _displayRefresh;
        return true;
    };

    SDL_LOG_INFO << "SDL Display Init";

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
    
    if (!getMajorDisplayInfo())
    {
        return false;
    }

    return true;
}

bool DisplaySDL::UnInit()
{
    SDL_LOG_INFO << "SDL Display Uninit";
    
    SDL_Quit();
    return true;
}

bool DisplaySDL::Open(uint32_t width, uint32_t height)
{
    if (_window != nullptr)
    {
        SDL_LOG_WARN << "Window is already opened";
        return false; // Hint : 返回 false 提示调用者,非笔误 
    }
    SDL_LOG_INFO << "Try to open SDL window";
    std::string windowTitle = _title.empty() ? "SDL Window" : _title;
    _windowWidth = width;
    _windowHeight = height;
    _window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _windowWidth, _windowHeight, 0 /* NO FLAG, mean software */);
    if (_window != nullptr)
    {
        SDL_LOG_INFO << "Creare SDL window successfully, window title is: " << windowTitle;
    }
    else
    {
        SDL_LOG_ERROR << "Create SDL window fail, error is: " << SDL_GetError();
        return false;
    }
    _render = SDL_CreateRenderer(_window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_TARGETTEXTURE);
    if (_render != nullptr)
    {
        SDL_LOG_INFO << "Create SDL render Successfully";
    }
    else
    {
        SDL_LOG_ERROR << "Create SDL render fail, error is: " << SDL_GetError();
        return false;
    }
    _texture = SDL_CreateTexture(_render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, _windowWidth, _windowHeight);
    if (_texture != nullptr)
    {
        SDL_LOG_INFO << "Create SDL texture successfully";
    }
    else
    {
        SDL_LOG_ERROR << "Create SDL texture fail, error is: " << SDL_GetError();
        return false;
    }
    SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND); // 支持透明度

    _frameBuffer = new uint32_t[_windowWidth*_windowHeight];
    // 初始化窗口 (黑屏)
    memset(_frameBuffer, 0x00, sizeof(uint32_t)*_windowWidth*_windowHeight);

    SDL_UpdateTexture(_texture, NULL, reinterpret_cast<const void*>(_frameBuffer), sizeof(uint32_t)*_windowWidth);
    SDL_RenderCopy(_render, _texture, NULL, NULL);
    SDL_RenderPresent(_render);

    SDL_LOG_INFO << "Open SDL window successfully";

    return true;
}

bool DisplaySDL::Close()
{
    SDL_LOG_INFO << "Try to close SDL window";
    if (_frameBuffer)
    {
        delete[] _frameBuffer;
        _frameBuffer = nullptr;
    }
    if (_texture)
    {
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
        SDL_LOG_INFO << "Destory SDL texture";
    }
    if (_render)
    {
        SDL_DestroyRenderer(_render);
        SDL_LOG_INFO << "Destory SDL render";
    }
    if (_window)
    {
        SDL_DestroyWindow(_window);
        SDL_LOG_INFO << "Destory SDL window";
    }
    SDL_LOG_INFO << "Close SDL window successfully";
    return true;
}

void DisplaySDL::UpdateWindow(const uint32_t* frameBuffer)
{
    assert(_frameBuffer);
    memcpy(_frameBuffer, frameBuffer, sizeof(uint32_t)*_windowWidth*_windowHeight);
    SDL_UpdateTexture(_texture, NULL, reinterpret_cast<const void*>(_frameBuffer), sizeof(uint32_t)*_windowWidth);
    SDL_RenderCopy(_render, _texture, NULL, NULL);
    SDL_RenderPresent(_render);
}

} // namespace Mmp