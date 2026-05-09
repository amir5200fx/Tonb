#pragma once
#ifndef _ShapePx_Module_Header
#define _ShapePx_Module_Header

#ifdef TnbShapePx_STATIC_DEFINE
#define TnbShapePx_EXPORT
#else
#ifdef TnbShapePx_EXPORT_DEFINE
#define TnbShapePx_EXPORT __declspec(dllexport)
#else
#define TnbShapePx_EXPORT __declspec(dllimport)
#endif // TnbShapePx_EXPORT_DEFINE
#endif // TnbShapePx_STATIC_DEFINE

#endif // !_ShapePx_Module_Header
