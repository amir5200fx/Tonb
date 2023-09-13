#include <Aft2d_SolutionData.hxx>

#include <Mesh_Curve_Info.hxx>
#include <Mesh_BndLayer_Info.hxx>
#include <Cad2d_Plane.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_QuadMesh.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Box.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_SolutionDataBase)
{
	ar& thePlane_;

	ar& theGlobalCurveInfo_;

	ar& theCurveInfo_;

	ar& theGlobalBndLayerInfo_;

	ar& theBoundaryMesh_;
	ar& theMesh_;
	ar& theBndLayers_;

	ar& theSizeFun_;

	ar& theBndLayerList_;
	ar& theGlobalBndLayerInfo_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_SolutionDataBase)
{
	ar& thePlane_;

	ar& theGlobalCurveInfo_;

	ar& theCurveInfo_;

	ar& theGlobalBndLayerInfo_;

	ar& theBoundaryMesh_;
	ar& theMesh_;
	ar& theBndLayers_;

	ar& theSizeFun_;

	ar& theBndLayerList_;
	ar& theGlobalBndLayerInfo_;
}