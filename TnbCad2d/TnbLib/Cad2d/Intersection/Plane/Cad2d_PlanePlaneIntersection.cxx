#include <Cad2d_PlanePlaneIntersection.hxx>

#include <Global_Macros.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Tools.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_EdgeEdgeIntersection.hxx>
#include <Cad2d_VertexEdgeIntersection.hxx>
#include <Cad_EntityManager.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	const Standard_Real Cad2d_PlanePlaneIntersection::DEFAULT_TOLERANCE(1.0E-6);
}

tnbLib::Cad2d_PlanePlaneIntersection::Cad2d_PlanePlaneIntersection()
	: theTolerance_(DEFAULT_TOLERANCE)
{
}

namespace tnbLib
{

	namespace palnePlaneIntersection
	{
		static std::vector<std::shared_ptr<Cad2d_EdgeEdgeIntersection>>
			RetrieveVertexEdgeIntersections
			(
				const std::vector<std::shared_ptr<Pln_Vertex>>& theVertices, 
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges, 
				const Standard_Real theTol
			)
		{

			std::vector<std::shared_ptr<Cad2d_EdgeEdgeIntersection>>
				entities;

			for (const auto& x : theVertices)
			{
				Debug_Null_Pointer(x);

				for (const auto& edge : theEdges)
				{
					Debug_Null_Pointer(edge);

					auto alg = std::make_shared<Cad2d_VertexEdgeIntersection>();
					Debug_Null_Pointer(alg);

					auto tol = MAX(theTol, x->Precision());

					alg->SetTolerance(tol);

					if (alg->NbEntities())
					{
						
						auto[alg0, alg1] = Cad2d_EdgeEdgeIntersection::ConvertFrom(*alg, theTol);

						Debug_Null_Pointer(alg0);
						Debug_Null_Pointer(alg1);

						entities.push_back(alg0);
						entities.push_back(alg1);					
					}
				}
			}
			return std::move(entities);
		}
	}
	

}

void tnbLib::Cad2d_PlanePlaneIntersection::Perform()
{
	if (NOT Plane0())
	{
		FatalErrorIn("void tnbLib::Cad2d_PlanePlaneIntersection::Perform()")
			<< "the plane 0 is not loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Plane1())
	{
		FatalErrorIn("void tnbLib::Cad2d_PlanePlaneIntersection::Perform()")
			<< "the plane 1 is not loaded!" << endl
			<< abort(FatalError);
	}

	const auto& plane0 = *Plane0();
	const auto& plane1 = *Plane1();

	Debug_Null_Pointer(plane0.Segments());
	Debug_Null_Pointer(plane1.Segments());

	auto edges0 = plane0.Segments()->RetrieveEntities();
	auto edges1 = plane1.Segments()->RetrieveEntities();

	auto corners0 = plane0.Corners()->RetrieveEntities();
	auto corners1 = plane1.Corners()->RetrieveEntities();

	auto& entities = ChangeEntities();

	Standard_Integer K = 0;

	auto entities0 = 
		palnePlaneIntersection::RetrieveVertexEdgeIntersections(corners0, edges1, Tolerance());
	auto entities1 =
		palnePlaneIntersection::RetrieveVertexEdgeIntersections(corners1, edges0, Tolerance());

	for (const auto& x : entities0)
	{
		x->SetIndex(++K);
		entities.push_back(x);
	}

	for (const auto& x : entities1)
	{
		x->SetIndex(++K);
		entities.push_back(x);
	}

	for (const auto& x : edges0)
	{
		Debug_Null_Pointer(x);

		for (const auto& edge : edges1)
		{
			Debug_Null_Pointer(edge);

			auto alg = std::make_shared<Cad2d_EdgeEdgeIntersection>(++K);
			Debug_Null_Pointer(alg);

			alg->LoadEdge0(x);
			alg->LoadEdge1(edge);

			alg->SetTolerance(Tolerance());

			alg->Perform();

			if (alg->NbEntities())
			{
				entities.push_back(alg);
			}
		}
	}

	Change_IsDone() = Standard_True;
}