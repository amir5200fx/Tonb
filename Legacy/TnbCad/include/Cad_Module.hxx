#pragma once
#ifndef _Cad_Module_Header
#define _Cad_Module_Header

#ifdef TnbCad_STATIC_DEFINE
#define TnbCad_EXPORT
#else
#ifdef TnbCad_EXPORT_DEFINE
#define TnbCad_EXPORT __declspec(dllexport)
#else
#define TnbCad_EXPORT __declspec(dllimport)
#endif // TnbCad_EXPORT_DEFINE
#endif // TnbCad_STATIC_DEFINE

#endif // !_Cad_Module_Header
