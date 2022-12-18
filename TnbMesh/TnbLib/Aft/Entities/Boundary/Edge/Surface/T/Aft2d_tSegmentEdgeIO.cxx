#include <Aft2d_tSegmentEdge.hxx>

#include <Aft2d_tPlnCurveSurface.hxx>
#include <Aft2d_ElementSurface.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_BndEdgeGeomAdaptorBase<tnbLib::Aft2d_tPlnCurveSurface>)
{
	ar & theCurve_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_BndEdgeGeomAdaptorBase<tnbLib::Aft2d_tPlnCurveSurface>)
{
	ar & theCurve_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_tSegmentEdge);