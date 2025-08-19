#pragma once
#ifndef _Global_Module_Header
#define _Global_Module_Header

#include <Base_Module.hxx>

#ifdef TnbGlobal_STATIC_DEFINE
#define TnbGlobal_EXPORT
#else
#ifdef TnbGlobal_EXPORT_DEFINE
#define TnbGlobal_EXPORT __declspec(dllexport)
#else
#define TnbGlobal_EXPORT __declspec(dllimport)
#endif // TnbGlobal_EXPORT_DEFINE
#endif // TnbGlobal_STATIC_DEFINE

#endif // !_Global_Module_Header
