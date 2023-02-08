//
// OpenGLCommond.h
//
// Library: GPU
// Package: GL
// Module:  OpenGL
// 

#pragma once

#include <iostream>
#include <string>

namespace Mmp
{

enum class OpenGLCommond
{
	DEPTH,
	STENCILFUNC,
	STENCILOP,
	BLEND,
	BLENDCOLOR,
	LOGICOP,
	UNIFORM4I,
	UNIFORM4UI,
	UNIFORM4F,
	UNIFORMMATRIX,
	UNIFORMSTEREOMATRIX,
	TEXTURESAMPLER,
	TEXTURELOD,
	VIEWPORT,
	SCISSOR,
	RASTER,
	CLEAR,
	INVALIDATE,
	BINDPROGRAM,
	BINDTEXTURE,
	BIND_FB_TEXTURE,
	BIND_VERTEX_BUFFER,
	BIND_BUFFER,
	GENMIPS,
	DRAW,
	DRAW_INDEXED,
	TEXTURE_SUBIMAGE,
};
const std::string OpenGLCommondToStr(OpenGLCommond commond);
extern std::ostream& operator<<(std::ostream& os, OpenGLCommond commond);

} // namespace Mmp
