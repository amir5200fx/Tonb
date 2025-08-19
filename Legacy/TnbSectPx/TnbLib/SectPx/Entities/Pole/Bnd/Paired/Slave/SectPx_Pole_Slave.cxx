#include <SectPx_Pole_Slave.hxx>

#include <SectPx_Pole_Master.hxx>
#include <SectPx_Pnts.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::Pole_Slave::typeName_ = "slave pole";

tnbLib::sectPxLib::Pole_Slave::Pole_Slave
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Pnt_Empty>& thePnt
)
	: SectPx_PairedPole(theIndex)
	, thePnt_(thePnt)
{
	// empty body
}

tnbLib::sectPxLib::Pole_Slave::Pole_Slave
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<Pnt_Empty>& thePnt
)
	: SectPx_PairedPole(theIndex, theName)
	, thePnt_(thePnt)
{
	// empty body
}

tnbLib::word 
tnbLib::sectPxLib::Pole_Slave::RegObjTypeName() const
{
	return typeName_;
}

tnbLib::Pnt2d
tnbLib::sectPxLib::Pole_Slave::Coord() const
{
	Debug_Null_Pointer(Master());
	auto pt = Master()->Coord();
	return std::move(pt);
}

std::shared_ptr<tnbLib::SectPx_Pnt>
tnbLib::sectPxLib::Pole_Slave::Pnt() const
{
	return thePnt_;
}