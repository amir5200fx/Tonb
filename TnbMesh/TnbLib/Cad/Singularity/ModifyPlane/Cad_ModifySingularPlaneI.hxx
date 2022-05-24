#pragma once
#ifndef _DEBUG
#include <Cad_ModifySingularPlaneTools.hxx>
#endif //_DEBUG
#include <Cad_SingularityTopology.hxx>
#include <Cad_ColorApprxMetric.hxx>

template<class SurfType>
inline void tnbLib::Cad_ModifySingularPlane<SurfType>::RegisterPolygons
(
	const std::vector<std::shared_ptr<Entity2d_Polygon>>& theWires
)
{
	Cad_ModifySingularPlaneBase::Reserve(theWires.size());
	for (const auto& x : theWires)
	{
		Debug_Null_Pointer(x);
		Cad_ModifySingularPlaneBase::RegisterPolygon(*x);
	}
}

template<class SurfType>
inline std::shared_ptr<typename tnbLib::Cad_ModifySingularPlane<SurfType>::parWireType> 
tnbLib::Cad_ModifySingularPlane<SurfType>::GetWire
(
	const Geo2d_TopoChainAnalysis::entityType & theEnt, 
	const typename Cad_SingularityTopology<SurfType>::edgeToCurveMap & theEdgeToCurve
)
{
	const auto& l = theEnt.Entities();
	std::vector<std::shared_ptr<parCurveType>> curves;
	curves.reserve(l.size());
	for (const auto& x : l)
	{
		Debug_Null_Pointer(x);
		auto iter = theEdgeToCurve.find(x);
		if (iter IS_EQUAL theEdgeToCurve.end())
		{
			FatalErrorIn(FunctionSIG)
				<< "unable to find the edge" << endl
				<< abort(FatalError);
		}
		curves.push_back(iter->second);
	}
	parWireType::OrientSingularCurves(curves);
	Standard_Integer k = 0;
	for (const auto& x : curves)
	{
		Debug_Null_Pointer(x);
		x->SetIndex(++k);
	}
	auto wire = std::make_shared<parWireType>(std::move(curves));
	return std::move(wire);
}

template<class SurfType>
inline std::vector<std::shared_ptr<typename tnbLib::Cad_ModifySingularPlane<SurfType>::plnType>> 
tnbLib::Cad_ModifySingularPlane<SurfType>::FormNewPlanes
(
	const std::vector<std::shared_ptr<Geo2d_TopoChainAnalysis::entityType>>& theOuters, 
	const std::vector<std::shared_ptr<Geo2d_TopoChainAnalysis::entityType>>& theInners,
	const typename Cad_SingularityTopology<SurfType>::edgeToCurveMap & theEdgeToCurve
)
{
	std::vector<std::shared_ptr<parWireType>> outerWires;
	std::vector<std::shared_ptr<parWireType>> innerWires;
	outerWires.reserve(theOuters.size());
	innerWires.reserve(theInners.size());

	for (const auto& x : theOuters)
	{
		Debug_Null_Pointer(x);
		auto wire = GetWire(*x, theEdgeToCurve);
		outerWires.push_back(std::move(wire));
	}

	for (const auto& x : theInners)
	{
		Debug_Null_Pointer(x);
		auto wire = GetWire(*x, theEdgeToCurve);
		innerWires.push_back(std::move(wire));
	}

	std::vector<Entity2d_Box> outerBoxes;
	outerBoxes.reserve(outerWires.size());
	for (const auto& x : outerWires)
	{
		Debug_Null_Pointer(x);
		auto b = x->CalcParametricBoundingBox();
		outerBoxes.push_back(std::move(b));
	}

	std::map<std::shared_ptr<parWireType>, std::shared_ptr<parWireType>>
		innerToOuter;
	for (const auto& x : innerWires)
	{
		Debug_Null_Pointer(x);
		const auto b = x->CalcParametricBoundingBox();

		Standard_Boolean found = Standard_False;
		for (size_t i = 0; i < outerBoxes.size(); i++)
		{
			if (Entity2d_Box::IsInside(b, outerBoxes.at(i)))
			{
				auto paired = std::make_pair(x, outerWires.at(i));
				auto insert = innerToOuter.insert(std::move(paired));
				if (NOT insert.second)
				{
					FatalErrorIn(FunctionSIG)
						<< "duplicate data has been found." << endl
						<< abort(FatalError);
				}

				found = Standard_True;
				break;
			}
		}
		if (NOT found)
		{
			FatalErrorIn(FunctionSIG)
				<< "unable to locate an inner wire to an outer one!" << endl
				<< abort(FatalError);
		}
	}

	std::map<std::shared_ptr<parWireType>, std::shared_ptr<std::vector<std::shared_ptr<parWireType>>>>
		outerToInners;
	for (const auto& x : outerWires)
	{
		auto l = std::make_shared<std::vector<std::shared_ptr<parWireType>>>();
		auto paired = std::make_pair(x, std::move(l));
		auto insert = outerToInners.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate data has been detected!" << endl
				<< abort(FatalError);
		}
	}

	for (const auto& x : innerToOuter)
	{
		const auto& outer = x.second;
		Debug_Null_Pointer(outer);

		auto iter = outerToInners.find(outer);
		if (iter IS_EQUAL outerToInners.end())
		{
			FatalErrorIn(FunctionSIG)
				<< "the item is not in the map!" << endl
				<< abort(FatalError);
		}
		iter->second->push_back(x.first);
	}

	std::vector<std::shared_ptr<plnType>> planes;
	planes.reserve(outerToInners.size());

	Standard_Integer k = 0;
	for (const auto& x : outerToInners)
	{
		const auto& outer = x.first;
		const auto& l = x.second;

		Debug_Null_Pointer(outer);
		Debug_Null_Pointer(x.second);

		auto plane = std::make_shared<plnType>(++k, "", nullptr, outer, l);
		planes.push_back(std::move(plane));
	}
	return std::move(planes);
}

template<class SurfType>
inline tnbLib::Pnt2d 
tnbLib::Cad_ModifySingularPlane<SurfType>::GetSample
(
	const Geo2d_TopoChainAnalysis::entityType & theEnt, 
	const typename Cad_SingularityTopology<SurfType>::edgeToCurveMap & theEdgeToCurve
)
{
	const auto& l = theEnt.Entities();
	if (l.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the list is empty!" << endl
			<< abort(FatalError);
	}
	const auto& x = l.front();
	
	auto iter = theEdgeToCurve.find(x);
	if (iter IS_EQUAL theEdgeToCurve.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(iter->second);
	const auto& curve = *iter->second;
	auto pt = curve.Value(MEAN(curve.FirstParameter(), curve.LastParameter()));
	return std::move(pt);
}

template<class SurfType>
inline Standard_Boolean 
tnbLib::Cad_ModifySingularPlane<SurfType>::IsOuterWire
(
	const Geo2d_TopoChainAnalysis::entityType & theEnt,
	const typename Cad_SingularityTopology<SurfType>::edgeToCurveMap & theEdgeToCurve,
	const std::map<std::shared_ptr<parCurveType>, Cad_ModifySingularPlaneToolsBase::pCurveType>& theType
)
{
	const auto& l = theEnt.Entities();
	for (const auto& x : l)
	{
		Debug_Null_Pointer(x);
		auto iter = theEdgeToCurve.find(x);
		if (iter IS_EQUAL theEdgeToCurve.end())
		{
			FatalErrorIn(FunctionSIG)
				<< "the item is not in the map" << endl
				<< abort(FatalError);
		}

		auto t = theType.find(iter->second);
		if (t IS_EQUAL theType.end())
		{
			FatalErrorIn(FunctionSIG)
				<< "the item is not in the map" << endl
				<< abort(FatalError);
		}

		if (t->second IS_EQUAL Cad_ModifySingularPlaneToolsBase::pCurveType::outerWire)
		{
			return Standard_True;
		}
	}
	return Standard_False;
}

template<class SurfType>
inline tnbLib::Cad_ModifySingularPlaneToolsBase::pCurveType 
tnbLib::Cad_ModifySingularPlane<SurfType>::RetrieveType
(
	const Geo2d_TopoChainAnalysis::entityType & theEnt, 
	const typename Cad_SingularityTopology<SurfType>::edgeToCurveMap & theEdgeToCurve, 
	const std::map<std::shared_ptr<parCurveType>, Cad_ModifySingularPlaneToolsBase::pCurveType>& theMap
)
{
	const auto& l = theEnt.Entities();
	if (l.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the list is empty!" << endl
			<< abort(FatalError);
	}

	const auto& x = l.front();
	auto iter = theEdgeToCurve.find(x);
	if (iter IS_EQUAL theEdgeToCurve.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the edge doesn't belong to the map!" << endl
			<< abort(FatalError);
	}

	auto t = theMap.find(iter->second);
	if (t IS_EQUAL theMap.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve doesn't belong to the map!" << endl
			<< abort(FatalError);
	}
	return t->second;
}

template<class SurfType>
inline void tnbLib::Cad_ModifySingularPlane<SurfType>::RemoveOutOfBoundaryHorizons
(
	Cad_SingularityTopology<SurfType>& theTopo,
	const Standard_Integer nbWires,
	const typename Cad_SingularityTopology<SurfType>::edgeToCurveMap & theEdgeToCurve, 
	const std::map<std::shared_ptr<parCurveType>, Cad_ModifySingularPlaneToolsBase::pCurveType>& theMap
)
{
	const auto& topo = theTopo.Topology();
	const auto& ents = topo->Entities();

	Standard_Boolean hasInner = nbWires > 1;

	std::vector<Standard_Integer> removeList;
	for (const auto& x : ents)
	{
		auto t = RetrieveType(*x.second, theEdgeToCurve, theMap);
		if (t IS_EQUAL Cad_ModifySingularPlaneToolsBase::pCurveType::horizon)
		{
			const auto pt = GetSample(*x.second, theEdgeToCurve);
			if (hasInner)
			{
				Standard_Boolean outside = Standard_False;
				if (NOT InsidePolygon(0, pt))
				{
					removeList.push_back(x.first);
					outside = Standard_True;
				}

				if (NOT outside)
				{
					for (Standard_Integer i = 1; i < nbWires; i++)
					{
						if (InsidePolygon(i, pt))
						{
							removeList.push_back(x.first);
							break;
						}
					}
				}
			}
			else
			{
				if (NOT InsidePolygon(0, pt))
				{
					removeList.push_back(x.first);
				}
			}
		}
	}

	if (removeList.empty())
	{
		return;
	}
	
	for (const auto x : removeList)
	{
		topo->DestroyEntity(x);
	}
}

#ifndef _DEBUG
template<class SurfType>
inline void tnbLib::Cad_ModifySingularPlane<SurfType>::RemoveColoredEdges
(
	Cad_SingularityTopology<SurfType>& theTopo,
	const Cad_ColorApprxMetric & theColors,
	const typename Cad_SingularityTopology<SurfType>::edgeToCurveMap & theEdgeToCurve,
	const std::map<std::shared_ptr<parCurveType>, Cad_ModifySingularPlaneToolsBase::pCurveType>& theMap,
	std::map<std::shared_ptr<Geo2d_TopoChainAnalysis::entityType>, Standard_Integer>& theColored
)
{
	const auto& topology = theTopo.Topology();

	Debug_Null_Pointer(topology);
	const auto& ents = topology->Entities();

	std::vector<Standard_Integer> removeList;
	for (const auto& x : ents)
	{

		auto t = RetrieveType(*x.second, theEdgeToCurve, theMap);
		if (t NOT_EQUAL Cad_ModifySingularPlaneToolsBase::pCurveType::horizon)
		{
			const auto pt = GetSample(*x.second, theEdgeToCurve);
			const auto color = theColors.Value(pt);

			if (color)
			{
				removeList.push_back(x.first);
			}
		}
	}

	if (removeList.empty())
	{
		return;
	}

	for (const auto x : removeList)
	{
		auto iter = ents.find(x);
		if (iter IS_EQUAL ents.end())
		{
			FatalErrorIn(FunctionSIG)
				<< "the item is not found!" << endl
				<< abort(FatalError);
		}
		auto pt = GetSample(*iter->second, theEdgeToCurve);
		auto color = theColors.Value(pt);

		auto ent = topology->deAttachEntity(iter->first);
		topology->RemoveFromRegistry(iter->first);

		auto paired = std::make_pair(std::move(ent), std::move(color));
		theColored.insert(std::move(paired));
	}
}
#endif // !_DEBUG


template<class SurfType>
inline Standard_Boolean 
tnbLib::Cad_ModifySingularPlane<SurfType>::IsZonesLoaded() const
{
	return NOT theZones_.empty();
}

template<class SurfType>
inline Standard_Boolean 
tnbLib::Cad_ModifySingularPlane<SurfType>::IsPlaneLoaded() const
{
	return (Standard_Boolean)thePlane_;
}

template<class SurfType>
inline Standard_Boolean 
tnbLib::Cad_ModifySingularPlane<SurfType>::IsColorsLoaded() const
{
	return (Standard_Boolean)theColors_;
}

template<class SurfType>
inline Standard_Boolean 
tnbLib::Cad_ModifySingularPlane<SurfType>::IsSurfaceLoaded() const
{
	return (Standard_Boolean)theSurface_;
}

template<class SurfType>
inline Standard_Boolean 
tnbLib::Cad_ModifySingularPlane<SurfType>::IsApproxInfoLoaded() const
{
	return (Standard_Boolean)theApproxInfo_;
}

#ifndef _DEBUG
template<class SurfType>
inline void tnbLib::Cad_ModifySingularPlane<SurfType>::Perform()
{
	if (NOT IsZonesLoaded())
	{
		FatalErrorIn("void Perform()") << endl
			<< "There are no horizons or have not been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT IsPlaneLoaded())
	{
		FatalErrorIn("void Perform()") << endl
			<< "The plane has not been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT IsColorsLoaded())
	{
		FatalErrorIn("void Perform()") << endl
			<< "The colors has not been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT IsSurfaceLoaded())
	{
		FatalErrorIn("void Perform()") << endl
			<< "The face has not been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT IsApproxInfoLoaded())
	{
		FatalErrorIn("void Perform()") << endl
			<< "The approximating info has not been loaded!" << endl
			<< abort(FatalError);
	}

	auto wires = RetrieveWires(*Plane());
	const auto bcurves =
		Cad_ModifySingularPlaneTools<plnType>::RetrieveCurves(wires);
	auto subsList =
		Cad_ModifySingularPlaneTools<plnType>::CalcParts(Zones(), bcurves);
	auto subMap = Cad_SubdivideHorizon<parCurveType>::Merge(subsList);

	auto horizonCurves =
		Cad_SingularZone<plnType>::RetrieveHorizons(Zones());

	auto modifiedWires =
		Cad_ModifySingularPlaneTools<plnType>::ModifyWires(wires, subMap, Tolerance());
	auto modifiedHorizons =
		Cad_ModifySingularPlaneTools<plnType>::ModifyHorizons(horizonCurves, subMap, 1.0E-12);

	auto curveTypes =
		Cad_ModifySingularPlaneTools<plnType>::CurveToTypeMap(modifiedHorizons, modifiedWires);
	auto wireApprox =
		Cad_ModifySingularPlaneTools<plnType>::GetPolygons(modifiedWires, ApproxInfo());

	RegisterPolygons(wireApprox);

	auto topology =
		std::make_shared<Cad_SingularityTopology<SurfType>>
		(modifiedWires, modifiedHorizons);
	Debug_Null_Pointer(topology);

	topology->Perform();
	Debug_If_Condition_Message(NOT topology->IsDone(), "the application is not performed!");

	const auto& edgeToCurve = topology->EdgeToCurveMap();

	// Removing the horizons that are outside of the domain
	RemoveOutOfBoundaryHorizons
	(
		*topology,
		(Standard_Integer)wireApprox.size(),
		edgeToCurve, curveTypes
	);

	std::map
		<
		std::shared_ptr<Geo2d_TopoChainAnalysis::entityType>,
		Standard_Integer
		> colored;
	RemoveColoredEdges
	(
		*topology,
		*theColors_,
		edgeToCurve,
		curveTypes, colored
	);

	const auto& zones = Zones();
	for (const auto& x : colored)
	{
		Debug_Null_Pointer(x.first);
		const auto& l = x.first;
		auto& zone = zones.at(Index_Of(x.second));

		for (const auto& e : l->Entities())
		{
			Debug_Null_Pointer(e);
			auto iter = edgeToCurve.find(e);
			if (iter IS_EQUAL edgeToCurve.end())
			{
				FatalErrorIn(FunctionSIG)
					<< "contradictory data: the edge has not been found!" << endl
					<< abort(FatalError);
			}

			const auto& curve = iter->second;
			zone->CurvesRef().push_back(curve);
		}
	}

	for (const auto& x : zones)
	{
		Debug_Null_Pointer(x);

		x->CreatePaired3d(*Surface());
		x->ProjectBoundariesToHorizons(*Surface());
	}

	const auto& dynLink = topology->Topology();
	Debug_Null_Pointer(dynLink);

	dynLink->reLink();

	std::vector<std::shared_ptr<Geo2d_TopoChainAnalysis::entityType>> outerWires;
	std::vector<std::shared_ptr<Geo2d_TopoChainAnalysis::entityType>> innerWires;
	const auto& ents = dynLink->Entities();
	for (const auto& x : ents)
	{
		Debug_Null_Pointer(x.second);
		const auto& chain = *x.second;

		if (NOT chain.IsRing())
		{
			FatalErrorIn(FunctionSIG)
				<< "the chain is not a ring!" << endl
				<< abort(FatalError);
		}

		if (IsOuterWire(chain, edgeToCurve, curveTypes))
		{
			outerWires.push_back(x.second);
		}
		else
		{
			innerWires.push_back(x.second);
		}
	}

	if (outerWires.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to form an outer wire!" << endl
			<< abort(FatalError);
	}

	auto modifieds = FormNewPlanes(outerWires, innerWires, edgeToCurve);
	for (const auto& x : modifieds)
	{
		Debug_Null_Pointer(x);
		x->SetPlane(Plane()->Plane());
	}

	ModifiedPlanesRef() = std::move(modifieds);

	Change_IsDone() = Standard_True;
}
#endif // !_DEBUG


template<class SurfType>
inline std::vector<std::shared_ptr<typename tnbLib::Cad_ModifySingularPlane<SurfType>::parWireType>> 
tnbLib::Cad_ModifySingularPlane<SurfType>::RetrieveWires
(
	const plnType & thePlane
)
{
	std::vector<std::shared_ptr<parWireType>> wires;
	wires.reserve(thePlane.NbHoles() + 1);
	const auto& outer = thePlane.Outer();
	if (NOT outer)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid plane has been detected!" << endl
			<< abort(FatalError);
	}
	wires.push_back(outer);
	if (thePlane.Inner())
	{
		for (const auto& x : *thePlane.Inner())
		{
			Debug_Null_Pointer(x);
			wires.push_back(x);
		}
	}
	return std::move(wires);
}