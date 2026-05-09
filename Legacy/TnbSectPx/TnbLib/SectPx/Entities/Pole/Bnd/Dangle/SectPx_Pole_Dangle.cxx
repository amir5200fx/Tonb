#include <SectPx_Pole_Dangle.hxx>

#include <SectPx_Pnt_Compnt.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::Pole_Dangle::typeName_ = "dangle pole";

tnbLib::sectPxLib::Pole_Dangle::Pole_Dangle
(
	const std::shared_ptr<Pnt_Compnt>& thePnt
)
	: thePnt_(thePnt)
{
}

tnbLib::sectPxLib::Pole_Dangle::Pole_Dangle
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Pnt_Compnt>& thePnt
)
	: SectPx_BndPole(theIndex)
	, thePnt_(thePnt)
{
}

tnbLib::sectPxLib::Pole_Dangle::Pole_Dangle
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<Pnt_Compnt>& thePnt
)
	: SectPx_BndPole(theIndex, theName)
	, thePnt_(thePnt)
{
}

tnbLib::word 
tnbLib::sectPxLib::Pole_Dangle::RegObjTypeName() const
{
	return typeName_;
}

tnbLib::Pnt2d
tnbLib::sectPxLib::Pole_Dangle::Coord() const
{
	Debug_Null_Pointer(Pnt());
	auto pt = Pnt()->Coord();
	return std::move(pt);
}

std::shared_ptr<tnbLib::SectPx_Pnt>
tnbLib::sectPxLib::Pole_Dangle::Pnt() const
{
	return thePnt_;
}