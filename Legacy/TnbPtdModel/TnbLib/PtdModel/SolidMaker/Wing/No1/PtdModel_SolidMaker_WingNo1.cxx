#include <PtdModel_SolidMaker_WingNo1.hxx>

#include <PtdModel_Face.hxx>
#include <PtdModel_Wing.hxx>
#include <PtdModel_IO_Wing.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#undef DebugInfo

#include <Geom_BSplineCurve.hxx>
#include <Geom_BSplineSurface.hxx>
#include <GeomFill_BSplineCurves.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeEdge2d.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRep_Tool.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Edge.hxx>
#include <TopLoc_Location.hxx>
#include <TopoDS.hxx>

tnbLib::ptdModel::solidMaker::WingNo1::WingNo1()
	: LeadingPatch_(Standard_False)
	, TrailingPatch_(Standard_False)
	, theTolerance_(1.0E-6)
{
	// empty body [8/8/2021 Amir]
}

void tnbLib::ptdModel::solidMaker::WingNo1::Perform()
{
	if (NOT Wing())
	{
		FatalErrorIn(FunctionSIG)
			<< "no wing has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto& upperPatch = Wing()->Upper();
	const auto& lowerPatch = Wing()->Lower();

	if (NOT upperPatch)
	{
		FatalErrorIn(FunctionSIG)
			<< "no upper patch has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT lowerPatch)
	{
		FatalErrorIn(FunctionSIG)
			<< "no lower patch has been found!" << endl
			<< abort(FatalError);
	}

	auto upperFace = BRepBuilderAPI_MakeFace(upperPatch->Surface(), Tolerance());
	auto lowerFace = BRepBuilderAPI_MakeFace(lowerPatch->Surface(), Tolerance());

	theUpper_ = upperFace;
	theLower_ = lowerFace;

	TopoDS_Shape myShape;
	myShape = BRepAlgoAPI_Fuse(upperFace, lowerFace);

	std::vector<Handle(Geom_BSplineCurve)> curves;
	for (TopExp_Explorer Explorer(myShape, TopAbs_EDGE); Explorer.More(); Explorer.Next())
	{
		TopoDS_Edge Edge = TopoDS::Edge(Explorer.Current());
		TopLoc_Location Loc;
		Standard_Real First, Last;
		Handle(Geom_Curve) Curve = BRep_Tool::Curve(Edge, First, Last);

		Handle(Geom_BSplineCurve) BSplCurve = Handle(Geom_BSplineCurve)::DownCast(Curve);
		if (BSplCurve.IsNull())
		{
			FatalErrorIn(FunctionSIG)
				<< "null curve has been detected!" << endl
				<< abort(FatalError);
		}

		curves.push_back(std::move(BSplCurve));
	}

	if (LeadingPatch())
	{
		GeomFill_BSplineCurves leGeom(curves[1], curves[5], GeomFill_CoonsStyle);
		theLeading_ = BRepBuilderAPI_MakeFace(leGeom.Surface(), Tolerance());
	}

	if (TrailingPatch())
	{
		GeomFill_BSplineCurves teGeom(curves[2], curves[6], GeomFill_CoonsStyle);
		theTrailing_ = BRepBuilderAPI_MakeFace(teGeom.Surface(), Tolerance());
	}

	if (Trimmed())
	{
		GeomFill_BSplineCurves rootGeom(curves[0], curves[4], GeomFill_CoonsStyle);
		theRoot_ = BRepBuilderAPI_MakeFace(rootGeom.Surface(), Tolerance());

		GeomFill_BSplineCurves tipGeom(curves[3], curves[7], GeomFill_CoonsStyle);
		theTip_ = BRepBuilderAPI_MakeFace(tipGeom.Surface(), Tolerance());
	}
	else
	{

	}

	myShape = BRepAlgoAPI_Fuse(myShape, theRoot_);
	
	if (LeadingPatch())
	{
		myShape = BRepAlgoAPI_Fuse(myShape, theLeading_);
	}

	if (TrailingPatch())
	{
		myShape = BRepAlgoAPI_Fuse(myShape, theTrailing_);
	}

	myShape = BRepAlgoAPI_Fuse(myShape, theTip_);

	myShape.Reverse();

	Change_IsDone() = Standard_True;
}

void tnbLib::ptdModel::solidMaker::WingNo1::SetLeadingPatch(const Standard_Boolean d)
{
	LeadingPatch_ = d;
}

void tnbLib::ptdModel::solidMaker::WingNo1::SetTrailingPatch(const Standard_Boolean d)
{
	TrailingPatch_ = d;
}

void tnbLib::ptdModel::solidMaker::WingNo1::SetTolerance(const Standard_Real tol)
{
	theTolerance_ = tol;
}
