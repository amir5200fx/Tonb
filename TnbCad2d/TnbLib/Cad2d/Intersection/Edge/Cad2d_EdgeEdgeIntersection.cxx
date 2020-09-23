#include <Cad2d_EdgeEdgeIntersection.hxx>

#include <Global_Macros.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Tools.hxx>
#include <Cad2d_IntsctEntity_OrthSegment.hxx>
#include <Cad2d_IntsctEntity_TangSegment.hxx>
#include <Cad2d_IntsctEntity_Pair.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2dAPI_InterCurveCurve.hxx>

tnbLib::Cad2d_EdgeEdgeIntersection::Cad2d_EdgeEdgeIntersection()
{
}

tnbLib::Cad2d_EdgeEdgeIntersection::Cad2d_EdgeEdgeIntersection
(
	const Standard_Integer theIndex
)
	: Cad2d_EntityEntityIntersection(theIndex)
{
}

tnbLib::Cad2d_EdgeEdgeIntersection::Cad2d_EdgeEdgeIntersection
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Cad2d_EntityEntityIntersection(theIndex, theName)
{
}

void tnbLib::Cad2d_EdgeEdgeIntersection::Perform()
{
	if (NOT Edge0())
	{
		FatalErrorIn("void tnbLib::Cad2d_EdgeEdgeIntersection::Perform()")
			<< "the edge0 is not loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Edge1())
	{
		FatalErrorIn("void tnbLib::Cad2d_EdgeEdgeIntersection::Perform()")
			<< "the edge1 is not loaded!" << endl
			<< abort(FatalError);
	}

	const auto& edge0 = *Edge0();
	const auto& edge1 = *Edge1();

	if (NOT edge0.Curve())
	{
		FatalErrorIn("void tnbLib::Cad2d_EdgeEdgeIntersection::Perform()")
			<< "the edge0 does not have a geometric curve!" << endl
			<< abort(FatalError);
	}

	if (NOT edge1.Curve())
	{
		FatalErrorIn("void tnbLib::Cad2d_EdgeEdgeIntersection::Perform()")
			<< "the edge1 does not have a geometric curve!" << endl
			<< abort(FatalError);
	}

	const auto& curve0 = *edge0.Curve();
	const auto& curve1 = *edge1.Curve();

	if (NOT Pln_Tools::IsBounded(curve0.Geometry()))
	{
		FatalErrorIn("void tnbLib::Cad2d_EdgeEdgeIntersection::Perform()")
			<< "the curve0 is not bounded!" << endl
			<< abort(FatalError);
	}

	if (NOT Pln_Tools::IsBounded(curve1.Geometry()))
	{
		FatalErrorIn("void tnbLib::Cad2d_EdgeEdgeIntersection::Perform()")
			<< "the curve1 is not bounded!" << endl
			<< abort(FatalError);
	}

	Geom2dAPI_InterCurveCurve 
		Inter(curve0.Geometry(), curve1.Geometry(), Tolerance());

	const auto& alg = Inter.Intersector();

	auto& entities = ChangeEntities();
	entities.reserve(alg.NbPoints() + alg.NbPoints());

	forThose(Index, 1, alg.NbPoints())
	{
		const auto& pt = alg.Point(Index);

		auto entity0 = std::make_shared<Cad2d_IntsctEntity_OrthSegment>(Index);
		auto entity1 = std::make_shared<Cad2d_IntsctEntity_OrthSegment>(Index);
		Debug_Null_Pointer(entity0);
		Debug_Null_Pointer(entity1);

		entity0->SetParentEdge(Edge0());
		entity1->SetParentEdge(Edge1());

		entity0->SetCoord(pt.Value());
		entity1->SetCoord(pt.Value());

		entity0->SetParameter(pt.ParamOnFirst());
		entity1->SetParameter(pt.ParamOnSecond());

		auto pair = std::make_shared<Cad2d_IntsctEntity_Pair>(Index, entity0, entity1);
		Debug_Null_Pointer(pair);

		entities.push_back(pair);
	}

	forThose(Index, 1, alg.NbSegments())
	{
		const auto& seg = alg.Segment(Index);

		if (NOT seg.HasFirstPoint())
		{
			FatalErrorIn("void Perform()") << endl
				<< "the segment does not have first point!" << endl
				<< abort(FatalError);
		}

		if (NOT seg.HasLastPoint())
		{
			FatalErrorIn("void Perform()") << endl
				<< "the segment does not have first point!" << endl
				<< abort(FatalError);
		}



		auto entity0 = std::make_shared<Cad2d_IntsctEntity_TangSegment>(Index);
		auto entity1 = std::make_shared<Cad2d_IntsctEntity_TangSegment>(Index);
		Debug_Null_Pointer(entity0);
		Debug_Null_Pointer(entity1);

		entity0->SetParentEdge(Edge0());
		entity1->SetParentEdge(Edge1());

		const auto& pt0 = seg.FirstPoint();
		const auto& pt1 = seg.LastPoint();

		entity0->SetCoord0(pt0.Value());
		entity0->SetCoord1(pt1.Value());
		entity0->SetParameter0(pt0.ParamOnFirst());
		entity0->SetParameter1(pt1.ParamOnFirst());

		if (seg.IsOpposite())
		{
			entity1->SetCoord0(pt1.Value());
			entity1->SetCoord1(pt0.Value());
			entity1->SetParameter0(pt1.ParamOnSecond());
			entity1->SetParameter1(pt0.ParamOnSecond());
		}
		else
		{
			entity1->SetCoord0(pt0.Value());
			entity1->SetCoord1(pt1.Value());
			entity1->SetParameter0(pt0.ParamOnSecond());
			entity1->SetParameter1(pt1.ParamOnSecond());
		}

		auto pair = std::make_shared<Cad2d_IntsctEntity_Pair>(Index, entity0, entity1);
		Debug_Null_Pointer(pair);

		entities.push_back(pair);
	}

	Change_IsDone() = Standard_True;
}

#include <Cad2d_VertexEdgeIntersection.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Tools.hxx>

std::tuple
<
	std::shared_ptr<tnbLib::Cad2d_EdgeEdgeIntersection>,
	std::shared_ptr<tnbLib::Cad2d_EdgeEdgeIntersection>
> 
tnbLib::Cad2d_EdgeEdgeIntersection::ConvertFrom
(
	const Cad2d_VertexEdgeIntersection & theAlg,
	const Standard_Real theTol
)
{
	if (NOT theAlg.NbEntities())
	{
		FatalErrorIn(FunctionSIG)
			<< "null intersection" << endl
			<< abort(FatalError);
	}

	const auto& vtx = theAlg.Vtx();
	const auto& edge = theAlg.Edge();

	auto fwd = Pln_Tools::ForwardEdge(vtx);
	auto bwd = Pln_Tools::BackwardEdge(vtx);

	Debug_Null_Pointer(fwd);
	Debug_Null_Pointer(bwd);

	auto alg0 = std::make_shared<Cad2d_EdgeEdgeIntersection>();
	auto alg1 = std::make_shared<Cad2d_EdgeEdgeIntersection>();

	Debug_Null_Pointer(alg0);
	Debug_Null_Pointer(alg1);

	auto entity1 = std::make_shared<Cad2d_IntsctEntity_OrthSegment>(0);
	Debug_Null_Pointer(entity1);

	const auto& pair = theAlg.Entities()[0];

	const auto& prior0 = pair->Entity0();
	const auto& prior1 = pair->Entity1();

	Debug_Null_Pointer(prior0);
	Debug_Null_Pointer(prior1);

	if (NOT prior0->IsPoint())
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data!" << endl
			<< abort(FatalError);
	}

	if (NOT prior1->IsSegment())
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data!" << endl
			<< abort(FatalError);
	}

	/*auto intsct0 = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Point>(prior0);
	Debug_Null_Pointer(intsct0);*/

	auto intsc1 = std::dynamic_pointer_cast<Cad2d_IntsctEntity_OrthSegment>(prior1);
	Debug_Null_Pointer(intsc1);

	entity1->SetParentEdge(edge);
	entity1->SetParameter(intsc1->Parameter());
	entity1->SetCoord(intsc1->Coord());

	{
		auto& entities = alg0->ChangeEntities();

		auto ent = std::make_shared<Cad2d_IntsctEntity_OrthSegment>(0);
		Debug_Null_Pointer(ent);

		ent->SetParentEdge(fwd);
		ent->SetParameter(fwd->Sense() ? fwd->Curve()->FirstParameter() : fwd->Curve()->LastParameter());
		ent->SetCoord(fwd->Curve()->Value(ent->Parameter()));

		if (Distance(ent->Coord(), vtx->Coord()) > theTol)
		{
			FatalErrorIn(FunctionSIG)
				<< "contradictory data!" << endl
				<< abort(FatalError);
		}

		auto nPair = std::make_shared<Cad2d_IntsctEntity_Pair>(ent, entity1);

		entities.push_back(std::move(nPair));
	}

	{
		auto& entities = alg1->ChangeEntities();

		auto ent = std::make_shared<Cad2d_IntsctEntity_OrthSegment>(0);
		Debug_Null_Pointer(ent);

		ent->SetParentEdge(bwd);
		ent->SetParameter(bwd->Sense() ? bwd->Curve()->FirstParameter() : bwd->Curve()->LastParameter());
		ent->SetCoord(bwd->Curve()->Value(ent->Parameter()));

		if (Distance(ent->Coord(), vtx->Coord()) > theTol)
		{
			FatalErrorIn(FunctionSIG)
				<< "contradictory data!" << endl
				<< abort(FatalError);
		}

		auto nPair = std::make_shared<Cad2d_IntsctEntity_Pair>(ent, entity1);

		entities.push_back(std::move(nPair));
	}

	auto t = std::make_tuple(alg0, alg1);
	return std::move(t);
}