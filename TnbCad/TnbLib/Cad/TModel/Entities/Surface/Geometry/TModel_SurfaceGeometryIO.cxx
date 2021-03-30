#include <TModel_SurfaceGeometry.hxx>

#include <Geo_Serialization.hxx>
#include <OpenCascade_Serialization.hxx>

#include <BRep_Tool.hxx>
#include <TopoDS.hxx>
#include <Geom_Surface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_SurfaceGeometry)
{
	ar & theGeometry_;
	ar & theMesh_;
	//TopoDS_Shape sh = theFace_;
	//ar & sh;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_SurfaceGeometry)
{
	ar & theGeometry_;
	ar & theMesh_;
	/*TopoDS_Shape sh;
	ar & sh;

	if (NOT sh.IsNull())
	{
		const TopoDS_Face& face = TopoDS::Face(sh);
		theFace_ = face;
	}

	if (NOT theFace_.IsNull())
	{
		theGeometry_ = BRep_Tool::Surface(theFace_);
	}*/
}