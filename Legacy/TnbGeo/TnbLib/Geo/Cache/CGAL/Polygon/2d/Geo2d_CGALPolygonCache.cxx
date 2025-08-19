#include <Geo2d_CGALPolygonCache.hxx>

#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::Geo2d_CGALPolygonCache::Geo2d_CGALPolygonCache(const Entity2d_Polygon& thePolygon)
{
	for (size_t i = 0; i < thePolygon.Points().size() - 1; i++)
	{
		const auto& x = thePolygon.Points().at(i);
		Point_2 pt(x.X(), x.Y());
		thePolygon_.push_back(std::move(pt));
	}
	if (NOT thePolygon_.is_simple())
	{
		FatalErrorIn(FunctionSIG)
			<< "the polygon is not simple" << endl
			<< abort(FatalError);
	}
}