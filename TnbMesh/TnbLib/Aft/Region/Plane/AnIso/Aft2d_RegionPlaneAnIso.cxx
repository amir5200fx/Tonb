#include <Aft2d_RegionPlaneAnIso.hxx>

#include <Aft2d_PlnWireAnIso.hxx>
#include <Aft2d_PlnCurveAnIso.hxx>
#include <Cad2d_PlnGapCurveAnIso.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Cad2d_Plane.hxx>

template<>
template<>
std::shared_ptr<tnbLib::Aft2d_PlnWireAnIso>
tnbLib::Aft2d_RegionPlaneAnIso::MakeMeshWire<tnbLib::Pln_Wire>
(
	const Pln_Wire& theWire
	)
{
	auto curves_ptr =
		std::make_shared<std::vector<std::shared_ptr<Aft2d_PlnCurveAnIso>>>();
	auto& curves = *curves_ptr;
	curves.reserve(theWire.NbEdges());

	Standard_Integer K = 0;
	for (const auto& x : theWire.Edges())
	{
		Debug_Null_Pointer(x);
		const auto& curve = x->Curve();
		Debug_Null_Pointer(curve);

		if (curve->IsGap())
		{
			auto newCurve = std::make_shared<Cad2d_PlnGapCurveAnIso>(curve);
			Debug_Null_Pointer(newCurve);
			newCurve->SetIndex(curve->Index());
			curves.push_back(std::move(newCurve));
		}
		else
		{
			auto newCurve = std::make_shared<Aft2d_PlnCurveAnIso>(curve);
			Debug_Null_Pointer(newCurve);
			newCurve->SetIndex(curve->Index());
			newCurve->SetSense(x->Sense());

			curves.push_back(std::move(newCurve));
		}
	}
	auto wire =
		std::make_shared<Aft2d_PlnWireAnIso>(std::move(curves));
	return std::move(wire);
}