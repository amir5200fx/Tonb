#pragma once
#ifndef _frameMaker_Module_Header
#define _frameMaker_Module_Header

#ifdef TnbFrameMaker_STATIC_DEFINE
#define TnbFrameMaker_EXPORT
#else
#ifdef TnbFrameMaker_EXPORT_DEFINE
#define TnbFrameMaker_EXPORT __declspec(dllexport)
#else
#define TnbFrameMaker_EXPORT __declspec(dllimport)
#endif // TnbFrameMaker_EXPORT_DEFINE
#endif // TnbFrameMaker_STATIC_DEFINE

#endif // !_frameMaker_Module_Header
