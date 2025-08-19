#pragma once
#ifndef _Airfoil_Module_Header
#define _Airfoil_Module_Header

#ifdef TnbAirfoil_STATIC_DEFINE
#define TnbAirfoil_EXPORT
#else
#ifdef TnbAirfoil_EXPORT_DEFINE
#define TnbAirfoil_EXPORT __declspec(dllexport)
#else
#define TnbAirfoil_EXPORT __declspec(dllimport)
#endif // TnbAirfoil_EXPORT_DEFINE
#endif // TnbAirfoil_STATIC_DEFINE

#endif // !_Airfoil_Module_Header
