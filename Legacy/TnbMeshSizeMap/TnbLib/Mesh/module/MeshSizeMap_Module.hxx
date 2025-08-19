#pragma once
#ifndef _MeshSizeMap_Module_Header
#define _MeshSizeMap_Module_Header

#ifdef TnbMeshSizeMap_STATIC_DEFINE
#define TnbMeshSizeMap_EXPORT
#else
#ifdef TnbMeshSizeMap_EXPORT_DEFINE
#define TnbMeshSizeMap_EXPORT __declspec(dllexport)
#else
#define TnbMeshSizeMap_EXPORT __declspec(dllimport)
#endif // TnbMeshSizeMap_EXPORT_DEFINE
#endif // TnbMeshSizeMap_STATIC_DEFINE

#endif // !_MeshSizeMap_Module_Header
