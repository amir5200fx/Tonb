#include <Aft2d_SegmentEdgeAnIso.hxx>

#include <Aft2d_PlnCurveAnIso.hxx>
#include <Aft2d_ElementAnIso.hxx>

#include <opencascade/Standard_Transient.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_BndEdgeGeomAdaptorBase<tnbLib::Aft2d_PlnCurveAnIso>)
{
	ar & theCurve_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_BndEdgeGeomAdaptorBase<tnbLib::Aft2d_PlnCurveAnIso>)
{
	ar & theCurve_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_SegmentEdgeAnIso);