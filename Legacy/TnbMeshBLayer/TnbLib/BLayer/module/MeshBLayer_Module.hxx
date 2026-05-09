#pragma once
#ifndef _MeshBLayer_Module_Header
#define _MeshBLayer_Module_Header

#ifdef TnbMeshBLayer_STATIC_DEFINE
#define TnbMeshBLayer_EXPORT
#else
#ifdef TnbMeshBLayer_EXPORT_DEFINE
#define TnbMeshBLayer_EXPORT __declspec(dllexport)
#else
#define TnbMeshBLayer_EXPORT __declspec(dllimport)
#endif // TnbMeshBLayer_EXPORT_DEFINE
#endif // TnbMeshBLayer_STATIC_DEFINE

#endif // !_MeshBLayer_Module_Header
