#pragma once
#ifndef _Cad2d_Module_Header
#define _Cad2d_Module_Header

#define TnbCad2d_STATIC_DEFINE

#ifdef TnbCad2d_STATIC_DEFINE
#define TnbCad2d_EXPORT
#else
#ifdef TnbCad2d_EXPORT_DEFINE
#define TnbCad2d_EXPORT __declspec(dllexport)
#else
#define TnbCad2d_EXPORT __declspec(dllimport)
#endif // TnbCad2d_EXPORT_DEFINE
#endif // TnbCad2d_STATIC_DEFINE

#endif // !_Cad2d_Module_Header
