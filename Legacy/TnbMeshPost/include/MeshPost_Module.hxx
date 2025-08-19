#pragma once
#ifndef _MeshPost_Module_Header
#define _MeshPost_Module_Header

#ifdef TnbMeshPost_STATIC_DEFINE
#define TnbMeshPost_EXPORT
#else
#ifdef TnbMeshPost_EXPORT_DEFINE
#define TnbMeshPost_EXPORT __declspec(dllexport)
#else
#define TnbMeshPost_EXPORT __declspec(dllimport)
#endif // TnbMeshPost_EXPORT_DEFINE
#endif // TnbMeshPost_STATIC_DEFINE

#endif // !_MeshPost_Module_Header
