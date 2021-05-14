#include <Aft2d_BoundaryOfPlane.hxx>

#include <Geo_BoxTools.hxx>
#include <Pln_Curve.hxx>
#include <Aft2d_SegmentEdge.hxx>
#include <Aft2d_PlnWire.hxx>
#include <Aft2d_PlnCurve.hxx>
#include <Aft2d_BoundaryOfPlane_Info.hxx>
#include <Aft2d_RegionPlane.hxx>
#include <Aft_Tools.hxx>
#include <Geo2d_MetricPrcsr.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

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

	std::vector<std::shared_ptr<typename Aft2d_RegionPlane::plnWireType>> wires;
	Plane()->RetrieveWiresTo(wires);
	if (wires.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid plane has been detected: the wire list is empty!" << endl
			<< abort(FatalError);
	}

	const auto& infoMap = Info()->Curve();
	auto& boundaries = BoundariesRef();

	Standard_Integer Ke = 0;
	Standard_Integer Kn = 0;

	std::vector<Entity2d_Box> boxes;
	boxes.reserve(wires.size());

	for (const auto& wire : wires)
	{
		Debug_Null_Pointer(wire);

		std::vector<std::shared_ptr<Aft2d_SegmentEdge>> Medges;

		std::vector<Entity2d_Box> wBoxes;
		const auto& curves = wire->Curves();
		wBoxes.reserve(curves.size());
		for (const auto& x : curves)
		{
			Debug_Null_Pointer(x);

			Debug_Null_Pointer(Info()->GlobalCurve());
			auto currentInfo = Info()->GlobalCurve();

			if (Info()->OverrideInfo() AND infoMap.size())
			{
				auto iter = infoMap.find(x->Index());

				if (iter NOT_EQUAL infoMap.end())
				{
					currentInfo = iter->second;
				}
			}

			auto mesh = Aft_Tools::RetrieveTopoMesh(x, MetricProcessor(), currentInfo);

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

		if (CheckWireNbPts(boundaries))
		{
			SetNbPtsCheck(Standard_True);
			//Checked = Standard_True;
			continue;
		}

		if (CheckSimplicity(boundaries))
		{
			SetSimpleCheck(Standard_True);
			//Checked = Standard_True;
			continue;
		}

		if (wires[0] IS_EQUAL wire)
		{
			if (CheckWireOrientation(boundaries, Standard_True))
			{
				SetOrientCheck(Standard_True);
				//Checked = Standard_True;
			}
		}
		else
		{
			if (CheckWireOrientation(boundaries, Standard_False))
			{
				SetOrientCheck(Standard_True);
				//Checked = Standard_True;
			}
		}
	}

	auto iter = boxes.begin();
	auto box0 = *iter;
	iter++;

	while (iter NOT_EQUAL boxes.end())
	{
		if (NOT Entity2d_Box::IsInside(iter->OffSet(1.0E-4), box0))
		{
			SetInnerCheck(Standard_True);
			break;
		}
		iter++;
	}

	Aft_Tools::ActiveBoundaryEdges(boundaries);

	UpdateFront();

	Change_IsDone() = Standard_True;
}