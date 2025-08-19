#pragma once
#ifndef _Model_Module_Header
#define _Model_Module_Header

#ifdef TnbModel_STATIC_DEFINE
#define TnbModel_EXPORT
#else
#ifdef TnbModel_EXPORT_DEFINE
#define TnbModel_EXPORT __declspec(dllexport)
#else
#define TnbModel_EXPORT __declspec(dllimport)
#endif // TnbModel_EXPORT_DEFINE
#endif // TnbModel_STATIC_DEFINE

#endif // !_Model_Module_Header
