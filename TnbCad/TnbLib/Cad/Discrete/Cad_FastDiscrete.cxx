#include <Cad_FastDiscrete.hxx>

#include <FastDiscrete_Params.hxx>

#include <TopoDS_Face.hxx>
#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>
#include <BRep_Tool.hxx>
#include <BRepBndLib.hxx>
#include <BndLib_AddSurface.hxx>
#include <BRepMesh_FastDiscret.hxx>
#include <Bnd_Box.hxx>
#include <Poly_Triangulation.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <GeomConvert.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <Geom2dConvert.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>


void tnbLib::Cad_FastDiscrete::Triangulation
(
	const TopoDS_Face & theFace,
	const FastDiscrete_Params & theParams
)
{
	TopoDS_Shape shape = theFace;
	Triangulation(shape, theParams);
}

void tnbLib::Cad_FastDiscrete::Triangulation
(
	const TopoDS_Shape & theShape,
	const FastDiscrete_Params & Parameters
)
{
	BRepMesh_FastDiscret::Parameters Params;
	Params.AdaptiveMin = Parameters.AdaptiveMin;
	Params.Angle = Parameters.Angle;
	Params.ControlSurfaceDeflection = Parameters.ControlSurfaceDeflection;
	Params.Deflection = Parameters.Deflection;
	Params.InParallel = Parameters.InParallel;
	Params.InternalVerticesMode = Parameters.InternalVerticesMode;
	Params.MinSize = Parameters.MinSize;
	Params.Relative = Parameters.Relative;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(theShape, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(theShape);
}

void tnbLib::Cad_FastDiscrete::Triangulation
(
	const TopoDS_Shape & theShape,
	const Bnd_Box & theBox,
	const FastDiscrete_Params & Parameters
)
{
	BRepMesh_FastDiscret::Parameters Params;
	Params.AdaptiveMin = Parameters.AdaptiveMin;
	Params.Angle = Parameters.Angle;
	Params.ControlSurfaceDeflection = Parameters.ControlSurfaceDeflection;
	Params.Deflection = Parameters.Deflection;
	Params.InParallel = Parameters.InParallel;
	Params.InternalVerticesMode = Parameters.InternalVerticesMode;
	Params.MinSize = Parameters.MinSize;
	Params.Relative = Parameters.Relative;

	BRepMesh_FastDiscret Mesh(theBox, Params);
	Mesh.Perform(theShape);
}