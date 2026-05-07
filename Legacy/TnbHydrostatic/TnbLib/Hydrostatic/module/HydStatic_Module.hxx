#pragma once
#ifndef _HydStatic_Module_Header
#define _HydStatic_Module_Header

#ifdef TnbHydStatic_STATIC_DEFINE
#define TnbHydStatic_EXPORT
#else
#ifdef TnbHydStatic_EXPORT_DEFINE
#define TnbHydStatic_EXPORT __declspec(dllexport)
#else
#define TnbHydStatic_EXPORT __declspec(dllimport)
#endif // TnbHydStatic_EXPORT_DEFINE
#endif // TnbHydStatic_STATIC_DEFINE

#endif // !_HydStatic_Module_Header
