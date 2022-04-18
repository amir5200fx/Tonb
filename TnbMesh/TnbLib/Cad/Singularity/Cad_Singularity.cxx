#include <Cad_Singularity.hxx>

#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::pair
<
	std::shared_ptr<tnbLib::Entity2d_Polygon>,
	std::shared_ptr<tnbLib::Entity2d_Polygon>
>
tnbLib::Cad_SingularityNonTempBase::RetrievePair
(
	const std::vector<std::shared_ptr<Entity2d_Polygon>>& theList
)
{
#ifdef _DEBUG
	if (theList.size() NOT_EQUAL 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "the list size is not 2!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	auto t = std::make_pair(theList.at(0), theList.at(1));
	return std::move(t);
}

tnbLib::Pnt2d 
tnbLib::Cad_SingularityNonTempBase::GetSamplePoint
(
	const Entity2d_Polygon & thePoly
)
{
	const auto& pts = thePoly.Points();
#ifdef _DEBUG
	if (pts.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid polygon has been detected!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	if (pts.size() IS_EQUAL 2)
	{
		auto m = MEAN(pts.at(0), pts.at(1));
		return std::move(m);
	}
	else
	{
		auto pt = pts.at(pts.size() / 2);
		return std::move(pt);
	}
}