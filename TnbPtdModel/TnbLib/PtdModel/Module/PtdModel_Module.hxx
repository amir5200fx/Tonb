#pragma once
#ifndef _PtdModel_Module_Header
#define _PtdModel_Module_Header

#ifdef TnbPtdModel_STATIC_DEFINE
#define TnbPtdModel_EXPORT
#else
#ifdef TnbPtdModel_EXPORT_DEFINE
#define TnbPtdModel_EXPORT __declspec(dllexport)
#else
#define TnbPtdModel_EXPORT __declspec(dllimport)
#endif // TnbPtdModel_EXPORT_DEFINE
#endif // TnbPtdModel_STATIC_DEFINE

#endif // !_PtdModel_Module_Header

