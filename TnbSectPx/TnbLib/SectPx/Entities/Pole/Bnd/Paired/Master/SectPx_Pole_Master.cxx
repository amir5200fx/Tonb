#include <SectPx_Pole_Master.hxx>

#include <SectPx_Pnt_Compnt.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::Pole_Master::typeName_ = "master pole";

tnbLib::sectPxLib::Pole_Master::Pole_Master
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Pnt_Compnt>& thePnt
)
	: SectPx_PairedPole(theIndex)
	, thePnt_(thePnt)
{
}

tnbLib::sectPxLib::Pole_Master::Pole_Master
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<Pnt_Compnt>& thePnt
)
	: SectPx_PairedPole(theIndex, theName)
	, thePnt_(thePnt)
{
}

tnbLib::word 
tnbLib::sectPxLib::Pole_Master::RegObjTypeName() const
{
	return typeName_;
}

tnbLib::Pnt2d
tnbLib::sectPxLib::Pole_Master::Coord() const
{
	Debug_Null_Pointer(Pnt());
	auto pt = Pnt()->Coord();
	return std::move(pt);
}

std::shared_ptr<tnbLib::SectPx_Pnt>
tnbLib::sectPxLib::Pole_Master::Pnt() const
{
	return thePnt_;
}