#pragma once
#ifndef _Mesh_Module_Header
#define _Mesh_Module_Header

#ifdef TnbMesh_STATIC_DEFINE
#define TnbMesh_EXPORT
#else
#ifdef TnbMesh_EXPORT_DEFINE
#define TnbMesh_EXPORT __declspec(dllexport)
#else
#define TnbMesh_EXPORT __declspec(dllimport)
#endif // TnbMesh_EXPORT_DEFINE
#endif // TnbMesh_STATIC_DEFINE

#endif // !_Mesh_Module_Header
