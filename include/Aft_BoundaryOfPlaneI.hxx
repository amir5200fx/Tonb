#pragma once
#include <Global_Macros.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	template<class RegionType, class SizeFun>
	void Aft_BoundaryOfPlane<RegionType, SizeFun, void>::UpdateFront()
	{
		Debug_Null_Pointer(MetricProcessor());
		const auto& sizeMap = *MetricProcessor();

		const auto& boundaries = ChangeBoundaries();
		for (const auto& x : boundaries)
		{
			Debug_Null_Pointer(x);
			const auto& n0 = x->Node0();
			const auto& n1 = x->Node1();

			x->SetCentre(sizeMap.CalcCentre(n0->Coord(), n1->Coord()));
			x->SetCharLength(sizeMap.CalcDistance(n0->Coord(), n1->Coord()));
		}
	}


	template<class RegionType, class SizeFun>
	void Aft_BoundaryOfPlane<RegionType, SizeFun, void>::Perform()
	{
		if (NOT MetricProcessor())
		{
			FatalErrorIn("void Aft_BoundaryOfPlane<RegionType, SizeFun, MetricFun>::Perform()")
				<< " no metric processor has been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT Plane())
		{
			FatalErrorIn("void Aft_BoundaryOfPlane<RegionType, SizeFun, MetricFun>::Perform()")
				<< " no plane has been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT Info())
		{
			FatalErrorIn("void Aft_BoundaryOfPlane<RegionType, SizeFun, MetricFun>::Perform()")
				<< " no info has been loaded!" << endl
				<< abort(FatalError);
		}

		std::vector<std::shared_ptr<typename RegionType::plnWireType>> wires;
		Plane()->RetrieveWiresTo(wires);
		if (wires.empty())
		{
			FatalErrorIn("void Aft_BoundaryOfPlane<RegionType, SizeFun, MetricFun>::Perform()")
				<< " Invalid plane: wire list is empty" << endl
				<< abort(FatalError);
		}

		const auto& infoMap = Info()->Curve();
		auto& boundaries = ChangeBoundaries();
		Standard_Integer Ke = 0;
		Standard_Integer Kn = 0;

		//Standard_Boolean Checked = Standard_False;

		std::vector<Entity2d_Box> boxes;
		boxes.reserve(wires.size());

		for (const auto& wire : wires)
		{
			Debug_Null_Pointer(wire);

			std::vector<std::shared_ptr<bndType>> Medges;

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

				auto mesh = curveType::template TopoMesh<bndType>(x, MetricProcessor(), currentInfo);

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

			if (base::CheckWireNbPts(Medges))
			{
				base::SetNbPtsCheck(Standard_True);
				//Checked = Standard_True;
				continue;
			}

			if (base::CheckSimplicity(Medges))
			{
				base::SetSimpleCheck(Standard_True);
				//Checked = Standard_True;
				continue;
			}

			if (wires[0] IS_EQUAL wire)
			{
				if (base::CheckWireOrientation(Medges, Standard_True))
				{
					base::SetOrientCheck(Standard_True);
					//Checked = Standard_True;
				}
			}
			else
			{
				if (base::CheckWireOrientation(Medges, Standard_False))
				{
					base::SetOrientCheck(Standard_True);
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
				base::SetInnerCheck(Standard_True);
				break;
			}
			iter++;
		}

		bndType::ActiveBoundaryEdges(bndType::UpCast(boundaries));

		UpdateFront();

		base::Change_IsDone() = Standard_True;
	}
}