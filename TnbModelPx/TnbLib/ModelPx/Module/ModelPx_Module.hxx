#pragma once
#ifndef _ModelPx_Module_Header
#define _ModelPx_Module_Header

#ifdef TnbModelPx_STATIC_DEFINE
#define TnbModelPx_EXPORT
#else
#ifdef TnbModelPx_EXPORT_DEFINE
#define TnbModelPx_EXPORT __declspec(dllexport)
#else
#define TnbModelPx_EXPORT __declspec(dllimport)
#endif // TnbModelPx_EXPORT_DEFINE
#endif // TnbModelPx_STATIC_DEFINE

#endif // !_ModelPx_Module_Header
