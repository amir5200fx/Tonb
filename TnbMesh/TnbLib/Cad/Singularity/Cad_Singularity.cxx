#include <Cad_Singularity.hxx>

#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const tnbLib::Dir2d tnbLib::Cad_SingularityNonTempBase::T0 = tnbLib::Dir2d(0, 1);
const tnbLib::Dir2d tnbLib::Cad_SingularityNonTempBase::T1 = tnbLib::Dir2d(-1, 0);
const tnbLib::Dir2d tnbLib::Cad_SingularityNonTempBase::T2 = tnbLib::Dir2d(0, -1);
const tnbLib::Dir2d tnbLib::Cad_SingularityNonTempBase::T3 = tnbLib::Dir2d(1, 0);

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

Standard_Boolean 
tnbLib::Cad_SingularityNonTempBase::ReversePolygon
(
	const Dir2d & u,
	const Standard_Integer zoneId
)
{
	try
	{
		Debug_Bad_Index(zoneId, 0, 3);
		const auto& t = (&Cad_SingularityNonTempBase::T0)[zoneId - 1];
		return u.Crossed(t) < 0;
	}
	catch (const Standard_Failure& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.GetMessageString() << endl
			<< abort(FatalError);
		return Standard_True;
	}
}

Standard_Boolean 
tnbLib::Cad_SingularityNonTempBase::ReverseCrossZonesPolygon
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1, 
	const Pnt2d & theCentre
)
{
	try
	{
		const auto u0 = Dir2d(theCentre, theP0);
		const auto u1 = Dir2d(theCentre, theP1);
		return u0.Crossed(u1) < 0;
	}
	catch (const Standard_Failure& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.GetMessageString() << endl
			<< abort(FatalError);
		return Standard_True;
	}
}