#include <Cad2d_SubdivideCrvs.hxx>

#include <Cad2d_IntsctEntity_Pair.hxx>
#include <Cad2d_IntsctEntity.hxx>
#include <Cad2d_IntsctEntity_Point.hxx>
#include <Cad2d_IntsctEntity_Segment.hxx>
#include <Cad2d_EdgeEdgeIntersection.hxx>
#include <Cad2d_VertexEdgeIntersection.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Edge.hxx>
#include <Pln_CmpEdge.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	typedef std::vector<std::shared_ptr<Cad2d_IntsctEntity_Segment>> entityList;
	typedef std::map<Standard_Integer, std::shared_ptr<entityList>>
		entityMap;
}

void tnbLib::Cad2d_SubdivideCrvs::Perform()
{
	/*auto seperate_point_edge = [](const std::shared_ptr<Cad2d_IntsctEntity_Pair>& x)
	{
		const auto& ent0 = x->Entity0();
		const auto& ent1 = x->Entity1();

		std::shared_ptr<Cad2d_IntsctEntity_Point> pt;
		std::shared_ptr<Cad2d_IntsctEntity_Segment> sgmnt;

		if (ent0->IsPoint())
		{
			pt = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Point>(ent0);
			Debug_Null_Pointer(pt);

			sgmnt = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Segment>(ent1);
			Debug_Null_Pointer(sgmnt);
		}
		else if (ent1->IsPoint())
		{
			pt = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Point>(ent1);
			Debug_Null_Pointer(pt);

			sgmnt = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Segment>(ent0);
			Debug_Null_Pointer(sgmnt);
		}
		auto t = std::make_pair(std::move(pt), std::move(sgmnt));
		return std::move(t);
	};*/

	auto insert_to_map = []
	(
		const Standard_Integer theIndex,
		std::shared_ptr<Cad2d_IntsctEntity_Segment>&& theEntity, 
		entityMap& theMap
		)
	{
		auto iter = theMap.find(theIndex);
		if (iter IS_EQUAL theMap.end())
		{
			auto l = std::make_shared<entityList>();
			l->push_back(std::move(theEntity));

			auto paired = std::make_pair(theIndex, std::move(l));
			auto insert = theMap.insert(std::move(paired));
			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data!" << endl
					<< abort(FatalError);
			}
		}
		else
		{
			auto& l = *iter->second;
			l.push_back(std::move(theEntity));
		}
	};

	entityMap entities;
	std::map<Standard_Integer, std::shared_ptr<Pln_Edge>> allEdges;

	// Register the edge-edge intersection type into a map. [1/30/2022 Amir]
	for (const auto& x : Entities())
	{
		Debug_Null_Pointer(x);

		if (x->IsVertexVertex())
		{
			continue;
		}

		// Convert the vertex-edge intersection type to the edge-edge type one [1/30/2022 Amir]
		if (auto vertexEdgeAlg = std::dynamic_pointer_cast<Cad2d_VertexEdgeIntersection>(x))
		{
			// Call the converting algorithm [1/30/2022 Amir]
			auto[edgeEdge0, edgeEdge1]  = 
				Cad2d_EdgeEdgeIntersection::ConvertFrom
				(
					*vertexEdgeAlg, vertexEdgeAlg->Tolerance()
				);

#ifdef _DEBUG
			if (NOT edgeEdge0 AND NOT edgeEdge1)
			{
				FatalErrorIn(FunctionSIG)
					<< "Something went wrong! both intersection entities are null." << endl
					<< abort(FatalError);
			}
#endif // _DEBUG

			if (edgeEdge0)
			{
				Debug_Null_Pointer(edgeEdge0->Edge0());
				Debug_Null_Pointer(edgeEdge0->Edge1());

				const auto& edge0 = *edgeEdge0->Edge0();
				const auto& edge1 = *edgeEdge0->Edge1();

				{// register edge0 [1/30/2022 Amir]
					auto paired = std::make_pair(edge0.Index(), edgeEdge0->Edge0());
					auto insert = allEdges.insert(std::move(paired));
					if (NOT insert.second)
					{
						// do nothing! the edge is already registered. [1/30/2022 Amir]
					}
				}

				{// register edge1 [1/30/2022 Amir]
					auto paired = std::make_pair(edge1.Index(), edgeEdge0->Edge1());
					auto insert = allEdges.insert(std::move(paired));
					if (NOT insert.second)
					{
						// do nothing! the edge is already registered. [1/30/2022 Amir]
					}
				}

				const auto& pairList = edgeEdge0->Entities();
				for (const auto& pair : pairList)
				{
					Debug_Null_Pointer(pair);

					auto ent0 = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Segment>(pair->Entity0());
					Debug_Null_Pointer(ent0);

					auto ent1 = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Segment>(pair->Entity1());
					Debug_Null_Pointer(ent1);

					insert_to_map(edge0.Index(), std::move(ent0), entities);
					insert_to_map(edge1.Index(), std::move(ent1), entities);
				}
			}

			if (edgeEdge1)
			{
				Debug_Null_Pointer(edgeEdge1->Edge0());
				Debug_Null_Pointer(edgeEdge1->Edge1());

				const auto& edge0 = *edgeEdge1->Edge0();
				const auto& edge1 = *edgeEdge1->Edge1();

				{// register edge0 [1/30/2022 Amir]
					auto paired = std::make_pair(edge0.Index(), edgeEdge1->Edge0());
					auto insert = allEdges.insert(std::move(paired));
					if (NOT insert.second)
					{
						// do nothing! the edge is already registered. [1/30/2022 Amir]
					}
				}

				{// register edge1 [1/30/2022 Amir]
					auto paired = std::make_pair(edge1.Index(), edgeEdge1->Edge1());
					auto insert = allEdges.insert(std::move(paired));
					if (NOT insert.second)
					{
						// do nothing! the edge is already registered. [1/30/2022 Amir]
					}
				}

				const auto& pairList = edgeEdge1->Entities();
				for (const auto& pair : pairList)
				{
					Debug_Null_Pointer(pair);

					auto ent0 = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Segment>(pair->Entity0());
					Debug_Null_Pointer(ent0);

					auto ent1 = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Segment>(pair->Entity1());
					Debug_Null_Pointer(ent1);

					insert_to_map(edge0.Index(), std::move(ent0), entities);
					insert_to_map(edge1.Index(), std::move(ent1), entities);
				}
			}
		}
		else
		{ // the entity must be an edge-edge one. [1/30/2022 Amir]
			auto edgeEdge = std::dynamic_pointer_cast<Cad2d_EdgeEdgeIntersection>(x);
			Debug_Null_Pointer(edgeEdge);

			Debug_Null_Pointer(edgeEdge->Edge0());
			Debug_Null_Pointer(edgeEdge->Edge1());

			const auto& edge0 = *edgeEdge->Edge0();
			const auto& edge1 = *edgeEdge->Edge1();

			{// register edge0 [1/30/2022 Amir]
				auto paired = std::make_pair(edge0.Index(), edgeEdge->Edge0());
				auto insert = allEdges.insert(std::move(paired));
				if (NOT insert.second)
				{
					// do nothing! the edge is already registered. [1/30/2022 Amir]
				}
			}

			{// register edge1 [1/30/2022 Amir]
				auto paired = std::make_pair(edge1.Index(), edgeEdge->Edge1());
				auto insert = allEdges.insert(std::move(paired));
				if (NOT insert.second)
				{
					// do nothing! the edge is already registered. [1/30/2022 Amir]
				}
			}

			const auto& pairList = edgeEdge->Entities();
			for (const auto& pair : pairList)
			{
				Debug_Null_Pointer(pair);

				auto ent0 = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Segment>(pair->Entity0());
				Debug_Null_Pointer(ent0);

				auto ent1 = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Segment>(pair->Entity1());
				Debug_Null_Pointer(ent1);

				insert_to_map(edge0.Index(), std::move(ent0), entities);
				insert_to_map(edge1.Index(), std::move(ent1), entities);
			}
		}
	}

	// Now, we have all intersection entities in the form of edge-edge type. [1/30/2022 Amir]
	//
	// Subdivide the edges that have at least one intersection type.
	//


	// Register the sub curves with their sense conditions in a map. [1/30/2022 Amir]
	std::map<Standard_Integer, std::pair<std::vector<std::shared_ptr<Pln_Curve>>, Standard_Boolean>> subCurves;
	for (const auto& x : allEdges)
	{
		Debug_Null_Pointer(x.second);
		const auto& e = x.second;

		auto iter = entities.find(e->Index());
		if (iter IS_EQUAL entities.end())
		{
			FatalErrorIn(FunctionSIG)
				<< "cannot find the item!" << endl
				<< abort(FatalError);
		}

		Debug_Null_Pointer(iter->second);
		auto& l = *iter->second;

		// Sort the entities based on their parameters [1/30/2022 Amir]
		Cad2d_IntsctEntity_Segment::SortEntities(l);

		// Subdivide the edge [1/30/2022 Amir]
		auto newCurves = Cad2d_IntsctEntity_Segment::SubdivideEdge(e, l, Tolerance());

		// if the sense of the parent edge is false, the order of the sub-curves will be reversed. [1/30/2022 Amir]
		if (NOT e->Sense())
		{
			std::reverse(newCurves.begin(), newCurves.end());
		}

		auto sense = e->Sense();
		auto paired0 = std::make_pair(std::move(newCurves), std::move(sense));

		auto id = e->Index();
		auto paired = std::make_pair(std::move(id), std::move(paired0));
		auto insert = subCurves.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "Something went wrong! duplicate data is detected." << endl
				<< abort(FatalError);
		}
	}

	std::map<Standard_Integer, std::vector<std::shared_ptr<Pln_Edge>>> subEdges;
	for (const auto& x : subCurves)
	{
		auto id = x.first;
		auto[subs, sense] = x.second;

		auto newEdges = Pln_Tools::RetrieveEdges(subs);
		auto paired = std::make_pair(id, std::move(newEdges));
		auto insert = subEdges.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "Something went wrong! duplicate data is detected." << endl
				<< abort(FatalError);
		}
	}

	SubEdgesRef() = std::move(subEdges);
	Change_IsDone() = Standard_True;
}