#pragma once
#ifndef _MeshBase_Module_Header
#define _MeshBase_Module_Header

#ifdef TnbMeshBase_STATIC_DEFINE
#define TnbMeshBase_EXPORT
#else
#ifdef TnbMeshBase_EXPORT_DEFINE
#define TnbMeshBase_EXPORT __declspec(dllexport)
#else
#define TnbMeshBase_EXPORT __declspec(dllimport)
#endif // TnbMeshBase_EXPORT_DEFINE
#endif // TnbMeshBase_STATIC_DEFINE

#endif // !_MeshBase_Module_Header

