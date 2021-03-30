#pragma once
#ifndef _ISC08_Module_Header
#define _ISC08_Module_Header

#ifdef TnbISC08_STATIC_DEFINE
#define TnbISC08_EXPORT
#else
#ifdef TnbISC08_EXPORT_DEFINE
#define TnbISC08_EXPORT __declspec(dllexport)
#else
#define TnbISC08_EXPORT __declspec(dllimport)
#endif // TnbISC08_EXPORT_DEFINE
#endif // TnbISC08_STATIC_DEFINE

#endif // !_ISC08_Module_Header
