#pragma once
#ifndef _CadModel_Module_Header
#define _CadModel_Module_Header

#ifdef TnbCadModel_STATIC_DEFINE
#define TnbCadModel_EXPORT
#else
#ifdef TnbCadModel_EXPORT_DEFINE
#define TnbCadModel_EXPORT __declspec(dllexport)
#else
#define TnbCadModel_EXPORT __declspec(dllimport)
#endif // TnbCadModel_EXPORT_DEFINE
#endif // TnbCadModel_STATIC_DEFINE

#endif // !_CadModel_Module_Header
