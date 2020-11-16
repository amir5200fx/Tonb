#pragma once
#ifndef _Geo_Module_Header
#define _Geo_Module_Header

#ifdef TnbGeo_STATIC_DEFINE
#define TnbGeo_EXPORT
#else
#ifdef TnbGeo_EXPORT_DEFINE
#define TnbGeo_EXPORT __declspec(dllexport)
#else
#define TnbGeo_EXPORT __declspec(dllimport)
#endif // TnbGeo_EXPORT_DEFINE
#endif // TnbGeo_STATIC_DEFINE


#endif // !_Geo_Module_Header
