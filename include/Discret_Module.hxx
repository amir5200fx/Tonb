#pragma once
#ifndef _Discret_Module_Header
#define _Discret_Module_Header

#ifdef TnbDiscret_STATIC_DEFINE
#define TnbDiscret_EXPORT
#else
#ifdef TnbDiscret_EXPORT_DEFINE
#define TnbDiscret_EXPORT __declspec(dllexport)
#else
#define TnbDiscret_EXPORT __declspec(dllimport)
#endif // TnbDiscret_EXPORT_DEFINE
#endif // TnbDiscret_STATIC_DEFINE

#endif // !_Discret_Module_Header
