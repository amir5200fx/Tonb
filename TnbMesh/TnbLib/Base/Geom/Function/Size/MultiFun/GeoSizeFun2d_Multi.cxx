#include <GeoSizeFun2d_Multi.hxx>

Standard_Real tnbLib::GeoSizeFun2d_Multi::Value(const Pnt2d& theCoord) const
{
	auto value = RealLast();
	for (const auto& x: theFunctions_)
	{
		auto v0 = x->Value(theCoord);
		if (v0 < value)
		{
			value = v0;
		}
	}
	return value;
}
