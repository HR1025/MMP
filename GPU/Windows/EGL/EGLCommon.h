//
// EGLCommon.h
//
// Library: GPU
// Package: Windows
// Module:  EGL
// 

#pragma once
#include <iostream>
#include <string>

#include <EGL/egl.h>

#include "Common/LogMessage.h"

#define EGL_LOG_TRACE   MMP_MLOG_TRACE("GPU")    
#define EGL_LOG_DEBUG   MMP_MLOG_DEBUG("GPU")    
#define EGL_LOG_INFO    MMP_MLOG_INFO("GPU")     
#define EGL_LOG_WARN    MMP_MLOG_WARN("GPU")     
#define EGL_LOG_ERROR   MMP_MLOG_ERROR("GPU")    
#define EGL_LOG_FATAL   MMP_MLOG_FATAL("GPU")    

namespace Mmp
{

enum class GLMode
{
    OPENGL,
    OPENGL_ES3,
    OPENGL_ES2, // not support
};
const std::string GLModeToStr(GLMode mode);
extern std::ostream& operator<<(std::ostream& os, GLMode mode);

/** 
 * @sa 1 - Default Frame Buffer : eglspec.1.5.pdf - 3.5 Rendering Surfaces
 *     2 - Frame Buffer Object  : es_spec_3.2.pdf - Chapter 9 Framebuffers and Framebuffer Objects
 */
enum class GLSurfaceType
{
    WINDOWS, // On-Screen  (Default Frame Buffer)
    PBUFFER, // Off-Screen (Default Frame Buffer)
    PIXMAP,  // Off-Screen (Default Frame Buffer)
    TEXTURE, // Off-Screen (No Default Frame Buffer)
};
const std::string GLSurfaceTypeToStr(GLSurfaceType type);
extern std::ostream& operator<<(std::ostream& os, GLSurfaceType type);

/**
 * @sa eglspec.1.5.pdf 3.1 Errors
 */
std::string EGLErrorToStr(EGLint error);

/**
 * @sa eglspec.1.5.pdf Table 3.1: EGLConfig attributes
 */
std::string EGLAttributeToStr(EGLint attr);

} // namespace Mmp 