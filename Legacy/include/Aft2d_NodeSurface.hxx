#pragma once
#ifndef _Aft2d_NodeSurface_Header
#define _Aft2d_NodeSurface_Header

#include <Aft_Node.hxx>
#include <Aft2d_NodeSurfaceTraits.hxx>
#include <Aft2d_NodeSurfaceFwd.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT Standard_Real Aft2d_NodeSurface::CalcMaxParaAdjLength() const;
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_NodeSurface);

#endif // !_Aft2d_NodeSurface_Header