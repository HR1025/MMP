#include "OpenGLCommond.h"

#include <cassert>

namespace Mmp
{

const std::string OpenGLCommondToStr(OpenGLCommond commond)
{
    switch (commond)
    {
        case OpenGLCommond::DEPTH: return "DEPTH";
        case OpenGLCommond::STENCILFUNC: return "STENCILFUNC";
        case OpenGLCommond::STENCILOP: return "STENCILOP";
        case OpenGLCommond::BLEND: return "BLEND";
        case OpenGLCommond::BLENDCOLOR: return "BLENDCOLOR";
        case OpenGLCommond::LOGICOP: return "LOGICOP";
        case OpenGLCommond::UNIFORM4I: return "UNIFORM4I";
        case OpenGLCommond::UNIFORM4UI: return "UNIFORM4UI";
        case OpenGLCommond::UNIFORM4F: return "UNIFORM4F";
        case OpenGLCommond::UNIFORMMATRIX: return "UNIFORMMATRIX";
        case OpenGLCommond::UNIFORMSTEREOMATRIX: return "UNIFORMSTEREOMATRIX";
        case OpenGLCommond::TEXTURESAMPLER: return "TEXTURESAMPLER";
        case OpenGLCommond::TEXTURELOD: return "TEXTURELOD";
        case OpenGLCommond::VIEWPORT: return "VIEWPORT";
        case OpenGLCommond::SCISSOR: return "SCISSOR";
        case OpenGLCommond::RASTER: return "RASTER";
        case OpenGLCommond::CLEAR: return "CLEAR";
        case OpenGLCommond::INVALIDATE: return "INVALIDATE";
        case OpenGLCommond::BINDPROGRAM: return "BINDPROGRAM";
        case OpenGLCommond::BINDTEXTURE: return "BINDTEXTURE";
        case OpenGLCommond::BIND_FB_TEXTURE: return "BIND_FB_TEXTURE";
        case OpenGLCommond::BIND_VERTEX_BUFFER: return "BIND_VERTEX_BUFFER";
        case OpenGLCommond::BIND_BUFFER: return "BIND_BUFFER";
        case OpenGLCommond::GENMIPS: return "GENMIPS";
        case OpenGLCommond::DRAW: return "DRAW";
        case OpenGLCommond::DRAW_INDEXED: return "DRAW_INDEXED";
        case OpenGLCommond::TEXTURE_SUBIMAGE: return "TEXTURE_SUBIMAGE";
        default: assert(false); return "UNKNOWN";
    }
}

} // namespace Mmp