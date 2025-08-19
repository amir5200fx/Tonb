#include <Aft2d_gPlnRegionSurface.hxx>

#include <GModel_ParaCurve.hxx>
#include <GModel_Surface.hxx>
#include <GModel_Wire.hxx>
#include <GModel_Edge.hxx>
#include <Aft2d_gPlnCurveSurface.hxx>
#include <Aft2d_gPlnWireSurface.hxx>

namespace tnbLib
{

	void Mesh_PlnRegion<GModel_ParaCurve, Geo2d_SizeFunction, Geo2d_MetricFunction>::RetrieveWiresTo
	(
		wireList & theWires
	) const
	{
		theWires.push_back(theOutter_);
		if (theInner_)
		{
			for (const auto& x : *theInner_)
			{
				theWires.push_back(x);
			}
		}
	}

	std::shared_ptr<typename Aft2d_gPlnRegionSurface::plnWireType>
		Mesh_PlnRegion<GModel_ParaCurve, Geo2d_SizeFunction, Geo2d_MetricFunction>::MakeMeshWire
		(
			const GModel_Wire & theWire
		)
	{
		auto curves_ptr =
			std::make_shared<std::vector<std::shared_ptr<plnCurveType>>>();
		auto& curves = *curves_ptr;
		curves.reserve(theWire.NbEdges());

		Standard_Integer K = 0;
		for (const auto& x : *theWire.Edges())
		{
			Debug_Null_Pointer(x);

			const auto& xCurve = x->Par();
			Debug_Null_Pointer(xCurve);

			curves.push_back(std::make_shared<plnCurveType>(*xCurve));
		}

		auto wire =
			std::make_shared<plnWireType>(curves_ptr);

		return std::move(wire);
	}

	std::shared_ptr<Aft2d_gPlnRegionSurface>
		Mesh_PlnRegion<GModel_ParaCurve, Geo2d_SizeFunction, Geo2d_MetricFunction>::MakePlane
		(
			const std::shared_ptr<GModel_Surface> & theSurface
		)
	{
		Debug_Null_Pointer(theSurface);
		if (NOT theSurface->Outer())
		{
			FatalErrorIn(FunctionSIG)
				<< "Invalid surface : has no outer wire" << endl
				<< abort(FatalError);
		}

		const auto& Outer = *theSurface->Outer();
		const auto& Inners = *theSurface->Inner();

		auto outer_wire =
			MakeMeshWire(Outer);

		std::shared_ptr<std::vector<std::shared_ptr<plnWireType>>>
			inner_wires;
		if (theSurface->Inner())
		{
			inner_wires =
				std::make_shared<std::vector<std::shared_ptr<plnWireType>>>();
			inner_wires->reserve(Inners.size());

			for (const auto& x : Inners)
			{
				Debug_Null_Pointer(x);

				auto wire = MakeMeshWire(*x);
				inner_wires->push_back(wire);
			}
		}

		auto plane =
			std::make_shared<Aft2d_gPlnRegionSurface>
			(
				theSurface, outer_wire,
				inner_wires);
		return std::move(plane);
	}
}