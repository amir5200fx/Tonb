#include <Aft2d_CornerNodeAnIso.hxx>

#include <Aft2d_PlnCurveAnIso.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_BndNodeToCurveAdaptor<tnbLib::Aft2d_PlnCurveAnIso>)
{
	ar & theCurves_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_BndNodeToCurveAdaptor<tnbLib::Aft2d_PlnCurveAnIso>)
{
	ar & theCurves_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_CornerNodeAnIso);