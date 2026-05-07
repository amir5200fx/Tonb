#pragma once
#include <Cad_PlnGapCurve.hxx>
#include <Cad_PoleSingularCurve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
namespace tnbLib
{
	template<class CurveType, class SizeFun, class MetricFun>
	void Mesh_RegionPlane<CurveType, SizeFun, MetricFun>::RetrieveWiresTo
	(
		wireList& theWires
	) const
	{
		theWires.push_back(theOuter_);
		if (theInner_)
		{
			for (const auto& x : *theInner_)
			{
				theWires.push_back(x);
			}
		}
	}

	template<class CurveType, class SizeFun, class MetricFun>
	template<class WireType>
	std::shared_ptr<typename Mesh_RegionPlane<CurveType, SizeFun, MetricFun>::plnWireType>
		Mesh_RegionPlane<CurveType, SizeFun, MetricFun>::MakeMeshWire
		(
			const WireType & theWire
		)
	{
		auto curves_ptr =
			std::make_shared<std::vector<std::shared_ptr<plnCurveType>>>();
		auto& curves = *curves_ptr;
		curves.reserve(theWire.NbEdges());

		Standard_Integer K = 0;
		for (const auto& x : theWire.Edges())
		{
			Debug_Null_Pointer(x);

			const auto& xCurve = x->Curve();
			Debug_Null_Pointer(xCurve);

			if (xCurve->IsGap())
			{
				auto gapCurve = std::make_shared<Cad_PlnGapCurve<plnCurveType>>(xCurve);
				curves.push_back(std::move(gapCurve));
			}
			else if (xCurve->IsDegenerated())
			{
				auto curve = std::make_shared<Cad_PoleSingularCurve<plnCurveType>>(xCurve);
				curves.push_back(std::move(curve));
			}
			else
			{
				auto curve = std::make_shared<plnCurveType>(xCurve);
				curves.push_back(std::move(curve));
			}
		}

		auto wire =
			std::make_shared<plnWireType>(std::move(curves));

		return std::move(wire);
	}
}

template<class CurveType, class SizeFun, class MetricFun>
std::shared_ptr<tnbLib::Mesh_RegionPlane<CurveType, SizeFun, MetricFun>>
tnbLib::Mesh_RegionPlane<CurveType, SizeFun, MetricFun>::MakePlane
(
	const std::shared_ptr<plnType>& thePlane
)
{
	Debug_Null_Pointer(thePlane);
	if (NOT thePlane->OuterWire())
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid surface : has no outer wire" << endl
			<< abort(FatalError);
	}

	const auto& Outer = *thePlane->OuterWire();

	auto outer_wire =
		MakeMeshWire(Outer);

	std::shared_ptr<std::vector<std::shared_ptr<plnWireType>>>
		inner_wires;
	if (thePlane->InnerWires())
	{
		const auto& Inners = *thePlane->InnerWires();
		inner_wires =
			std::make_shared<std::vector<std::shared_ptr<plnWireType>>>();
		inner_wires->reserve(Inners.size());

		for (const auto& x : Inners)
		{
			Debug_Null_Pointer(x);

			auto wire = MakeMeshWire(*x);
			inner_wires->push_back(std::move(wire));
		}
	}

	auto plane =
		std::make_shared<Mesh_RegionPlane>
		(
			thePlane, outer_wire,
			inner_wires);
	return std::move(plane);
}