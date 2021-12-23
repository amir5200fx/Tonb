#include <Aft2d_gCornerNode.hxx>

#include <Aft2d_gPlnCurveSurface.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_BndNodeToCurveAdaptor<tnbLib::Aft2d_gPlnCurveSurface>)
{
	ar & theCurves_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_BndNodeToCurveAdaptor<tnbLib::Aft2d_gPlnCurveSurface>)
{
	ar & theCurves_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_gCornerNode);

