#include <Aft2d_gSegmentEdgeUniMetric.hxx>

#include <Aft2d_gPlnCurveSurfaceUniMetric.hxx>
#include <Aft2d_ElementSurface.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_BndEdgeGeomAdaptorBase<tnbLib::Aft2d_gPlnCurveSurfaceUniMetric>)
{
	ar & theCurve_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_BndEdgeGeomAdaptorBase<tnbLib::Aft2d_gPlnCurveSurfaceUniMetric>)
{
	ar & theCurve_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_gSegmentEdgeUniMetric);