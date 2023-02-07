//
// DisplaySDL.h
//
// Library: Common
// Package: Display
// Module:  SDL
// 

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
 * @note 软件模拟
 */
class DisplaySDL
{
public:
    bool Init();
    // bool UnInit();
    // bool Open();
    // bool Close();
};

} // namespace Mmp