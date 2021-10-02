#include <Cad2d_PlanePlaneIntersection.hxx>

#include <Global_Macros.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Tools.hxx>
#include <Geo_BoxTools.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_EdgeEdgeIntersection.hxx>
#include <Cad2d_VertexEdgeIntersection.hxx>
#include <Cad_EntityManager.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	unsigned short Cad2d_PlanePlaneIntersection::verbose(0);
	const Standard_Real Cad2d_PlanePlaneIntersection::DEFAULT_TOLERANCE(1.0E-6);
}

namespace tnbLib
{

	auto RetrieveVertexEdgeIntersections
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

void tnbLib::Cad2d_PlanePlaneIntersection::Perform()
{
	if (verbose)
	{
		Info << endl;
		Info << "******* Calculating Plane-Plane intersections ********" << endl;
		Info << endl;
	}

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

	auto entities0 = 
		RetrieveVertexEdgeIntersections(corners0, edges1, Tolerance());
	auto entities1 =
		RetrieveVertexEdgeIntersections(corners1, edges0, Tolerance());

	if (verbose)
	{
		Info << endl
			<< " - nb. of the corners on the plane0: " << entities1.size()
			<< endl
			<< " - nb. of the corners on the plane1: " << entities0.size()
			<< endl;
	}

	Standard_Integer K = 0;
	entities.reserve(entities0.size() + entities1.size());
	for (auto& x : entities0)
	{
		x->SetIndex(++K);
		entities.push_back(std::move(x));
	}

	for (auto& x : entities1)
	{
		x->SetIndex(++K);
		entities.push_back(std::move(x));
	}

	std::vector<Entity2d_Box> boxes1;
	boxes1.reserve(edges1.size());
	for (const auto& x : edges1)
	{
		auto b = x->BoundingBox(Tolerance());
		boxes1.push_back(std::move(b));
	}

	for (const auto& x : edges0)
	{
		Debug_Null_Pointer(x);
		auto b = x->BoundingBox(Tolerance());

		size_t k = 0;
		for (const auto& edge : edges1)
		{
			Debug_Null_Pointer(edge);

			if (Geo_BoxTools::IsIntersect(b, boxes1[k++]))
			{
				auto alg = std::make_shared<Cad2d_EdgeEdgeIntersection>(++K);
				Debug_Null_Pointer(alg);

				alg->LoadEdge0(x);
				alg->LoadEdge1(edge);

				alg->SetTolerance(Tolerance());

				alg->Perform();

				if (alg->NbEntities())
				{
					entities.push_back(std::move(alg));
				}
			}
		}
	}

	if (verbose)
	{
		Info << endl
			<< " - nb. of entities: " << entities.size()
			<< endl;
	}

	Change_IsDone() = Standard_True;

	if (verbose)
	{
		Info << endl;
		Info << "******* End of the Calculating Plane-Plane intersections ********" << endl;
		Info << endl;
	}
}