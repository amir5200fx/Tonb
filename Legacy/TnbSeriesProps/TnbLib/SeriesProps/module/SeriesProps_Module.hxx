#pragma once
#ifndef _SeriesProps_Module_Header
#define _SeriesProps_Module_Header

#ifdef TnbSeriesProps_STATIC_DEFINE
#define TnbSeriesProps_EXPORT
#else
#ifdef TnbSeriesProps_EXPORT_DEFINE
#define TnbSeriesProps_EXPORT __declspec(dllexport)
#else
#define TnbSeriesProps_EXPORT __declspec(dllimport)
#endif // TnbSeriesProps_EXPORT_DEFINE
#endif // TnbSeriesProps_STATIC_DEFINE

#endif // !_SeriesProps_Module_Header
