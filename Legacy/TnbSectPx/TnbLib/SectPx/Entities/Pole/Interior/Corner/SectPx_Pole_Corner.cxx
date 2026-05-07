#include <SectPx_Pole_Corner.hxx>

#include <SectPx_Pnt.hxx>

const char* tnbLib::sectPxLib::Pole_Corner::typeName_ = "corner pole";

tnbLib::sectPxLib::Pole_Corner::Pole_Corner
(
	const Standard_Integer theIndex,
	const std::shared_ptr<SectPx_Pnt>& thePnt
)
	: SectPx_InterPole(theIndex)
	, thePnt_(thePnt)
{
}

tnbLib::sectPxLib::Pole_Corner::Pole_Corner
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<SectPx_Pnt>& thePnt
)
	: SectPx_InterPole(theIndex, theName)
	, thePnt_(thePnt)
{
}

tnbLib::word 
tnbLib::sectPxLib::Pole_Corner::RegObjTypeName() const
{
	return typeName_;
}

tnbLib::Pnt2d
tnbLib::sectPxLib::Pole_Corner::Coord() const
{
	Debug_Null_Pointer(Pnt());
	auto pt = Pnt()->Coord();
	return std::move(pt);
}