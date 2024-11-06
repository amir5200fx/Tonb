#pragma once
#include <Aft3d_Edge.hxx>
#include <Aft3d_Facet.hxx>
#include <Aft3d_Node.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
inline const tnbLib::Pnt3d& 
tnbLib::legLib::Aft3d_Tools::GetCoord0(const Aft3d_Edge& theEdge)
{
	Debug_Null_Pointer(theEdge.Node0());
	return theEdge.Node0()->Coord();
}

inline const tnbLib::Pnt3d&
tnbLib::legLib::Aft3d_Tools::GetCoord1(const Aft3d_Edge& theEdge)
{
	Debug_Null_Pointer(theEdge.Node1());
	return theEdge.Node1()->Coord();
}

inline const tnbLib::Pnt3d& 
tnbLib::legLib::Aft3d_Tools::GetCoord0(const Aft3d_Facet& theFacet)
{
	Debug_Null_Pointer(theFacet.Node0());
	return theFacet.Node0()->Coord();
}

inline const tnbLib::Pnt3d&
tnbLib::legLib::Aft3d_Tools::GetCoord1(const Aft3d_Facet& theFacet)
{
	Debug_Null_Pointer(theFacet.Node1());
	return theFacet.Node1()->Coord();
}

inline const tnbLib::Pnt3d&
tnbLib::legLib::Aft3d_Tools::GetCoord2(const Aft3d_Facet& theFacet)
{
	Debug_Null_Pointer(theFacet.Node2());
	return theFacet.Node2()->Coord();
}