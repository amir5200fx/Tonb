#pragma once
#ifndef _LegMesh_Module_Header
#define _LegMesh_Module_Header

#ifdef TnbLegMesh_STATIC_DEFINE
#define TnbLegMesh_EXPORT
#else
#ifdef TnbLegMesh_EXPORT_DEFINE
#define TnbLegMesh_EXPORT __declspec(dllexport)
#else
#define TnbLegMesh_EXPORT __declspec(dllimport)
#endif // TnbLegMesh_EXPORT_DEFINE
#endif // TnbLegMesh_STATIC_DEFINE

#endif // !_LegMesh_Module_Header
