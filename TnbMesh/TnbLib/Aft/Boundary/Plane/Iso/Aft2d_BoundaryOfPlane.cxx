#include <Aft2d_BoundaryOfPlane.hxx>

#include <Geo_BoxTools.hxx>
#include <Pln_Curve.hxx>
#include <Aft2d_SegmentEdge.hxx>
#include <Aft2d_PlnWire.hxx>
#include <Aft2d_PlnCurve.hxx>
#include <Aft2d_BoundaryOfPlane_Info.hxx>
#include <Aft2d_RegionPlane.hxx>
#include <Aft_Tools.hxx>
#include <Cad2d_PlnGapCurve.hxx>
#include <Geo2d_MetricPrcsr.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Geo2d_MetricPrcsrUniMetric.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

unsigned short tnbLib::Aft2d_BoundaryOfPlane::verbose = 0;

void tnbLib::Aft2d_BoundaryOfPlane::UpdateFront()
{
	if (NOT MetricProcessor())
	{
		FatalErrorIn(FunctionSIG)
			<< "no metric processor has been loaded!" << endl
			<< abort(FatalError);
	}
	const auto& sizeMap = *MetricProcessor();

	const auto& boundaries = Boundaries();
	for (const auto& x : boundaries)
	{
		Debug_Null_Pointer(x);
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();

		x->SetCentre(sizeMap.CalcCentre(n0->Coord(), n1->Coord()));
		x->SetCharLength(sizeMap.CalcDistance(n0->Coord(), n1->Coord()));
	}
}

void tnbLib::Aft2d_BoundaryOfPlane::Perform()
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

	std::vector<std::shared_ptr<typename Aft2d_RegionPlane::plnWireType>> wires;
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
	auto& boundaries = BoundariesRef();

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

		std::vector<std::shared_ptr<Aft2d_SegmentEdge>> Medges;

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
			std::vector<std::shared_ptr<Aft2d_SegmentEdge>> mesh;
			if (x->IsGap())
			{
				mesh = Cad2d_PlnGapCurve::TopoMesh<Aft2d_SegmentEdge>(x, MetricProcessor(), currentInfo);
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

		for (const auto& x : Medges)
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