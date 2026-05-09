#pragma once
#ifndef _Server_Module_Header
#define _Server_Module_Header

#ifdef TnbServer_STATIC_DEFINE
#define TnbServer_EXPORT
#else
#ifdef TnbServer_EXPORT_DEFINE
#define TnbServer_EXPORT __declspec(dllexport)
#else
#define TnbServer_EXPORT __declspec(dllimport)
#endif // TnbServer_EXPORT_DEFINE
#endif // TnbServer_STATIC_DEFINE

#endif