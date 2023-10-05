#pragma once
#ifndef _HydDyna_Module_Header
#define _HydDyna_Module_Header

#ifdef TnbHydDyna_STATIC_DEFINE
#define TnbHydDyna_EXPORT
#else
#ifdef TnbHydDyna_EXPORT_DEFINE
#define TnbHydDyna_EXPORT __declspec(dllexport)
#else
#define TnbHydDyna_EXPORT __declspec(dllimport)
#endif // TnbHydDyna_EXPORT_DEFINE
#endif // TnbHydDyna_STATIC_DEFINE

#endif // !_HydDyna_Module_Header
