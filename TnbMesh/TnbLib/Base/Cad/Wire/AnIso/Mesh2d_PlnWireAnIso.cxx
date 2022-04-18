#include <Mesh2d_PlnWireAnIso.hxx>

#include <Mesh2d_PlnCurveAnIso.hxx>
#include <Pln_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
tnbLib::Entity2d_Box tnbLib::Mesh2d_PlnWireAnIso::CalcBoundingBox
(
	const Mesh2d_PlnCurveAnIso& theCurve
)
{
	const auto& c = theCurve.Curve();
	Debug_Null_Pointer(c);
	auto b = c->BoundingBox(0);
	return std::move(b);
}