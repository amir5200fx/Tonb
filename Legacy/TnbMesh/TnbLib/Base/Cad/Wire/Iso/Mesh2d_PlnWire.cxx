#include <Mesh2d_PlnWire.hxx>

#include <Mesh2d_PlnCurve.hxx>
#include <Pln_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
tnbLib::Entity2d_Box tnbLib::Mesh2d_PlnWire::CalcBoundingBox
(
	const Mesh2d_PlnCurve& theCurve
)
{
	const auto& c = theCurve.Curve();
	Debug_Null_Pointer(c);
	auto b = c->BoundingBox(0);
	return std::move(b);
}