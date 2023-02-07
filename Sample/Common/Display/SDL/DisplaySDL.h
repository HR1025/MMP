//
// DisplaySDL.h
//
// Library: Common
// Package: Display
// Module:  SDL
// 

#include <cstdint>
#include <string>

#include <SDL2/SDL.h>

#include "Common/LogMessage.h"

#define  SDL_LOG_TRACE      MMP_MLOG_TRACE("Display")    
#define  SDL_LOG_DEBUG      MMP_MLOG_DEBUG("Display")    
#define  SDL_LOG_INFO       MMP_MLOG_INFO("Display")     
#define  SDL_LOG_WARN       MMP_MLOG_WARN("Display")     
#define  SDL_LOG_ERROR      MMP_MLOG_ERROR("Display")    
#define  SDL_LOG_FATAL      MMP_MLOG_FATAL("Display")    

namespace Mmp
{

/**
 * @brief  SDL 窗口创建器
 * @note   1 - CPU
 *         2 - 非线程安全
 *         3 - 简易版,只能用于调试不可用于生产
 * @todo   1 - 完善接口
 *         2 - 完善异常流处理
 */
class DisplaySDL
{
public:
    DisplaySDL();
public:
    void SetTitle(const std::string& title);
    std::string GetTitle();
public:
    /**
     * @brief 初始化
     */
    bool Init();
    /**
     * @brief 重置
     */
    bool UnInit();
    /**
     * @brief      打开窗口
     * @param[in]  width
     * @param[in]  height
     * @note       目前仅支持 1080 * 1920
     * @todo       完善接口
     */
    bool Open(uint32_t width, uint32_t height);
    /**
     * @brief      关闭窗口
     */
    bool Close();
    /**
     * @brief      更新整个窗口
     * @param[in]  frameBuffer
     * @note       frameBuffer 与 Open 时的参数保持一致, 内部不做任何判断
     * @todo       有需求更新 window 的话, 提供一个 UpdateSubWindow 即可
     *             (目前来看没有这个需求)
     */
    void UpdateWindow(const uint32_t* frameBuffer);
private:
    uint32_t     _displayWidth;
    uint32_t     _displayHeight;
    uint32_t     _displayRefresh;
    uint32_t     _windowWidth;
    uint32_t     _windowHeight;
    std::string  _title;
private:
    SDL_Window*      _window;
    SDL_Renderer*    _render;       // render bind to window
    SDL_Texture*     _texture;      // texture bind to render, 目前格式固定为 ARGB8888 
    uint32_t*        _frameBuffer;  // _frameBuffer "bind" to texture (格式固定为 ARGB888)
};

} // namespace Mmp