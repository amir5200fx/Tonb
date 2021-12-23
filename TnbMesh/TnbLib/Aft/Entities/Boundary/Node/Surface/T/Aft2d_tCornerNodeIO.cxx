#include <Aft2d_tCornerNode.hxx>

#include <Aft2d_tPlnCurveSurface.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_BndNodeToCurveAdaptor<tnbLib::Aft2d_tPlnCurveSurface>)
{
	ar & theCurves_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_BndNodeToCurveAdaptor<tnbLib::Aft2d_tPlnCurveSurface>)
{
	ar & theCurves_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_tCornerNode);