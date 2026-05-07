#include <Cad_FastDiscrete.hxx>

#include <FastDiscrete_Params.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <opencascade/TopoDS_Face.hxx>
#include <opencascade/TopoDS_Wire.hxx>
#include <opencascade/TopoDS.hxx>
#include <opencascade/TopExp_Explorer.hxx>
#include <opencascade/BRepTools_WireExplorer.hxx>
#include <opencascade/BRep_Tool.hxx>
#include <opencascade/BRepTools.hxx>
#include <opencascade/BRepBndLib.hxx>
#include <opencascade/BndLib_AddSurface.hxx>
#include <opencascade/BRepMesh_FastDiscret.hxx>
#include <opencascade/BRepMesh_EdgeDiscret.hxx>
#include <opencascade/Bnd_Box.hxx>
#include <opencascade/Poly_Triangulation.hxx>
#include <opencascade/Geom2d_BSplineCurve.hxx>
#include <opencascade/Geom2d_TrimmedCurve.hxx>
#include <opencascade/GeomConvert.hxx>
#include <opencascade/GeomAdaptor_Surface.hxx>
#include <opencascade/Geom2dConvert.hxx>
#include <opencascade/Geom_BSplineSurface.hxx>
#include <opencascade/Geom_RectangularTrimmedSurface.hxx>

#include <opencascade/IMeshTools_MeshBuilder.hxx>

#include <opencascade/BRepMesh_IncrementalMesh.hxx>

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
	IMeshTools_Parameters aMeshParams;
	aMeshParams.Deflection = Parameters.Deflection;
	aMeshParams.Angle = Parameters.Angle;
	aMeshParams.Relative = Parameters.Relative;
	aMeshParams.InParallel = Parameters.InParallel;
	aMeshParams.MinSize = Parameters.MinSize;
	aMeshParams.InternalVerticesMode = Parameters.InternalVerticesMode;
	aMeshParams.ControlSurfaceDeflection = Standard_True;

	BRepMesh_IncrementalMesh 
		aMesher
		(
			theShape, aMeshParams
		);


	/*BRepMesh_FastDiscret::Parameters Params;
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

	Mesh.Perform(theShape);*/

	/*const auto& sharedFaces = Mesh.SharedFaces();

	for (
		TopExp_Explorer aFaceExp(theShape.Oriented(TopAbs_FORWARD), TopAbs_FACE);
		aFaceExp.More();
		aFaceExp.Next()
		)
	{
		auto aFace = TopoDS::Face(aFaceExp.Current());

		Handle(BRepMesh_FaceAttribute) faceAttr;
		Mesh.GetFaceAttribute(aFace, faceAttr);
		if (faceAttr.IsNull())
		{
			FatalErrorIn(FunctionSIG)
				<< "no face attribute has been found." << endl
				<< abort(FatalError);
		}

		for (
			TopExp_Explorer aWireExp(aFace, TopAbs_WIRE);
			aWireExp.More();
			aWireExp.Next()
			)
		{
			auto wire = TopoDS::Wire(aWireExp.Current());

			for (
				BRepTools_WireExplorer anEdgeExp(wire);
				anEdgeExp.More();
				anEdgeExp.Next()
				)
			{
				auto edge = TopoDS::Edge(anEdgeExp.Current());
				BRepMesh_EdgeTessellator
					tess
					(
						edge, faceAttr,
						sharedFaces,
						Params.Deflection,
						Params.Angle,
						Params.MinSize
					);
			}
		}
	}*/
}

void tnbLib::Cad_FastDiscrete::Triangulation
(
	const TopoDS_Shape & theShape,
	const Bnd_Box & theBox,
	const FastDiscrete_Params & Parameters
)
{
	IMeshTools_Parameters aMeshParams;
	aMeshParams.Deflection = Parameters.Deflection;
	aMeshParams.Angle = Parameters.Angle;
	aMeshParams.Relative = Parameters.Relative;
	aMeshParams.InParallel = Parameters.InParallel;
	aMeshParams.MinSize = Parameters.MinSize;
	aMeshParams.InternalVerticesMode = Parameters.InternalVerticesMode;
	aMeshParams.ControlSurfaceDeflection = Standard_True;

	BRepMesh_IncrementalMesh
		aMesher
		(
			theShape, aMeshParams
		);

	/*BRepMesh_FastDiscret::Parameters Params;
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

	BRepAdaptor_Curve bac;
	GCPnts_TangentialDeflection thePointsOnCurve;
	thePointsOnCurve.Initialize(bac,Params.Deflection,)*/
	/*const auto& sharedFaces = Mesh.SharedFaces();

	for (
		TopExp_Explorer aFaceExp(theShape.Oriented(TopAbs_FORWARD), TopAbs_FACE);
		aFaceExp.More();
		aFaceExp.Next()
		)
	{
		auto aFace = TopoDS::Face(aFaceExp.Current());

		Handle(BRepMesh_FaceAttribute) faceAttr;
		Mesh.GetFaceAttribute(aFace, faceAttr);
		if (faceAttr.IsNull())
		{
			FatalErrorIn(FunctionSIG)
				<< "no face attribute has been found." << endl
				<< abort(FatalError);
		}

		for (
			TopExp_Explorer aWireExp(aFace, TopAbs_WIRE);
			aWireExp.More();
			aWireExp.Next()
			)
		{
			auto wire = TopoDS::Wire(aWireExp.Current());

			for (
				BRepTools_WireExplorer anEdgeExp(wire);
				anEdgeExp.More();
				anEdgeExp.Next()
				)
			{
				auto edge = TopoDS::Edge(anEdgeExp.Current());
				BRepMesh_EdgeTessellator
					tess
					(
						edge, faceAttr,
						sharedFaces,
						Params.Deflection,
						Params.Angle,
						Params.MinSize
					);
			}
		}
	}*/
}