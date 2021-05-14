#include <Aft2d_CornerNode.hxx>

#include <Aft2d_PlnCurve.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_BndNodeToCurveAdaptor<tnbLib::Aft2d_PlnCurve>)
{
	ar & theCurves_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_BndNodeToCurveAdaptor<tnbLib::Aft2d_PlnCurve>)
{
	ar & theCurves_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_CornerNode);