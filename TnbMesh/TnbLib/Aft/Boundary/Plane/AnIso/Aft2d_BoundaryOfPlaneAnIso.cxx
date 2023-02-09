#include <Aft2d_BoundaryOfPlaneAnIso.hxx>

#include <Geo_BoxTools.hxx>
#include <Pln_Curve.hxx>
#include <Aft2d_SegmentEdgeAnIso.hxx>
#include <Aft2d_PlnWireAnIso.hxx>
#include <Aft2d_PlnCurveAnIso.hxx>
#include <Aft2d_BoundaryOfPlane_Info.hxx>
#include <Aft2d_RegionPlaneAnIso.hxx>
#include <Aft2d_GapEdgeTemplate.hxx>
#include <Aft_Tools.hxx>
#include <Cad2d_PlnGapCurveAnIso.hxx>
#include <Geo2d_MetricPrcsr.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Geo2d_MetricPrcsrUniMetric.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

unsigned short tnbLib::Aft2d_BoundaryOfPlaneAnIso::verbose(0);

#ifdef _DEBUG
template<>
void tnbLib::Aft2d_BoundaryOfPlaneAnIso::UpdateFront()
{
	Debug_Null_Pointer(MetricProcessor());
	const auto& sizeMap = *MetricProcessor();

	const auto& boundaries = ChangeBoundaries();
	for (const auto& x : boundaries)
	{
		Debug_Null_Pointer(x);
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();

		x->SetEffectiveMetric(sizeMap.CalcEffectiveMetric(n0->Coord(), n1->Coord()));
		x->SetCentre(sizeMap.CalcCentre(n0->Coord(), n1->Coord()));
		x->SetCharLength(sizeMap.CalcDistance(n0->Coord(), n1->Coord()));
	}

	for (const auto& x : boundaries)
	{
		Debug_Null_Pointer(x);

		auto n0 = std::dynamic_pointer_cast<typename bndType::bndNodeType>(x->Node0());
		Debug_Null_Pointer(n0);

		const auto& edges = n0->RetrieveBoundaryEdges();
		auto Iter = edges.begin();
		Debug_Null_Pointer(Iter->second.lock());
		auto M = Iter->second.lock()->EffectiveMetric();
		Iter++;

		while (Iter NOT_EQUAL edges.end())
		{
			Debug_Null_Pointer(Iter->second.lock());
			const auto& Mi = Iter->second.lock()->EffectiveMetric();
			if (M.Determinant() < Mi.Determinant())
			{
				M = Entity2d_Metric1::UnionSR(M, Mi);
			}
			else
			{
				M = Entity2d_Metric1::UnionSR(Mi, M);
			}
			Iter++;
		}

		n0->SetMetric(M);
	}
}
#endif // _DEBUG

template<>
void tnbLib::Aft2d_BoundaryOfPlaneAnIso::RemoveDegeneracies()
{
	auto& boundaries = ChangeBoundaries();
	std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>> modified;
	modified.reserve(boundaries.size());

	Standard_Boolean contracted = Standard_False;
	for (const auto& x : boundaries)
	{
		Debug_Null_Pointer(x);
		if (x->IsGap())
		{
			auto gapEdge = std::dynamic_pointer_cast<Aft2d_GapEdgeTemplate<Aft2d_SegmentEdgeAnIso>>(x);
			Debug_Null_Pointer(gapEdge);

			gapEdge->Contraction(*MetricProcessor());

			if (NOT contracted) contracted = Standard_True;
		}
		else
		{
			modified.push_back(x);
		}
	}

	if (NOT contracted) return;

	modified.shrink_to_fit();
	boundaries = std::move(modified);

	Standard_Integer Ke = 0;
	Standard_Integer Kn = 0;
	for (const auto& x : boundaries)
	{
		Debug_Null_Pointer(x);
		x->SetIndex(++Ke);
		x->Node0()->SetIndex(++Kn);
	}
}

template<>
void tnbLib::Aft2d_BoundaryOfPlaneAnIso::Perform()
{
	if (verbose)
	{
		tnbLib::Info << endl
			<< "****** Meshing the boundaries ******" << endl << endl;
	}

	if (NOT MetricProcessor())
	{
		FatalErrorIn(FunctionSIG)
			<< "no metric processor has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Plane())
	{
		FatalErrorIn(FunctionSIG)
			<< " no plane has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Info())
	{
		FatalErrorIn(FunctionSIG)
			<< " no info has been loaded!" << endl
			<< abort(FatalError);
	}

	if (verbose)
	{
		tnbLib::Info << " Retrieving the wires..." << endl;
	}

	std::vector<std::shared_ptr<typename Aft2d_RegionPlaneAnIso::plnWireType>> wires;
	Plane()->RetrieveWiresTo(wires);
	if (wires.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid plane has been detected: the wire list is empty!" << endl
			<< abort(FatalError);
	}

	if (verbose)
	{
		tnbLib::Info << " - nb. of wires: " << wires.size() << endl << endl;
	}

	const auto& infoMap = Info()->Curve();
	auto& boundaries = this->ChangeBoundaries();

	Standard_Integer Ke = 0;
	Standard_Integer Kn = 0;

	std::vector<Entity2d_Box> boxes;
	boxes.reserve(wires.size());

	for (const auto& wire : wires)
	{
		if (verbose)
		{
			tnbLib::Info << " - wire's name: "
				<< wire->Name()
				<< ", index: "
				<< wire->Index()
				<< endl << endl;
		}

		Debug_Null_Pointer(wire);

		std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>> Medges;

		std::vector<Entity2d_Box> wBoxes;
		const std::vector<std::shared_ptr<Aft2d_PlnCurveAnIso>>& curves = wire->Curves();
		wBoxes.reserve(curves.size());

		if (verbose)
		{
			tnbLib::Info << " - nb. of curves: " << curves.size() << endl << endl;
		}
		for (const auto& x : curves)
		{
			Debug_Null_Pointer(x);

			Debug_Null_Pointer(Info()->GlobalCurve());
			auto currentInfo = Info()->GlobalCurve();

			Standard_Boolean overrideInfo = Standard_False;
			if (Info()->OverrideInfo() AND infoMap.size())
			{
				auto iter = infoMap.find(x->Index());

				if (iter NOT_EQUAL infoMap.end())
				{
					currentInfo = iter->second;
					overrideInfo = Standard_True;
				}
			}

			if (verbose)
			{
				tnbLib::Info << " - curve no. " << x->Index() << "." << endl;
				tnbLib::Info << "   Using local info: " << (overrideInfo ? "YES." : "NO.") << endl;
			}

			if (verbose)
			{
				tnbLib::Info << "   Discretizing..." << endl;
			}
			std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>> mesh;
			if (x->IsGap())
			{
				mesh = Cad2d_PlnGapCurveAnIso::TopoMesh<Aft2d_SegmentEdgeAnIso>(x, MetricProcessor(), currentInfo);
			}
			else
			{
				mesh = Aft_Tools::RetrieveTopoMesh(x, MetricProcessor(), currentInfo);
			}

			if (verbose)
			{
				tnbLib::Info << "   Discretization is done!" << endl;
			}
			auto nodes = Aft_Tools::RetrieveNodes(Aft_Tools::UpCast(mesh));
			auto box = Geo_BoxTools::GetBox(Aft_Tools::RetrieveGeometry(nodes), 0.0);

			wBoxes.push_back(std::move(box));

			for (const auto& edge : mesh)
			{
				Debug_Null_Pointer(edge);
				Medges.push_back(std::move(edge));
			}
		}

		auto iter = wBoxes.begin();
		auto wBox = *iter;
		iter++;
		while (iter NOT_EQUAL wBoxes.end())
		{
			wBox = Geo_BoxTools::Union(wBox, *iter);
			iter++;
		}

		boxes.push_back(std::move(wBox));

		for (auto& x : Medges)
		{
			Debug_Null_Pointer(x);
			x->SetIndex(++Ke);
		}

		if (verbose)
		{
			tnbLib::Info << endl;
			tnbLib::Info << " Merging the edges..." << endl;
			tnbLib::Info << " - Tolerance: " << Info()->MergeTolerance() << endl << endl;
		}

		Aft_Tools::MergeDangles(Medges, Info()->MergeTolerance());

		for (const auto& x : Medges)
		{
			Debug_Null_Pointer(x);
			boundaries.push_back(std::move(x));
		}

		for (const auto& x : boundaries)
		{
			Debug_Null_Pointer(x);
			auto& n0 = x->Node0();

			n0->SetIndex(++Kn);
		}

		if (verbose)
		{
			tnbLib::Info << " Checking the min. nb. of the points in a wire: ";
		}
		if (CheckWireNbPts(boundaries))
		{
			SetNbPtsCheck(Standard_True);
			//Checked = Standard_True;

			if (verbose)
			{
				tnbLib::Info << " NO!" << endl;
			}
			continue;
		}
		else
		{
			if (verbose)
			{
				tnbLib::Info << " OK!" << endl;
			}
		}

		if (verbose)
		{
			tnbLib::Info << " Checking the simplicity of the wire: ";
		}
		if (CheckSimplicity(boundaries))
		{
			SetSimpleCheck(Standard_True);
			//Checked = Standard_True;

			if (verbose)
			{
				tnbLib::Info << " NO!" << endl;
			}
			continue;
		}
		else
		{
			if (verbose)
			{
				tnbLib::Info << " OK!" << endl;
			}
		}

		if (verbose)
		{
			tnbLib::Info << " Checking the wire orientation: ";
		}
		if (wires[0] IS_EQUAL wire)
		{
			if (CheckWireOrientation(boundaries, Standard_True))
			{
				SetOrientCheck(Standard_True);
				//Checked = Standard_True;
				if (verbose)
				{
					tnbLib::Info << " NO!" << endl;
				}
			}
			else
			{
				if (verbose)
				{
					tnbLib::Info << " OK!" << endl;
				}
			}
		}
		else
		{
			if (CheckWireOrientation(boundaries, Standard_False))
			{
				SetOrientCheck(Standard_True);
				//Checked = Standard_True;
				if (verbose)
				{
					tnbLib::Info << " NO!" << endl;
				}
			}
			else
			{
				if (verbose)
				{
					tnbLib::Info << " OK!" << endl;
				}
			}
		}
	}

	auto iter = boxes.begin();
	auto box0 = *iter;
	iter++;

	if (verbose)
	{
		tnbLib::Info << " Checking the inner wires: ";
	}
	Standard_Boolean innerWireCheck = Standard_False;
	while (iter NOT_EQUAL boxes.end())
	{
		if (NOT Entity2d_Box::IsInside(iter->OffSet(1.0E-4), box0))
		{
			SetInnerCheck(Standard_True);
			innerWireCheck = Standard_True;
			break;
		}
		iter++;
	}

	if (innerWireCheck)
	{
		if (verbose)
		{
			tnbLib::Info << " NO!" << endl;
		}
	}
	else
	{
		if (verbose)
		{
			tnbLib::Info << " OK!" << endl;
		}
	}

	if (verbose)
	{
		tnbLib::Info << endl;
		tnbLib::Info << " Activating the boundary edges..." << endl;
	}

	Aft_Tools::ActiveBoundaryEdges(boundaries);

	RemoveDegeneracies();

	if (verbose)
	{
		tnbLib::Info << endl;
		tnbLib::Info << " Updating the front..." << endl;
	}
	UpdateFront();

	Change_IsDone() = Standard_True;

	if (verbose)
	{
		tnbLib::Info << endl
			<< "****** End of the Meshing the boundaries ******" << endl << endl;
	}
}