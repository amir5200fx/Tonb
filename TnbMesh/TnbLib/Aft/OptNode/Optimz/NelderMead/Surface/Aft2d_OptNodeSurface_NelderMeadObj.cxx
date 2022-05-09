#include <Aft2d_OptNodeSurface_NelderMeadObj.hxx>

#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Real tnbLib::Aft2d_OptNodeSurface_NelderMeadObj::DEFAULT_TOLERANCE = 1.0E-3;

const int tnbLib::Aft2d_OptNodeSurface_NelderMeadObj::nbVariables = 2;

Standard_Real 
tnbLib::Aft2d_OptNodeSurface_NelderMeadObj::EstimateError
(
	const Standard_Real d0, 
	const Standard_Real d1
)
{
	auto e0 = ABS(1.0 - d0);
	auto e1 = ABS(1.0 - d1);
	std::cout << "e0: " << e0 << ",  e1: " << e1 << std::endl;
	std::cout << MEAN(e0, e1) << std::endl;
	return MEAN(e0, e1);
}

Standard_Real 
tnbLib::Aft2d_OptNodeSurface_NelderMeadObj::Value
(
	const Pnt2d & theCoord
) const
{
	Debug_Null_Pointer(MetricMap());
	const auto& map = *MetricMap();
	std::cout << "coord: " << theCoord << std::endl;
	d0 = map.CalcDistance(theCoord, P0());
	d1 = map.CalcDistance(theCoord, P1());

	return EstimateError(d0, d1);
}

Standard_Boolean 
tnbLib::Aft2d_OptNodeSurface_NelderMeadObj::IsConverged() const
{
	return (ABS(1.0 - d0) <= Tolerance() AND ABS(1.0 - d1) <= Tolerance());
}

void tnbLib::Aft2d_OptNodeSurface_NelderMeadObj::SetV
(
	const Standard_Integer Dim,
	const Standard_Real xi,
	Pnt2d & P
)
{
	Debug_Null_Pointer(MetricMap());
	const auto& domain = MetricMap()->BoundingBox();
	auto[x0, x1] = domain.Bound(Dim - 1);
	auto x = xi;
	if (x < x0)
	{
		std::cout << "corrected!" << std::endl;
		x = x0;
	}
	if (x > x1)
	{
		std::cout << "corrected!" << std::endl;
		x = x1;
	}
	P.SetCoord(Dim, x);
}