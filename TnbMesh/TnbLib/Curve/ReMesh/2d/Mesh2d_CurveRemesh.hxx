#pragma once
#ifndef _Mesh2d_CurveRemesh_Header
#define _Mesh2d_CurveRemesh_Header

#include <Mesh_Module.hxx>
#include <Mesh_CurveRemesh.hxx>
#include <Mesh2d_CurveRemeshFwd.hxx>

template<>
Standard_Real tnbLib::Mesh2d_CurveRemesh::Discretize(const std::shared_ptr<Geo2d_SizeFunction>&);

template<>
void tnbLib::Mesh2d_CurveRemesh::Perform();

#endif // !_Mesh2d_CurveRemesh_Header
