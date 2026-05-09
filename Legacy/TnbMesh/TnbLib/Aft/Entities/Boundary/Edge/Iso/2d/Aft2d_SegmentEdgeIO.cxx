#include <Aft2d_SegmentEdge.hxx>

#include <Aft2d_PlnCurve.hxx>
#include <Aft2d_Element.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_BndEdgeGeomAdaptorBase<tnbLib::Aft2d_PlnCurve>)
{
	ar & theCurve_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_BndEdgeGeomAdaptorBase<tnbLib::Aft2d_PlnCurve>)
{
	ar & theCurve_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_SegmentEdge);