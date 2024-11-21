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

#include <opencascade/Geom2dAPI_InterCurveCurve.hxx>

#include <Cad2d_VertexEdgeIntersection.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Tools.hxx>

std::shared_ptr<tnbLib::Cad2d_EdgeEdgeIntersection> 
tnbLib::Cad2d_EdgeEdgeIntersection::operator()
(
	const std::shared_ptr<Pln_Edge>& theEdge0,
	const std::shared_ptr<Pln_Edge>& theEdge1, 
	const Standard_Real theTol
	) const
{
	auto ent = Cad2d_EdgeEdgeIntersection::Intersect(theEdge0, theEdge1, theTol);
	return std::move(ent);
}

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

	if (theAlg.NbEntities() > 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "multiply intersection points between the vertex and the edge have been detected!" << endl
			<< abort(FatalError);
	}

	const auto& vtx = theAlg.Vtx();
	const auto& edge = theAlg.Edge();

	auto fwd = Pln_Tools::ForwardEdge(vtx);
	auto bwd = Pln_Tools::BackwardEdge(vtx);

	if (NOT fwd AND NOT bwd)
	{
		FatalErrorIn(FunctionSIG)
			<< "orphan vertex has been detected!" << endl
			<< abort(FatalError);
	}

	//Debug_Null_Pointer(fwd);
	//Debug_Null_Pointer(bwd);

	std::shared_ptr<Cad2d_EdgeEdgeIntersection> alg0;
	std::shared_ptr<Cad2d_EdgeEdgeIntersection> alg1;
	//auto alg0 = std::make_shared<Cad2d_EdgeEdgeIntersection>();
	//auto alg1 = std::make_shared<Cad2d_EdgeEdgeIntersection>();

	//Debug_Null_Pointer(alg0);
	//Debug_Null_Pointer(alg1);

	auto entity1 = std::make_shared<Cad2d_IntsctEntity_OrthSegment>(0);
	Debug_Null_Pointer(entity1);

	const auto& pair = theAlg.Entities()[0];

	const auto& ent0 = pair->Entity0();
	const auto& ent1 = pair->Entity1();

	Debug_Null_Pointer(ent0);
	Debug_Null_Pointer(ent1);

	if (NOT ent0->IsPoint())
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data!" << endl
			<< abort(FatalError);
	}

	if (NOT ent1->IsSegment())
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data!" << endl
			<< abort(FatalError);
	}

	/*auto intsct0 = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Point>(prior0);
	Debug_Null_Pointer(intsct0);*/

	auto intsc1 = std::dynamic_pointer_cast<Cad2d_IntsctEntity_OrthSegment>(ent1);
	Debug_Null_Pointer(intsc1);

	entity1->SetParentEdge(edge);
	entity1->SetParameter(intsc1->Parameter());
	entity1->SetCoord(intsc1->Coord());

	if (fwd)
	{
		alg0 = std::make_shared<Cad2d_EdgeEdgeIntersection>();
		Debug_Null_Pointer(alg0);

		auto& entities = alg0->EntitiesRef();

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

	if (bwd)
	{
		auto alg1 = std::make_shared<Cad2d_EdgeEdgeIntersection>();
		Debug_Null_Pointer(alg1);

		auto& entities = alg1->EntitiesRef();

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

	auto t = std::make_tuple(std::move(alg0), std::move(alg1));
	return std::move(t);
}

std::shared_ptr<tnbLib::Cad2d_EdgeEdgeIntersection> 
tnbLib::Cad2d_EdgeEdgeIntersection::Intersect
(
	const std::shared_ptr<Pln_Edge>& theEdge0,
	const std::shared_ptr<Pln_Edge>& theEdge1,
	const Standard_Real theTol
)
{
	if (NOT theEdge0)
	{
		FatalErrorIn("void tnbLib::Cad2d_EdgeEdgeIntersection::Perform()")
			<< "the edge0 is not loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT theEdge1)
	{
		FatalErrorIn("void tnbLib::Cad2d_EdgeEdgeIntersection::Perform()")
			<< "the edge1 is not loaded!" << endl
			<< abort(FatalError);
	}

	const auto& edge0 = *theEdge0;
	const auto& edge1 = *theEdge1;

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
		Inter(curve0.Geometry(), curve1.Geometry(), theTol);

	const auto& alg = Inter.Intersector();

	auto ent = std::make_shared<Cad2d_EdgeEdgeIntersection>(theEdge0, theEdge1);
	Debug_Null_Pointer(ent);

	ent->SetTolerance(theTol);
	auto& entities = ent->EntitiesRef();
	entities.reserve(alg.NbPoints() + alg.NbSegments());

	forThose(Index, 1, alg.NbPoints())
	{
		const auto& pt = alg.Point(Index);

		auto entity0 = std::make_shared<Cad2d_IntsctEntity_OrthSegment>(Index);
		auto entity1 = std::make_shared<Cad2d_IntsctEntity_OrthSegment>(Index);
		Debug_Null_Pointer(entity0);
		Debug_Null_Pointer(entity1);

		entity0->SetParentEdge(theEdge0);
		entity1->SetParentEdge(theEdge1);

		entity0->SetCoord(pt.Value());
		entity1->SetCoord(pt.Value());

		entity0->SetParameter(pt.ParamOnFirst());
		entity1->SetParameter(pt.ParamOnSecond());

		auto pair = std::make_shared<Cad2d_IntsctEntity_Pair>
			(Index, std::move(entity0), std::move(entity1));
		Debug_Null_Pointer(pair);

		entities.push_back(std::move(pair));
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

		entity0->SetParentEdge(theEdge0);
		entity1->SetParentEdge(theEdge1);

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

		auto pair = std::make_shared<Cad2d_IntsctEntity_Pair>
			(Index, std::move(entity0), std::move(entity1));
		Debug_Null_Pointer(pair);

		entities.push_back(std::move(pair));
	}
	return std::move(ent);
}