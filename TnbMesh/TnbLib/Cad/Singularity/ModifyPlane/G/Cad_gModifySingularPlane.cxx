#include <Cad_gModifySingularPlane.hxx>

#include <Cad_ModifySingularPlaneTools.hxx>
#include <Cad_SingularityTopology.hxx>
#include <Cad_ColorApprxMetric.hxx>

#include <TecPlot.hxx>

#ifdef _DEBUG

template<>
void tnbLib::Cad_gModifySingularPlane::RemoveColoredEdges
(
	Cad_SingularityTopology<GModel_Surface>& theTopo, 
	const Cad_ColorApprxMetric & theColors, 
	const Cad_SingularityTopology<GModel_Surface>::edgeToCurveMap & theEdgeToCurve, 
	const std::map<std::shared_ptr<Aft2d_gPlnCurveSurface>, Cad_ModifySingularPlaneToolsBase::pCurveType>& theMap, 
	std::map<std::shared_ptr<Geo_TopoChainAnalysis_Entity<Geo2d_SegmentGraphEdge>>, Standard_Integer>& theColored
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

template<>
void tnbLib::Cad_gModifySingularPlane::Perform()
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
		Cad_ModifySingularPlaneTools<Aft2d_gRegionPlaneSurface>::RetrieveCurves(wires);
	auto subsList =
		Cad_ModifySingularPlaneTools<Aft2d_gRegionPlaneSurface>::CalcParts(Zones(), bcurves);
	auto subMap = Cad_SubdivideHorizon<Aft2d_gPlnCurveSurface>::Merge(subsList);

	auto horizonCurves =
		Cad_SingularZone<Aft2d_gRegionPlaneSurface>::RetrieveHorizons(Zones());

	auto modifiedWires =
		Cad_ModifySingularPlaneTools<Aft2d_gRegionPlaneSurface>::ModifyWires(wires, subMap, Tolerance());

	auto modifiedHorizons =
		Cad_ModifySingularPlaneTools<Aft2d_gRegionPlaneSurface>::ModifyHorizons(horizonCurves, subMap, 1.0E-12);

	auto curveTypes =
		Cad_ModifySingularPlaneTools<Aft2d_gRegionPlaneSurface>::CurveToTypeMap(modifiedHorizons, modifiedWires);
	auto wireApprox =
		Cad_ModifySingularPlaneTools<Aft2d_gRegionPlaneSurface>::GetPolygons(modifiedWires, ApproxInfo());

	RegisterPolygons(wireApprox);

	auto topology =
		std::make_shared<Cad_SingularityTopology<GModel_Surface>>
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

			/*OFstream myFile("failed_chain.plt");
			std::vector<Pnt2d> mypoints;
			for (const auto& e : chain.Entities())
			{
				mypoints.push_back(e->Node0()->Coord());
				mypoints.push_back(e->Node1()->Coord());
			}
			Io::ExportCurve(mypoints, myFile);*/
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
#endif // _DEBUG
