#include <PlnOpert_SplitWire.hxx>

#include <Geo_BinSearch.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Wire.hxx>
#include <PlnOpert_IntsctEntity.hxx>
#include <PlnOpert_IntsctPoint.hxx>
#include <PlnOpert_IntsctPair.hxx>
#include <PlnOpert_IntsctSegment.hxx>
#include <PlnOpert_SplitWire_Info.hxx>
#include <PlnOpert_IntsctCurveCurve_Info.hxx>
#include <PlnOpert_IntsctCurveCurve.hxx>

#include <list>

namespace tnbLib
{
	typedef std::map
		<
		Standard_Integer,
		std::shared_ptr<std::list<std::shared_ptr<PlnOpert_IntsctEntity>>>
		>
		intersectMap;

	void PushToMap
	(
		const Standard_Integer theIndex,
		const std::shared_ptr<PlnOpert_IntsctEntity>& theEntity, 
		intersectMap& theMap
	)
	{
		auto iter = theMap.find(theIndex);
		if (iter IS_EQUAL theMap.end())
		{
			theMap.insert
			(
				std::make_pair
				(
					theIndex,
					std::make_shared<std::list<std::shared_ptr<PlnOpert_IntsctEntity>>>()
				));		
		}
		else
		{
			iter->second->push_back(theEntity);
		}
	}

	bool CompareEntities
	(
		const std::shared_ptr<PlnOpert_IntsctEntity>& theEnt0,
		const std::shared_ptr<PlnOpert_IntsctEntity>& theEnt1
	)
	{
		Debug_Null_Pointer(theEnt0);
		Debug_Null_Pointer(theEnt1);

		return theEnt0->CharParameter() < theEnt1->CharParameter();
	}

	std::vector<std::shared_ptr<Pln_Edge>> 
		Subdivide
		(
			const std::shared_ptr<Pln_Curve>& theCurve, 
			std::list<std::shared_ptr<PlnOpert_IntsctEntity>>& theEntities
		)
	{
		theEntities.sort(CompareEntities);
		theEntities.sort();

		std::vector<Standard_Real> params;
		for (const auto& x : theEntities)
		{
			if (x->IsPoint())
			{
				params.push_back(x->CharParameter());
			}
			else
			{
				auto seg = std::dynamic_pointer_cast<PlnOpert_IntsctSegment>(x);
				Debug_Null_Pointer(seg);

				params.push_back(seg->Parameter0());
				params.push_back(seg->Parameter1());
			}
		}

		auto curves = theCurve->Split(params);

		std::vector<std::shared_ptr<Pln_Vertex>> vertices;
		vertices.reserve(curves.size()*2);
		for (const auto& x : curves)
		{
			Debug_Null_Pointer(x);
			vertices.push_back(std::make_shared<Pln_Vertex>(0, x->FirstCoord()));
			vertices.push_back(std::make_shared<Pln_Vertex>(0, x->LastCoord()));
		}

		std::vector<std::shared_ptr<Pln_Edge>> edges;
		edges.reserve(curves.size());

		Standard_Integer k = 0;
		for (const auto& x : curves)
		{
			Debug_Null_Pointer(x);
			auto edge = std::make_shared<Pln_Edge>(vertices[2 * k], vertices[2 * k + 1], x);

			++k;

			edges.push_back(edge);
		}
		return std::move(edges);
	}

	std::map<Standard_Integer, std::pair<std::shared_ptr<Pln_Vertex>, Standard_Real>>
		IntersectionWithVertices
		(
			const std::vector<std::shared_ptr<Pln_Vertex>>& theVertices, 
			const Handle(Geom2d_Curve)& theCurve
		)
	{
		std::map<Standard_Integer, std::pair<std::shared_ptr<Pln_Vertex>, Standard_Real>>
			intVertMap;

		for (const auto& x : theVertices)
		{
			Standard_Real param;
			if (Pln_Tools::Distance(x->Coord(), theCurve, param) <= x->Precision())
			{
				auto insert = intVertMap.insert(std::make_pair(x->Index(), std::make_pair(x, param)));
				if (NOT insert.second)
				{
					FatalErrorIn("void Perform()")
						<< "Unable to insert the vertex to the map!" << endl
						<< abort(FatalError);
				}
			}
		}
		return std::move(intVertMap);
	}

}

void tnbLib::PlnOpert_SplitWire::Perform()
{
	if (NOT Wire())
	{
		FatalErrorIn("void Perform()")
			<< "the wire is not loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Cutter())
	{
		FatalErrorIn("void Perform()")
			<< "the cutter is not loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Info())
	{
		FatalErrorIn("void Perform()")
			<< "the info is not loaded!" << endl
			<< abort(FatalError);
	}

	intersectMap entCurves;
	std::list<std::shared_ptr<PlnOpert_IntsctEntity>> entCutter;

	auto vertices = Wire()->RetrieveVertices();

	//- find the vertices which have intersection with the cutter and put them into a map
	auto intVertxMap = 
		IntersectionWithVertices(vertices, Cutter()->Geometry());

	Standard_Integer nbIntsct = 0;
	//- the edges connected to these vertices have an intersection with the cutter at 
	//- these points
	for (const auto& x : intVertxMap)
	{
		const auto& paired = x.second;
		
		const auto& vtx = paired.first;
		const auto param = paired.second;

		Debug_Null_Pointer(vtx);
		Debug_If_Condition_Message
		(
			NOT vtx->IsManifold(),
			"Invalid data: the wire is not manifold!");

		std::vector<std::weak_ptr<Pln_Edge>> edges;
		vtx->RetrieveEdgesTo(edges);

		auto e0 = edges[0].lock();
		auto ent0 = 
			std::make_shared<PlnOpert_IntsctPoint>
			(
				0,
				vtx->Coord(), e0->Parameter(e0->Index(vtx)));

		auto e1 = edges[1].lock();
		auto ent1 = 
			std::make_shared<PlnOpert_IntsctPoint>
			(
				0, 
				vtx->Coord(), e1->Parameter(e1->Index(vtx)));

		auto cutter = 
			std::make_shared<PlnOpert_IntsctPoint>(0, vtx->Coord(), param);

		entCutter.push_back(cutter);

		PushToMap(e0->Index(),)
	}

	

	const auto& edges = Wire()->Edges();
	const auto& domain = Wire()->BoundingBox();
	
	auto intersection = 
		std::make_shared<PlnOpert_IntsctCurveCurve>(Info()->IntsctInfo());
	intersection->LoadCurve0(Cutter());

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		intersection->LoadCurve1(x->Curve());

		intersection->Perform();
		Debug_If_Condition_Message
		(
			NOT intersection->IsDone(), 
			"the intersection algorithm is not performed!"
		);

		if (NOT intersection->HasIntersection())
			continue;

		const auto& entities = intersection->Entities();
		for (const auto& ent : entities)
		{
			entCutter.push_back(ent->Entity0());

			PushToMap(x->Index(), ent->Entity1(), entCurves);
		}
	}


}