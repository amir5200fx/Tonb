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

	auto& entities = ChangeEntities();
	Standard_Integer k = 0;
	for (Standard_Integer i = 1; i <= alg.NbPoints(); i++)
	{
		if (alg.Distance(i) <= Tolerance())
		{
			auto entity0 = std::make_shared<Cad2d_IntsctEntity_Point>(++k);
			auto entity1 = std::make_shared<Cad2d_IntsctEntity_OrthSegment>(k);

			entity0->SetParentVertex(Vtx());

			entity1->SetParentEdge(Edge());
			entity1->SetCoord(alg.Point(i));
			entity1->SetParameter(alg.Parameter(i));

			auto pair = std::make_shared<Cad2d_IntsctEntity_Pair>(k, std::move(entity0), std::move(entity1));
			Debug_Null_Pointer(pair);

			entities.push_back(std::move(pair));
		}
	}

	Change_IsDone() = Standard_True;
}