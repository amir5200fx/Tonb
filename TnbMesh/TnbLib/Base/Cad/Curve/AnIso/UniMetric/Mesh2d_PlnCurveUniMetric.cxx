#include <Mesh2d_PlnCurveUniMetric.hxx>

#include <Pln_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
Handle(Geom2d_Curve) 
tnbLib::Mesh2d_PlnCurveUniMetric::Geometry() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->Geometry();
}

template<>
Standard_Real 
tnbLib::Mesh2d_PlnCurveUniMetric::FirstParameter() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->FirstParameter();
}

template<>
Standard_Real 
tnbLib::Mesh2d_PlnCurveUniMetric::LastParameter() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->LastParameter();
}

template<>
tnbLib::Pnt2d tnbLib::Mesh2d_PlnCurveUniMetric::Value(const Standard_Real x) const
{
	Debug_Null_Pointer(Curve());
	auto pt = Curve()->Value(x);
	return std::move(pt);
}

template<>
void tnbLib::Mesh2d_PlnCurveUniMetric::Reverse()
{
	Debug_Null_Pointer(Curve());
	Curve()->Reverse();
}