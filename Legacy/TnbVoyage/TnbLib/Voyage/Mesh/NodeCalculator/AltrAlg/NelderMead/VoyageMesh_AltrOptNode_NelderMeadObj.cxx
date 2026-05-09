#include <VoyageMesh_AltrOptNode_NelderMeadObj.hxx>

#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Real tnbLib::VoyageMesh_AltrOptNode_NelderMeadObj::DEFAULT_TOLERANCE = 1.0E-3;
const int tnbLib::VoyageMesh_AltrOptNode_NelderMeadObj::nbVariables = 2;

Standard_Real
tnbLib::VoyageMesh_AltrOptNode_NelderMeadObj::EstimateError
(
	const Standard_Real d0,
	const Standard_Real d1
)
{
	const auto del0 = std::abs(1.0 - d0);
	const auto del1 = std::abs(1.0 - d1);

	static const Standard_Real Pow = 3.0;
	const auto cost0 = std::pow(1.0 + del0, Pow);
	const auto cost1 = std::pow(1.0 + del1, Pow);

	return cost0 * cost1;
}

Standard_Real
tnbLib::VoyageMesh_AltrOptNode_NelderMeadObj::Value
(
	const Pnt2d& theCoord
) const
{
	Debug_Null_Pointer(MetricMap());
	const auto& map = *MetricMap();

	d0 = map.CalcUnitDistance(theCoord, P0());
	d1 = map.CalcUnitDistance(theCoord, P1());

	return EstimateError(d0, d1);
}

Standard_Boolean
tnbLib::VoyageMesh_AltrOptNode_NelderMeadObj::IsConverged() const
{
	return (ABS(1.0 - d0) <= Tolerance() AND ABS(1.0 - d1) <= Tolerance());
}

void tnbLib::VoyageMesh_AltrOptNode_NelderMeadObj::SetV
(
	const Standard_Integer Dim,
	const Standard_Real xi,
	Pnt2d& P
)
{
	Debug_Null_Pointer(MetricMap());
	const auto& domain = MetricMap()->BoundingBox();
	auto [x0, x1] = domain.Bound(Dim - 1);
	auto x = xi;
	if (x < x0)
	{
		x = x0;
	}
	if (x > x1)
	{
		x = x1;
	}
	P.SetCoord(Dim, x);
}