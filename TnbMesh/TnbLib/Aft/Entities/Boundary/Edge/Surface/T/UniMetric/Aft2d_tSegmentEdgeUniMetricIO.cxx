#include <Aft2d_tSegmentEdgeUniMetric.hxx>

#include <Aft2d_tPlnCurveSurfaceUniMetric.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_BndEdgeGeomAdaptorBase<tnbLib::Aft2d_tPlnCurveSurfaceUniMetric>)
{
	ar & theCurve_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_BndEdgeGeomAdaptorBase<tnbLib::Aft2d_tPlnCurveSurfaceUniMetric>)
{
	ar & theCurve_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_tSegmentEdgeUniMetric);