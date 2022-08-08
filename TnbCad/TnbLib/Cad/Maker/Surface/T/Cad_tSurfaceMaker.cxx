#include <Cad_tSurfaceMaker.hxx>

#include <TModel_Edge.hxx>
#include <TModel_CmpEdge.hxx>
#include <TModel_Wire.hxx>
#include <TModel_Surface.hxx>
#include <Cad_tSurfaceMakerInfo.hxx>
#include <Cad_tEdgeMakerInfo.hxx>
#include <Cad_tEdgeMakerInfo_Absolute.hxx>
#include <Cad_tSurfaceMakerInfo_Absolute.hxx>
#include <Cad_tEdgeMaker.hxx>
#include <Cad_GeomSurface.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo


#include <TopoDS.hxx>
#include <BRepTools.hxx>
#include <BRep_Tool.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <ShapeFix_Wire.hxx>
#include <TopExp_Explorer.hxx>

const std::shared_ptr<tnbLib::Cad_tSurfaceMaker::MakerInfo> tnbLib::Cad_tSurfaceMaker::DEFAULT_INFO =
std::make_shared<tnbLib::Cad_tSurfaceMaker::MakerInfo>();

namespace tnbLib
{

	class Cad_tSurfaceMakerRunTimeSetConfigs
	{

		/*Private Data*/

	public:

		// default constructor [1/21/2022 Amir]

		Cad_tSurfaceMakerRunTimeSetConfigs()
		{
			SetConfigs();
		}

		// public functions and operators [1/21/2022 Amir]

		static void SetConfigs();
	};
}

void tnbLib::Cad_tSurfaceMakerRunTimeSetConfigs::SetConfigs()
{
	auto& myInfo = *Cad_tSurfaceMaker::DEFAULT_INFO;

	myInfo.Edge = std::make_shared<tnbLib::Cad_tEdgeMakerInfo_Absolute>(Precision::Confusion());
	myInfo.Surface = std::make_shared<tnbLib::Cad_tSurfaceMakerInfo_Absolute>();
}

static const tnbLib::Cad_tSurfaceMakerRunTimeSetConfigs mytSurfaceMakerRunTimeSetConfigsObj;

void tnbLib::Cad_tSurfaceMaker::Perform()
{
	if (NOT Info())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info. has been loaded." << endl
			<< abort(FatalError);
	}

	const auto forwardFace = TopoDS::Face(Face().Oriented(TopAbs_FORWARD));

	auto cmpEdge = std::make_shared<std::vector<std::shared_ptr<TModel_Edge>>>();
	Debug_Null_Pointer(cmpEdge);

	auto& outter_edges = *cmpEdge;

	const auto& surfInfo = Info()->Surface;
	const auto tol = surfInfo->Tolerance();
	Standard_Integer K = 0;
	Standard_Integer wireIndex = 0;

	const auto outer_wire = BRepTools::OuterWire(forwardFace);

	if (outer_wire.IsNull())
	{
		FatalErrorIn(FunctionSIG)
			<< "Null outer wire" << endl
			<< abort(FatalError);
	}

	ShapeFix_Wire SFWF(outer_wire, forwardFace, tol);

	SFWF.SetPrecision(surfInfo->Precision());
	SFWF.SetMaxTolerance(surfInfo->MaxTolerance());
	SFWF.SetMinTolerance(surfInfo->MinTolerance());

	SFWF.FixReorder();
	SFWF.ClosedWireMode() = Standard_True;
	SFWF.FixClosed();
	SFWF.FixConnected();

	SFWF.Perform();

	auto fixed_outer_wire = SFWF.Wire();
	for (
		BRepTools_WireExplorer anEdgeExp(fixed_outer_wire);
		anEdgeExp.More();
		anEdgeExp.Next()
		)
	{
		K++;

		auto edge = TopoDS::Edge(anEdgeExp.Current());
		auto edgeMaker = std::make_shared<Cad_tEdgeMaker>(edge, forwardFace, Info()->Edge);
		Debug_Null_Pointer(edgeMaker);

		edgeMaker->Perform();
		Debug_If_Condition_Message(NOT edgeMaker->IsDone(), "the application is not performed!");

		auto new_edge = edgeMaker->Edge();
		new_edge->SetIndex(K);

		outter_edges.push_back(std::move(new_edge));
	}

	auto outerWire = std::make_shared<TModel_Wire>(++wireIndex, "", cmpEdge);
	std::shared_ptr<std::vector<std::shared_ptr<TModel_Wire>>> Qwire;
	for (
		TopExp_Explorer aWireExp(forwardFace, TopAbs_WIRE);
		aWireExp.More();
		aWireExp.Next()
		)
	{
		auto wire = TopoDS::Wire(aWireExp.Current());

		if (wire.IsNull()) continue;
		if (wire IS_EQUAL outer_wire) continue;
		// has inner wire

		auto cmpEdge = std::make_shared<std::vector<std::shared_ptr<TModel_Edge>>>();
		Debug_Null_Pointer(cmpEdge);

		auto& Inner_edges = *cmpEdge;

		ShapeFix_Wire SFWF(wire, forwardFace, tol);

		SFWF.SetPrecision(surfInfo->Precision());
		SFWF.SetMaxTolerance(surfInfo->MaxTolerance());
		SFWF.SetMinTolerance(surfInfo->MinTolerance());

		SFWF.FixReorder();
		SFWF.ClosedWireMode() = Standard_True;
		SFWF.FixClosed();
		SFWF.FixConnected();

		SFWF.Perform();
		wire = SFWF.WireAPIMake();

		for (
			BRepTools_WireExplorer anEdgeExp(wire);
			anEdgeExp.More();
			anEdgeExp.Next()
			)
		{
			auto edge = TopoDS::Edge(anEdgeExp.Current());

			K++;

			auto edgeMaker = std::make_shared<Cad_tEdgeMaker>(edge, forwardFace, Info()->Edge);
			Debug_Null_Pointer(edgeMaker);

			edgeMaker->Perform();
			Debug_If_Condition_Message(NOT edgeMaker->IsDone(), "the application is not performed!");

			auto new_edge = edgeMaker->Edge();
			new_edge->SetIndex(K);

			Inner_edges.push_back(std::move(new_edge));
		}

		if (Inner_edges.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "Empty wire" << endl
				<< abort(FatalError);
		}

		auto innerWire = std::make_shared<TModel_Wire>(++wireIndex, "", cmpEdge);

		if (NOT Qwire) Qwire = std::make_shared<std::vector<std::shared_ptr<TModel_Wire>>>();
		Qwire->push_back(innerWire);
	}

	TopLoc_Location Location;
	auto geometry = 
		std::make_shared<Cad_GeomSurface>(BRep_Tool::Surface(forwardFace, Location));

	auto face =
		std::make_shared<TModel_Surface>(geometry, outerWire, Qwire);

	theSurface_ = std::move(face);

	Change_IsDone() = Standard_True;
}