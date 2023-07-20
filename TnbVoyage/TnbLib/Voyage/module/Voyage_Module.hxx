#pragma once
#ifndef _Voyage_Module_Header
#define _Voyage_Module_Header

#ifdef TnbVoyage_STATIC_DEFINE
#define TnbVoyage_EXPORT
#else
#ifdef TnbVoyage_EXPORT_DEFINE
#define TnbVoyage_EXPORT __declspec(dllexport)
#else
#define TnbVoyage_EXPORT __declspec(dllimport)
#endif // TnbVoyage_EXPORT_DEFINE
#endif // TnbVoyage_STATIC_DEFINE

#endif // !_Voyage_Module_Header
