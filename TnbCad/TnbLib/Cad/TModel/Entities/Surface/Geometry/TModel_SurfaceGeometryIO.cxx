#include <TModel_SurfaceGeometry.hxx>

#include <Geo_Serialization.hxx>
#include <OpenCascade_Serialization.hxx>

#include <BRep_Tool.hxx>
#include <TopoDS.hxx>
#include <Geom_Surface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_SurfaceGeometry)
{
	auto hasGeometry = false;
	if (theGeometry_)
	{
		hasGeometry = true;
		ar & hasGeometry;
		ar & theGeometry_;
	}
	else
	{
		ar & hasGeometry;
	}
	
	auto hasMesh = false;
	if (theMesh_)
	{
		hasMesh = true;
		ar & hasMesh;
		ar & theMesh_;
	}
	else
	{
		ar & hasMesh;
	}
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_SurfaceGeometry)
{
	bool hasGeometry;
	bool hasMesh;

	theGeometry_.Nullify();
	theMesh_.Nullify();

	ar & hasGeometry;
	if (hasGeometry)
	{
		ar & theGeometry_;
	}

	ar & hasMesh;

	if (hasMesh)
	{
		ar & theMesh_;
	}	
}