#include <SectPx_OneParCPtsMap_Single.hxx>

#include <SectPx_Pole.hxx>
#include <SectPx_Pars.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::OneParCPtsMap_Single::typeName_("single point cpts map");

tnbLib::sectPxLib::OneParCPtsMap_Single::OneParCPtsMap_Single(const Standard_Integer theIndex)
	: SectPx_OneParCPtsMap(theIndex)
{
	// empty body
}

tnbLib::sectPxLib::OneParCPtsMap_Single::OneParCPtsMap_Single
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: SectPx_OneParCPtsMap(theIndex, theName)
{
	// empty body
}

tnbLib::word
tnbLib::sectPxLib::OneParCPtsMap_Single::RegObjTypeName() const
{
	return typeName_;
}

Standard_Integer
tnbLib::sectPxLib::OneParCPtsMap_Single::NbPts() const
{
	return 1;
}

std::vector<tnbLib::Pnt2d>
tnbLib::sectPxLib::OneParCPtsMap_Single::Pts() const
{
	std::vector<Pnt2d> pts;
	pts.push_back(CalcCoord());
	return std::move(pts);
}

tnbLib::Pnt2d
tnbLib::sectPxLib::OneParCPtsMap_Single::CalcCoord() const
{
	Debug_If_Condition(NOT IsComplete());

	Debug_Null_Pointer(Pole0());
	Debug_Null_Pointer(Pole1());

	Debug_If_Condition(Pole0() IS_EQUAL Pole1());

	const auto p0 = Pole0()->Coord();
	const auto p1 = Pole1()->Coord();

	const auto t = Par().lock();
	Debug_If_Condition(t->InCycle());

	return p0 + t->Value()*(p1 - p0);
}