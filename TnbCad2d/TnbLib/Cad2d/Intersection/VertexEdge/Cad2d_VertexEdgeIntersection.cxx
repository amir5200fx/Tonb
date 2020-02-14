#include <Cad2d_VertexEdgeIntersection.hxx>

#include <Global_Macros.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Tools.hxx>
#include <Cad2d_IntsctEntity_Point.hxx>
#include <Cad2d_IntsctEntity_OrthSegment.hxx>
#include <Cad2d_IntsctEntity_Pair.hxx>

#include <Geom2dAPI_ProjectPointOnCurve.hxx>

tnbLib::Cad2d_VertexEdgeIntersection::Cad2d_VertexEdgeIntersection()
{
}

void tnbLib::Cad2d_VertexEdgeIntersection::Perform()
{
	if (NOT Vtx())
	{
		FatalErrorIn("void tnbLib::Cad2d_EdgeEdgeIntersection::Perform()")
			<< "the vertex is not loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Edge())
	{
		FatalErrorIn("void tnbLib::Cad2d_EdgeEdgeIntersection::Perform()")
			<< "the edge is not loaded!" << endl
			<< abort(FatalError);
	}

	const auto& edge = *Edge();

	if (NOT edge.Curve())
	{
		FatalErrorIn("void tnbLib::Cad2d_EdgeEdgeIntersection::Perform()")
			<< "the edge does not have a geometric curve!" << endl
			<< abort(FatalError);
	}

	const auto& curve = *edge.Curve();

	if (NOT Pln_Tools::IsBounded(curve.Geometry()))
	{
		FatalErrorIn("void tnbLib::Cad2d_EdgeEdgeIntersection::Perform()")
			<< "the curve is not bounded!" << endl
			<< abort(FatalError);
	}

	Geom2dAPI_ProjectPointOnCurve
		alg(Vtx()->Coord(), curve.Geometry());

	if (alg.LowerDistance() <= Tolerance())
	{
		auto& entities = ChangeEntities();
		entities.reserve(1);

		auto entity0 = std::make_shared<Cad2d_IntsctEntity_Point>(1);
		auto entity1 = std::make_shared<Cad2d_IntsctEntity_OrthSegment>(1);
		
		entity0->SetParentVertex(Vtx());
		entity1->SetParentEdge(Edge());

		entity1->SetCoord(alg.NearestPoint());

		entity1->SetParameter(alg.LowerDistanceParameter());

		auto pair = std::make_shared<Cad2d_IntsctEntity_Pair>(1, entity0, entity1);
		Debug_Null_Pointer(pair);

		entities.push_back(pair);
	}

	Change_IsDone() = Standard_True;
}