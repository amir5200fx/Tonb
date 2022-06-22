#include <Aft2d_tBoundaryOfPlaneSurface.hxx>

#include <Aft2d_tPlnWireSurface.hxx>
#include <Aft2d_tPlnCurveSurface.hxx>
#include <Aft2d_tPlnWireSurface.hxx>
#include <Aft2d_tSegmentGapEdge.hxx>
#include <Cad_tPoleSingularCurve.hxx>
#include <Cad_tLineSingularCurve.hxx>
#include <Cad_tPlnGapCurve.hxx>
#include <Global_Macros.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

unsigned short tnbLib::Aft2d_tBoundaryOfPlaneSurface::verbose(0);

#include <Aft_Tools.hxx>
#include <Aft2d_MetricPrcsrSurface.hxx>

#ifdef _DEBUG
template<>
void tnbLib::Aft2d_tBoundaryOfPlaneSurface::RemoveDegeneracies()
{
	auto& boundaries = ChangeBoundaries();
	std::vector<std::shared_ptr<bndType>> modified;
	modified.reserve(boundaries.size());

	Standard_Boolean contracted = Standard_False;
	for (const auto& x : boundaries)
	{
		Debug_Null_Pointer(x);
		if (x->IsSingular())
		{
			if (NOT x->SingularityContraction(*MetricProcessor()))
			{
				modified.push_back(x);
			}
			else
			{
				if (NOT contracted) contracted = Standard_True;
			}
		}
		else if (x->IsGap())
		{
			auto gapEdge = std::dynamic_pointer_cast<Aft2d_tSegmentGapEdge>(x);
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
	boundaries = modified;

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
void tnbLib::Aft2d_tBoundaryOfPlaneSurface::Perform()
{
	if (verbose)
	{
		tnbLib::Info << endl
			<< "****** Meshing the boundaries ******" << endl << endl;
	}

	if (NOT MetricProcessor())
	{
		FatalErrorIn("void Aft_PlnBoundary<RegionType, SizeFun, MetricFun>::Perform()")
			<< " no metric processor has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Plane())
	{
		FatalErrorIn("void Aft_PlnBoundary<RegionType, SizeFun, MetricFun>::Perform()")
			<< " no plane has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Info())
	{
		FatalErrorIn("void Aft_PlnBoundary<RegionType, SizeFun, MetricFun>::Perform()")
			<< " no info has been loaded!" << endl
			<< abort(FatalError);
	}

	if (verbose)
	{
		tnbLib::Info << " Retrieving the wires..." << endl;
	}

	std::vector<std::shared_ptr<Aft2d_tPlnWireSurface>> wires;
	Plane()->RetrieveWiresTo(wires);
	if (wires.empty())
	{
		FatalErrorIn("void Aft_PlnBoundary<RegionType, SizeFun, MetricFun>::Perform()")
			<< " Invalid plane: wire list is empty" << endl
			<< abort(FatalError);
	}

	if (verbose)
	{
		tnbLib::Info << " - nb. of wires: " << wires.size() << endl << endl;
	}

	const auto& infoMap = Info()->Curve();
	auto& boundaries = ChangeBoundaries();
	Standard_Integer Ke = 0;
	Standard_Integer Kn = 0;

	Standard_Boolean Checked = Standard_False;

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

		std::vector<std::shared_ptr<bndType>> Medges;

		std::vector<Entity2d_Box> wBoxes;
		const auto& curves = wire->Curves();
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

			std::vector<std::shared_ptr<Aft2d_tSegmentEdge>> mesh;
			//mesh = Aft2d_gPlnCurveSurface::TopoMesh<bndType>(x, MetricProcessor(), currentInfo);
			if (x->IsSingular())
			{
				auto singCurve = std::dynamic_pointer_cast<Cad_tSingularCurve>(x);
				Debug_Null_Pointer(singCurve);

				if (singCurve->IsPole())
				{
					mesh = Cad_tPoleSingularCurve::TopoMesh<bndType>(x, MetricProcessor(), currentInfo);
				}
				else if (singCurve->IsLine())
				{
					mesh = Cad_tLineSingularCurve::TopoMesh<bndType>(x, MetricProcessor(), currentInfo);
				}
				else
				{
					FatalErrorIn(FunctionSIG)
						<< "invalid data has been detected!" << endl
						<< abort(FatalError);
				}
			}
			else if (x->IsGap())
			{
				mesh = Cad_tPlnGapCurve::TopoMesh<bndType>(x, MetricProcessor(), currentInfo);
			}
			else
			{
				mesh = Aft2d_tPlnCurveSurface::TopoMesh<bndType>(x, MetricProcessor(), currentInfo);
			}

			if (verbose)
			{
				tnbLib::Info << "   Discretization is done!" << endl;
			}
			auto nodes = bndType::RetrieveNodes(bndType::UpCast(mesh));
			auto box = Entity2d_Box::BoundingBoxOf(bndType::nodeType::RetrieveGeometry(nodes));

			wBoxes.push_back(std::move(box));

			for (const auto& edge : mesh)
			{
				Debug_Null_Pointer(edge);
				Medges.push_back(edge);
			}
		}

		auto iter = wBoxes.begin();
		auto wBox = *iter;
		iter++;
		while (iter NOT_EQUAL wBoxes.end())
		{
			wBox = Entity2d_Box::Union(wBox, *iter);
			iter++;
		}

		boxes.push_back(wBox);

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

		bndType::MergeDangles(Medges, Info()->MergeTolerance());

		for (const auto& x : Medges)
		{
			Debug_Null_Pointer(x);
			boundaries.push_back(x);
		}

		for (auto& x : Medges)
		{
			Debug_Null_Pointer(x);
			auto& n0 = x->Node0();

			n0->SetIndex(++Kn);
		}

		if (verbose)
		{
			tnbLib::Info << " Checking the min. nb. of the points in a wire: ";
		}
		if (base::CheckWireNbPts(Medges))
		{
			base::SetNbPtsCheck(Standard_True);
			Checked = Standard_True;

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
		if (base::CheckSimplicity(Medges))
		{
			base::SetSimpleCheck(Standard_True);
			Checked = Standard_True;

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
			if (base::CheckWireOrientation(Medges, Standard_True))
			{
				base::SetOrientCheck(Standard_True);
				Checked = Standard_True;

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
			if (base::CheckWireOrientation(Medges, Standard_False))
			{
				base::SetOrientCheck(Standard_True);
				Checked = Standard_True;

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
			base::SetInnerCheck(Standard_True);
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

	bndType::ActiveBoundaryEdges(bndType::UpCast(boundaries));

	/*if (NOT Checked)
	{
		RemoveDegeneracies();
	}*/

	RemoveDegeneracies();

	if (verbose)
	{
		tnbLib::Info << endl;
		tnbLib::Info << " Updating the front..." << endl;
	}
	UpdateFront();

	base::Change_IsDone() = Standard_True;

	if (verbose)
	{
		tnbLib::Info << endl
			<< "****** End of the Meshing the boundaries ******" << endl << endl;
	}
}
#endif // _DEBUG

template<>
void tnbLib::Aft2d_tBoundaryOfPlaneSurface::UpdateFront()
{
	Debug_Null_Pointer(MetricProcessor());
	auto sizeMapPtr = std::dynamic_pointer_cast<Aft2d_MetricPrcsrSurface>(MetricProcessor());
	Debug_Null_Pointer(sizeMapPtr);
	const auto& sizeMap = *sizeMapPtr;

	const auto& boundaries = Boundaries();
	std::vector<std::shared_ptr<Aft2d_NodeSurface>> nodes =
		Aft_Tools::RetrieveNodes(Aft2d_tSegmentEdge::UpCast(boundaries));
	for (const auto& x : nodes)
	{
		auto pt = sizeMap.CalcCoord3D(x->Coord());
		x->SetCoord3D(std::move(pt));
	}

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