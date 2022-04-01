#include <Cad2d_CrvsIntsct.hxx>

#include <Cad2d_EdgeEdgeIntersection.hxx>
#include <Cad2d_VertexEdgeIntersection.hxx>
#include <Cad2d_VertexVertexIntersection.hxx>
#include <Cad2d_IntsctEntity_Pair.hxx>
#include <Cad2d_SearchCrv.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Real tnbLib::Cad2d_CrvsIntsct::DEFAULT_TOLERANCE = 1.0E-6;

namespace tnbLib
{

	

	static std::shared_ptr<Cad2d_IntsctEntity_Pair> 
		IntersectionTwoPoints
		(
			const std::shared_ptr<Pln_Vertex>& theVtx0,
			const std::shared_ptr<Pln_Vertex>& theVtx1, 
			const Standard_Real theTol
		)
	{
		auto ent = Cad2d_VertexVertexIntersection::Intersect(theVtx0, theVtx1, theTol);
		if (ent->NbEntities())
		{
			return ent->Entities()[0];
		}
		return nullptr;
	}

	static std::shared_ptr<Cad2d_IntsctEntity_Pair> 
		IntersectionPointCurve
		(
			const std::shared_ptr<Pln_Vertex>& theVtx, 
			const std::shared_ptr<Pln_Edge>& theCurve,
			const Standard_Real theTol
		)
	{
		auto ent = Cad2d_VertexEdgeIntersection::Intersect(theVtx, theCurve, theTol);
		if (ent->NbEntities())
		{
			return ent->Entities()[0];
		}
		return nullptr;
	}

	static auto 
		IntersectionCurveCurve
		(
			const std::shared_ptr<Pln_Edge>& theCurve0, 
			const std::shared_ptr<Pln_Edge>& theCurve1,
			const Standard_Real theTol
		)
	{
		static auto alg = Cad2d_EdgeEdgeIntersection();
		auto ent = alg(theCurve0, theCurve1, theTol);
		return std::move(ent);
	}

	static std::shared_ptr<Cad2d_IntsctEntity_Pair>
		Intersection
		(
			const std::shared_ptr<Pln_Vertex>& theVtx,
			const std::shared_ptr<Pln_Edge>& theCurve,
			const Standard_Real theTol
		)
	{
		if (theCurve->IsRing())
		{
			if (auto x = IntersectionTwoPoints(theVtx, theCurve->FirstVtx(), theTol))
			{
				return std::move(x);
			}

			if (auto x = IntersectionPointCurve(theVtx, theCurve, theTol))
			{
				return std::move(x);
			}
			return nullptr;
		}
		else
		{
#ifdef _DEBUG
			if (theCurve->Curve()->IsRing(theTol))
			{
				FatalErrorIn(FunctionSIG)
					<< "contradictory data has been detected!" << endl
					<<" - the edge will be supposed to be a ring under this tolerance threshold" << endl
					<< abort(FatalError);
			}
#endif // _DEBUG
			if (auto x = IntersectionTwoPoints(theVtx, theCurve->FirstVtx(), theTol))
			{
				return std::move(x);
			}

			if (auto x = IntersectionTwoPoints(theVtx, theCurve->LastVtx(), theTol))
			{
				return std::move(x);
			}

			if (auto x = IntersectionPointCurve(theVtx, theCurve, theTol))
			{
				return std::move(x);
			}
			return nullptr;
		}
	}

	static auto ExtremetiesIntersections
	(
		const std::shared_ptr<Pln_Edge>& theCurve0, 
		const std::shared_ptr<Pln_Edge>& theCurve1,
		const Standard_Real theTol
	)
	{
		std::vector<std::shared_ptr<Cad2d_EntityEntityIntersection>> entities;
		{
			const auto vtx = theCurve0->FirstVtx();
			Debug_Null_Pointer(vtx);

			auto ent = Intersection(vtx, theCurve1, theTol);
			if (ent)
			{
				auto entity = std::make_shared<Cad2d_VertexEdgeIntersection>(vtx, theCurve1);
				Debug_Null_Pointer(entity);

				entity->EntitiesRef().push_back(std::move(ent));
				entities.push_back(std::move(entity));
			}
		}

		{
			const auto vtx = theCurve0->LastVtx();
			Debug_Null_Pointer(vtx);

			auto ent = Intersection(vtx, theCurve1, theTol);
			if (ent)
			{
				auto entity = std::make_shared<Cad2d_VertexEdgeIntersection>(vtx, theCurve1);
				Debug_Null_Pointer(entity);

				entity->EntitiesRef().push_back(std::move(ent));
				entities.push_back(std::move(entity));
			}
		}

		if (auto x = IntersectionPointCurve(theCurve1->FirstVtx(), theCurve0, theTol))
		{
			auto entity = std::make_shared<Cad2d_VertexEdgeIntersection>(theCurve1->FirstVtx(), theCurve0);
			Debug_Null_Pointer(entity);
			entity->EntitiesRef().push_back(std::move(x));
			entities.push_back(std::move(entity));
		}

		if (auto x = IntersectionPointCurve(theCurve1->LastVtx(), theCurve0, theTol))
		{
			auto entity = std::make_shared<Cad2d_VertexEdgeIntersection>(theCurve1->LastVtx(), theCurve0);
			Debug_Null_Pointer(entity);
			entity->EntitiesRef().push_back(std::move(x));
			entities.push_back(std::move(entity));
		}
		return std::move(entities);
	}

	static auto Intersection
	(
		const std::shared_ptr<Pln_Edge>& theCurve0, 
		const std::shared_ptr<Pln_Edge>& theCurve1, 
		const Standard_Real theTol
	)
	{
		auto entities = ExtremetiesIntersections(theCurve0, theCurve1, theTol);

		auto inners = IntersectionCurveCurve(theCurve0, theCurve1, theTol);
		if (inners->NbEntities())
		{
			entities.push_back(std::move(inners));
		}
		return std::move(entities);
	}

	static auto Contains
	(
		const Standard_Integer id, 
		const std::vector<Standard_Integer>& Indices
	)
	{
		for (auto x : Indices)
		{
			if (x IS_EQUAL id)
			{
				return Standard_True;
			}
		}
		return Standard_False;
	}

	static std::vector<std::shared_ptr<Cad2d_EntityEntityIntersection>>
		Intersection
		(
			const std::shared_ptr<Pln_Edge>& theCurve, 
			const std::vector<std::shared_ptr<Pln_Edge>>& theCurves, 
			std::map<Standard_Integer, std::vector<Standard_Integer>>& theBooklet, 
			const Standard_Real theTolerance
		)
	{
		static std::vector<Standard_Integer> myIntializer;
		auto& curveNbs = myIntializer;

		auto iter = theBooklet.find(theCurve->Index());
		if (iter IS_EQUAL theBooklet.end())
		{
			auto paired = std::make_pair(theCurve->Index(), std::vector<Standard_Integer>());
			auto insert = theBooklet.insert(std::move(paired));
			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data has been detected!" << endl
					<< abort(FatalError);
			}

			auto entities = Intersection(theCurve, theCurves, theBooklet, theTolerance);
			return std::move(entities);
		}
		else
		{
			curveNbs = iter->second;
		}

		std::vector<std::shared_ptr<Cad2d_EntityEntityIntersection>> entities;
		for (const auto& x : theCurves)
		{
			Debug_Null_Pointer(x);
			auto id = x->Index();

			Standard_Boolean doIntersection = Standard_False;
			if (curveNbs.empty())
			{
				doIntersection = Standard_True;
			}
			else
			{
				if (NOT Contains(id, curveNbs))
				{
					doIntersection = Standard_True;
				}
			}

			if (doIntersection)
			{
				auto ents = Intersection(theCurve, x, theTolerance);
				for (auto& e : ents)
				{
					entities.push_back(std::move(e));
				}

				curveNbs.push_back(id);

				auto iter = theBooklet.find(id);
				if (iter NOT_EQUAL theBooklet.end())
				{
					auto& l = iter->second;
					l.push_back(theCurve->Index());
				}
				else
				{
					std::vector<Standard_Integer> l;
					l.push_back(theCurve->Index());

					auto paired = std::make_pair(id, std::move(l));
					auto insert = theBooklet.insert(std::move(paired));
					if (NOT insert.second)
					{
						FatalErrorIn(FunctionSIG)
							<< "duplicate data has been detected!" << endl
							<< abort(FatalError);
					}
				}
			}
		}

		return std::move(entities);
	}
}

void tnbLib::Cad2d_CrvsIntsct::Perform()
{
	if (NOT Engine())
	{
		FatalErrorIn(FunctionSIG)
			<< "no search engine has been found!" << endl
			<< abort(FatalError);
	}

	if (Engine()->NbCurves() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< " at least two curves are needed to run the application!" << endl
			<< abort(FatalError);
	}

	std::map<Standard_Integer, std::vector<Standard_Integer>> booklet;

	const auto curves = Engine()->AllCurves();

	std::vector<std::shared_ptr<Cad2d_EntityEntityIntersection>> entities;
	for (const auto& x : curves)
	{
		Debug_Null_Pointer(x);

		auto foundItems = Engine()->Find(x);
		if (foundItems.size())
		{
			auto ents = Intersection(x, foundItems, booklet, Tolerance());
			if (ents.size())
			{
				for (auto& e : ents)
				{
					entities.push_back(std::move(e));
				}
			}
		}
	}

	EntitiesRef() = std::move(entities);

	Change_IsDone() = Standard_True;
}