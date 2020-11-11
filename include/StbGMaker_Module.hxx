#pragma once
#ifndef _StbGMaker_Module_Header
#define _StbGMaker_Module_Header

#define TnbStbGMaker_STATIC_DEFINE

#ifdef TnbStbGMaker_STATIC_DEFINE
#define TnbStbGMaker_EXPORT
#else
#ifdef TnbStbGMaker_EXPORT_DEFINE
#define TnbStbGMaker_EXPORT __declspec(dllexport)
#else
#define TnbStbGMaker_EXPORT __declspec(dllimport)
#endif // TnbStbGMaker_EXPORT_DEFINE
#endif // TnbStbGMaker_STATIC_DEFINE

#endif // !_StbGMaker_Module_Header
