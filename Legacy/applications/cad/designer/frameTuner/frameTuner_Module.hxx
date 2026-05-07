#pragma once
#ifndef _frameTunner_Module_Header
#define _frameTunner_Module_Header

#ifdef TnbFrameTunner_STATIC_DEFINE
#define TnbFrameTunner_EXPORT
#else
#ifdef TnbFrameTunner_EXPORT_DEFINE
#define TnbFrameTunner_EXPORT __declspec(dllexport)
#else
#define TnbFrameTunner_EXPORT __declspec(dllimport)
#endif // TnbFrameTunner_EXPORT_DEFINE
#endif // TnbFrameTunner_STATIC_DEFINE

#endif // !_frameTunner_Module_Header
