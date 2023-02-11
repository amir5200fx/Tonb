#pragma once
#ifndef _PtdShapeFit_Module_Header
#define _PtdShapeFit_Module_Header

#ifdef TnbPtdShapeFit_STATIC_DEFINE
#define TnbPtdShapeFit_EXPORT
#else
#ifdef TnbPtdShapeFit_EXPORT_DEFINE
#define TnbPtdShapeFit_EXPORT __declspec(dllexport)
#else
#define TnbPtdShapeFit_EXPORT __declspec(dllimport)
#endif // TnbPtdShapeFit_EXPORT_DEFINE
#endif // TnbPtdShapeFit_STATIC_DEFINE

#endif // !_PtdShapeFit_Module_Header
