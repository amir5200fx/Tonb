#pragma once
#ifndef _GMesh_Module_Header
#define _GMesh_Module_Header

#ifdef TnbGMesh_STATIC_DEFINE
#define TnbGMesh_EXPORT
#else
#ifdef TnbGMesh_EXPORT_DEFINE
#define TnbGMesh_EXPORT __declspec(dllexport)
#else
#define TnbGMesh_EXPORT __declspec(dllimport)
#endif // TnbGMesh_EXPORT_DEFINE
#endif // TnbGMesh_STATIC_DEFINE

#endif // !_GMesh_Module_Header
