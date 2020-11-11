#pragma once
#ifndef _Marine_Module_Header
#define _Marine_Module_Header

#define TnbMarine_STATIC_DEFINE

#ifdef TnbMarine_STATIC_DEFINE
#define TnbMarine_EXPORT
#else
#ifdef TnbMarine_EXPORT_DEFINE
#define TnbMarine_EXPORT __declspec(dllexport)
#else
#define TnbMarine_EXPORT __declspec(dllimport)
#endif // TnbMarine_EXPORT_DEFINE
#endif // TnbMarine_STATIC_DEFINE

#endif // !_Marine_Module_Header
